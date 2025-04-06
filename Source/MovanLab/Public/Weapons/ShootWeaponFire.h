// Fill out your copyright notice in the Description page of Project Settings.



#pragma once

#include "CoreMinimal.h"
#include "ShootInterface.h"
#include "Trajectory.h"
#include "GameFramework/Actor.h"
#include "ShootWeaponFire.generated.h"

// 用来播放和管理枪械特效的类
UCLASS()
class MOVANLAB_API AShootWeaponFire : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShootWeaponFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Fire(FTrajectory Trajectory);

	virtual void Fire_Implementation(FTrajectory Trajectory);
};
