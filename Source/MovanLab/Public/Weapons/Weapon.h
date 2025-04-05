// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class MOVANLAB_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndAttack();

	virtual void StartAttack_Implementation();
	virtual void EndAttack_Implementation();

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


