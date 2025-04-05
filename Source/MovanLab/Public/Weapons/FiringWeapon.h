// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"

#include "Components/ArrowComponent.h"
#include "Equipment/EquipmentInterface.h"
#include "Weapons/Trajectory.h"
#include "FiringWeapon.generated.h"

UCLASS()
class MOVANLAB_API AFiringWeapon : public AWeapon, public IEquipmentInterface
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* MuzzleArrow;

	/** 蛋壳抛出位置箭头 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* ShellEjectArrow;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* MuzzleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ACharacter> OwnerCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDrawDebugLine = false;

private:
	bool bFiring = false;

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
	AFiringWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
