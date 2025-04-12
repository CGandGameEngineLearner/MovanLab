// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ShootComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "Shooter.generated.h"

class UHealthAttributeSet;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogShooter, Log, All);

UCLASS(config=Game)
class AShooter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()


private:
	void BindPropertyEvents();

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser,  float DamageMagnitude, float OldValue, float NewValue);

	virtual void HandleOutOfHealth_Implementation(AActor* DamageInstigator, AActor* DamageCauser, float DamageMagnitude, float OldValue, float NewValue);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Movement)
	float RunSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Movement)
	float WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Movement)
	float AimSpeed = 210.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
	UHealthAttributeSet* HealthAttributeSet;




private:
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** 射击 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Shoot, meta = (AllowPrivateAccess = "true"))
	UShootComponent* ShootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;
	
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Run Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* RunAction;
	
	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LeftFireAction;

public:
	AShooter();


	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for start run */
	void StartRun(const FInputActionValue& Value);

	/** Called for end run */
	void EndRun(const FInputActionValue& Value);

	void StartLeftFire(const FInputActionValue& Value);

	void EndLeftFire(const FInputActionValue& Value);
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};


