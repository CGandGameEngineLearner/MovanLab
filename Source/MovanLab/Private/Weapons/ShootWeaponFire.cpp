// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ShootWeaponFire.h"


// Sets default values
AShootWeaponFire::AShootWeaponFire()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShootWeaponFire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShootWeaponFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShootWeaponFire::Fire_Implementation(FTrajectory Trajectory)
{
	
}

