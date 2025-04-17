// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/ShootWeapon.h"
#include "ShootComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnHitSignature, UShootComponent, OnHit, AActor*, HitActor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOVANLAB_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AShootWeapon> ShootWeapon = nullptr;

	
	
	
public:

	/** 枪械在骨骼上的插槽名称 */ 
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category=Shoot)
	FName WeaponSocketName;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TSubclassOf<UGameplayAbility> ShootAbilityClass;


	UPROPERTY(BlueprintAssignable)
	FOnHitSignature OnHit;


	
private:
	TObjectPtr<ACharacter> OwnerCharacter = nullptr;
	

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;


	FDelegateHandle OnHitDelegateHandle;

	
public:



	UFUNCTION(BlueprintCallable, Category="Shoot")
	void StartLeftFire();

	UFUNCTION(BlueprintCallable, Category="Shoot")
	void EndLeftFire();

	UFUNCTION(BlueprintCallable, Category="Shoot")
	void SetShootWeapon(AShootWeapon* Weapon);
	
public:
	// Sets default values for this component's properties
	UShootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
