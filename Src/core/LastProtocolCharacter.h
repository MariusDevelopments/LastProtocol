// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Gun.h"
#include "LastProtocolCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 * Oyuncunun yonettigi ana third person karakter.
 * Hareket, kamera, silah ve saglik akisini bu sinif toplar.
 */
UCLASS(abstract)
class ALastProtocolCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Kamerayi karakterin arkasinda tutan spring arm. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Oyuncunun baktigi takip kamerasi. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;


	UPROPERTY(EditAnywhere, Category = "Input|Touch Controls")
	UInputAction* ShootAction;

public:

	/** Constructor */
	ALastProtocolCharacter();	

protected:
	virtual void BeginPlay() override;


	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void Shoot();

	// Blueprint tarafinda secilen silah sinifi oyun baslayinca karaktere takilir.
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;

	// Karakterin maksimum can degeri. Blueprint uzerinden dengelenebilir.
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;

	// Anlik can degeri. BeginPlay icinde MaxHealth ile baslatilir.
	float Health;

	// AI ve task'lar oyuncunun hayatta olup olmadigini bu bayraktan kontrol eder.
	UPROPERTY(BlueprintReadOnly)
	bool IsAlive = true;

	// Spawn edilen ve karakterin WeaponSocket noktasina takilan silah nesnesi.
	AGun* Gun;

	// Can degistikten sonra HUD uzerindeki health bar'i gunceller.
	void UpdateHUD();

	// Unreal'in damage sistemi tarafindan cagrilir; can azaltma ve olme akisi burada islenir.
	UFUNCTION()
	void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};

