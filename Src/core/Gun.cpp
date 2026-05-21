// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Kismet/GameplayStatics.h"

AGun::AGun()
{
	// Silah actor'u Tick alabilir; ileride recoil/cooldown gibi sistemler eklenebilir.
	PrimaryActorTick.bCanEverTick = true;

	// Root, mesh ve muzzle flash component hiyerarsisi kuruluyor.
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot); 

	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Muzzle Flash Particle"));
	MuzzleFlashParticleSystem->SetupAttachment(Mesh);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	// Ates edilene kadar muzzle flash kapali kalir.
	MuzzleFlashParticleSystem->Deactivate();

}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AGun::PullTrigger()
{
	// Her tetik cekildiginde namlu efekti yeniden baslatilir.
	MuzzleFlashParticleSystem->Activate(true);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, GetActorLocation());

	if (OwnerController)
	{
		// Merminin cikis ve bakis yonu oyuncunun/AI'nin kamera bakisindan alinir.
		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

		//DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90.0f, 2.0f, FColor::Red, true);

		// ViewPointRotation.Vector() ileri yonu verir; MaxRange ile menzil son noktasi hesaplanir.
		FVector EndLocation = ViewPointLocation+ ViewPointRotation.Vector()* MaxRange;

		FHitResult HitResult;
		FCollisionQueryParams Params;
		// Silah ve silahin sahibi raycast tarafindan vurulmasin diye yok sayilir.
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());


		// Ozel trace channel uzerinden tek bir isabet kontrolu yapilir.
		bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation, EndLocation, ECC_GameTraceChannel2, Params);

		if (IsHit) {
			// Isabet noktasinda efekt olusturulur ve vurulan actor'e damage gonderilir.
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactParticleSystem, HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.ImpactPoint);


			AActor* HitActor = HitResult.GetActor();
			if (HitActor) {
				UGameplayStatics::ApplyDamage(HitActor, BulletDamage, OwnerController, this, UDamageType::StaticClass());
			}
		}
	}
}

