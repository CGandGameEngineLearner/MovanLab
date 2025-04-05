// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShootComponent.h"

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
	Character = Cast<ACharacter>(GetOwner());
	checkf(Character,TEXT("ShootComponent必须被挂载在Character类的对象上"));

	GunSocket = Character->GetMesh()->GetSocketByName(GunSocketName);
	checkf(GunSocket, TEXT("GunSocket: %s 不存在，请检查名称是否正确"), *GunSocketName.ToString());
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

