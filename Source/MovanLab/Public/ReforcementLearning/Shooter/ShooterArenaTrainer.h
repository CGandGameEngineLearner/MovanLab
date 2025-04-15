// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Training/AbstractTrainer.h"
#include "ShooterArenaTrainer.generated.h"

UCLASS()
class MOVANLAB_API AShooterArenaTrainer : public ABlueprintTrainer, public IGenericTeamAgentInterface
{
public:
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGenericTeamId TeamId = FGenericTeamId();

private:
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShooterArenaTrainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
};
