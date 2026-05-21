// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Gun.generated.h"

UCLASS()
class LASTPROTOCOL_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Silah actor'unun varsayilan componentlerini kurar.
	AGun();

protected:
	// Silah spawn edildiginde ilk ayarlar burada yapilir.
	virtual void BeginPlay() override;

public:	
	// Gerekirse silahin frame bazli davranislari icin kullanilir.
	virtual void Tick(float DeltaTime) override;

	// Silahin ana root componenti.
	UPROPERTY(VisibleAnyWhere)
	USceneComponent* SceneRoot;
	 
	// Silahin gorunen skeletal mesh'i.
	UPROPERTY(VisibleAnyWhere)
	USkeletalMeshComponent* Mesh;

	// Namlu ates efekti icin Niagara componenti.
	UPROPERTY(VisibleAnyWhere)
	UNiagaraComponent* MuzzleFlashParticleSystem;

	// Mermi bir yuzeye carptiginda oynatilacak impact efekti.
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ImpactParticleSystem;

	// Her isabetin uygulayacagi hasar miktari.
	UPROPERTY(EditAnywhere)
	float BulletDamage = 10.0f;

	// Raycast merminin maksimum menzili.
	UPROPERTY(EditAnywhere)
	float MaxRange = 10000.0f;

	UPROPERTY(EditAnywhere)
	USoundBase* ShootSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	// Silahi kullanan pawn'un controller'i; damage kaynagini dogru vermek icin tutulur.
	AController* OwnerController;

	// Ates etme akisi: muzzle flash, line trace, impact efekti ve damage.
	void PullTrigger();

};
