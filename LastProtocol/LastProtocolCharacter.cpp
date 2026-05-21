// Copyright Epic Games, Inc. All Rights Reserved.

#include "LastProtocolCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "LastProtocol.h"
#include "LastProtocolPlayerController.h"

ALastProtocolCharacter::ALastProtocolCharacter()
{
	// Karakterin carpisma kapsulunu third person karakter boyutuna ayarliyoruz.
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Controller donusu kamerayi etkiler, karakterin kendisi hareket yonune gore doner.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Karakter hareket ayarlari: hiz, donus ve ziplama hissi burada belirlenir.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Bu degerler Blueprint tarafindan da degistirilebilir; oyun hissini dengelemek icin kullanilir.
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Kamera kolu karakterin arkasinda durur ve duvara girerse otomatik kisalir.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// FollowCamera spring arm ucuna baglanir; bakis kontrolunu spring arm tasir.
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Mesh ve anim blueprint referanslari C++ yerine karakter Blueprint'i uzerinden verilir.
}

void ALastProtocolCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Hasar alindiginda OnDamageTaken fonksiyonunun otomatik calismasi icin delegate baglaniyor.
	OnTakeAnyDamage.AddDynamic(this, &ALastProtocolCharacter::OnDamageTaken);

	// Oyun basinda cani maksimum degere kuruyoruz.
	Health = MaxHealth;
	UpdateHUD();

	// Karakter mesh'indeki varsayilan silah kemigini gizleyip kendi silah actor'umuzu kullaniyoruz.
	GetMesh()->HideBoneByName("weapon_r", EPhysBodyOp::PBO_None);

	// Blueprint'te secilen silah sinifini spawn edip karakterin WeaponSocket noktasina bagliyoruz.
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	if (Gun) {
		Gun->SetOwner(this);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Gun->OwnerController = GetController();
	}
}

void ALastProtocolCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Enhanced Input action'lari karakter fonksiyonlarina baglaniyor.
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Ziplama baslama ve bitirme inputlari.
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Hareket ve mouse bakis inputlari.
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALastProtocolCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ALastProtocolCharacter::Look);

		// Gamepad veya alternatif bakis inputu.
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALastProtocolCharacter::Look);

		// Ates etme inputu silahin tetigini cagirir.
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ALastProtocolCharacter::Shoot);

	}
	else
	{
		UE_LOG(LogLastProtocol, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ALastProtocolCharacter::Move(const FInputActionValue& Value)
{
	// Input degeri X/Y eksenli hareket vektoru olarak okunur.
	FVector2D MovementVector = Value.Get<FVector2D>();

	// Ortak hareket fonksiyonuna aktarilir; boylece UI veya input ayni fonksiyonu kullanabilir.
	DoMove(MovementVector.X, MovementVector.Y);
}

void ALastProtocolCharacter::Look(const FInputActionValue& Value)
{
	// Input degeri yatay/dikey kamera bakisi olarak okunur.
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// Kamera donusunu ortak bakis fonksiyonuna yonlendiriyoruz.
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ALastProtocolCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// Kamera yaw acisina gore ileri ve sag yonleri hesaplanir.
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Hesaplanan yonlere input miktari kadar hareket eklenir.
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ALastProtocolCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// Kamera/karakter kontrolune yaw ve pitch girdisi eklenir.
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ALastProtocolCharacter::DoJumpStart()
{
	// Karaktere ziplama komutu verilir.
	Jump();
}

void ALastProtocolCharacter::DoJumpEnd()
{
	// Tus birakilinca ziplama kesilir.
	StopJumping();
}

void ALastProtocolCharacter::Shoot()
{
	// Silah varsa tetiklenir; asil raycast ve damage hesabi AGun icindedir.
	if (Gun) 
		Gun->PullTrigger();
	
}

void ALastProtocolCharacter::UpdateHUD()
{
	ALastProtocolPlayerController* PlayerController = Cast<ALastProtocolPlayerController>(GetController());

	if (PlayerController && PlayerController->HUDWidget) {

		const float HealthPercent = MaxHealth > 0.0f ? Health / MaxHealth : 0.0f;

		PlayerController->HUDWidget->SetHealthBarPercent(HealthPercent);
	}
}

void ALastProtocolCharacter::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsAlive) {
		// Can degerini 0 ile MaxHealth arasinda tutarak HUD'a temiz bir yuzde gonderiyoruz.
		Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
		UpdateHUD();
		if (Health <= 0.0f) {
			IsAlive = false;

			// Olunce karakter artik carpisma almaz ve controller'dan ayrilir.
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			DetachFromControllerPendingDestroy();

		}
	}
}
