// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"


void AWeapon::EndAttack_Implementation()
{
}

void AWeapon::StartAttack_Implementation()
{
	
}

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

