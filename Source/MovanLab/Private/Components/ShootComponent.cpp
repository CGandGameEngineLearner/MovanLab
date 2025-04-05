// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShootComponent.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"


void UShootComponent::SetAimPitch(float Pitch)
{
	AimPitch = Pitch;
}

float UShootComponent::GetAimPitch()const
{
	return AimPitch;
}

void UShootComponent::StartLeftFire()
{
	if (ShootWeapon)
	{
		ShootWeapon->StartAttack();
	}
}

void UShootComponent::EndLeftFire()
{
	if (ShootWeapon)
	{
		ShootWeapon->EndAttack();
	}
}

void UShootComponent::SetShootWeapon(AShootWeapon* Weapon)
{
	if (ShootWeapon)
	{
		ShootWeapon->UnEquip();
		ShootWeapon = nullptr;
	}
	ShootWeapon = Weapon;
	if (ShootWeapon)
	{
		ShootWeapon->Equip(OwnerCharacter);
	}
}

// Sets default values for this component's properties
UShootComponent::UShootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
	


	
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	checkf(OwnerCharacter,TEXT("ShootComponent必须被挂载在Character类的对象上"));

	GunSocket = OwnerCharacter->GetMesh()->GetSocketByName(GunSocketName);
	checkf(GunSocket, TEXT("GunSocket: %s 不存在，请检查名称是否正确"), *GunSocketName.ToString());

	AbilitySystemComponent = OwnerCharacter->FindComponentByClass<UAbilitySystemComponent>();
	checkf(AbilitySystemComponent,TEXT("AbilitySystemComponent必须被挂载在Character类的对象上"));

	
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

