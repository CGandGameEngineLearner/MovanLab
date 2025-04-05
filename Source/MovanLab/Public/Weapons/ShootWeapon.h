// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"

#include "Components/ArrowComponent.h"
#include "Equipment/EquipmentInterface.h"
#include "GAS/Abilities/ShootAbility.h"
#include "Weapons/Trajectory.h"
#include "ShootWeapon.generated.h"

UCLASS()
class MOVANLAB_API AShootWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* MuzzleMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TSubclassOf<UShootAbility> ShootAbilityClass;

	/** 蛋壳抛出位置插槽 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ShellEjectName;

	/** 枪口位置插槽 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName;

	/** 弹匣外备用的子弹数量 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ReserveAmmunitionQuantity = 180;
	
	/** 弹匣中的子弹数量 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagazineAmmunitionQuantity = 30;

	/** 子弹伤害 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BulletInjury = 10;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDrawDebugLine = false;

private:
	bool bFiring = false;

	TObjectPtr<const USkeletalMeshSocket> MuzzleSocket;

	TObjectPtr<const USkeletalMeshSocket> ShellEjectSocket;

	FGameplayAbilitySpecHandle SpecHandle;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTrajectory ComputeTrajectory();

	virtual FTrajectory ComputeTrajectory_Implementation();
	
	virtual void StartAttack_Implementation() override;
	virtual void EndAttack_Implementation() override;

	virtual void Equip_Implementation(ACharacter* InOwner) override;

	virtual void UnEquip_Implementation() override;

public:
	// Sets default values for this actor's properties
	AShootWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
