// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/EquipmentInterface.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UAbilitySystemComponent;

UCLASS()
class MOVANLAB_API AWeapon : public AActor,  public IEquipmentInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAbilitySystemComponent> OwnerAbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ACharacter> OwnerCharacter = nullptr;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndAttack();

	virtual void StartAttack_Implementation();
	virtual void EndAttack_Implementation();


	virtual void Equip_Implementation(ACharacter* InOwner) override;

	virtual void UnEquip_Implementation() override;

public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};


