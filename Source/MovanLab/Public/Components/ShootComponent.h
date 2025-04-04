// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOVANLAB_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	float AimPitch;

public:

	UFUNCTION(BlueprintCallable, Category="Shoot")
	void SetAimPitch(float Pitch);
	
	UFUNCTION(BlueprintPure, Category="Shoot")
	float GetAimPitch()const;
	
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
