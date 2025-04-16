// Fill out your copyright notice in the Description page of Project Settings.


#include "ReforcementLearning/Shooter/ShooterArenaTrainer.h"


void AShooterArenaTrainer::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	this->TeamId = TeamID;
}

FGenericTeamId AShooterArenaTrainer::GetGenericTeamId() const
{
	return this->TeamId;
}

ETeamAttitude::Type AShooterArenaTrainer::GetTeamAttitudeTowards(const AActor& Other) const
{
	ETeamAttitude::Type Result = ETeamAttitude::Type::Neutral;

	if (GetPawn()->Tags.Num() > 0 && Other.Tags.Num() > 0)
	{
		if (GetPawn()->Tags[0] != Other.Tags[0])
		{
			Result = ETeamAttitude::Type::Hostile;
		}
		else
		{
			Result = ETeamAttitude::Type::Friendly;
		}
	}
	
	

	APawn* OtherPawn = Cast<APawn>(Other.GetOuter());
	if (OtherPawn == nullptr)
	{
		return  Result;
	}
	AController* OtherController = OtherPawn->GetController();
	if (OtherController == nullptr)
	{
		return  Result;
	}
	IGenericTeamAgentInterface* OtherGenericTeamAgentInterface = Cast<IGenericTeamAgentInterface>(OtherController);
	if (OtherGenericTeamAgentInterface == nullptr)
	{
		return  Result;
	}
	
	
	FGenericTeamId OtherTeamId = OtherGenericTeamAgentInterface->GetGenericTeamId();
	if (OtherTeamId==TeamId)
	{
		Result = ETeamAttitude::Type::Friendly;
		return  Result;
	}
	else
	{
		Result = ETeamAttitude::Type::Hostile;
		return  Result;
	}
}

// Sets default values
AShooterArenaTrainer::AShooterArenaTrainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterArenaTrainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterArenaTrainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

