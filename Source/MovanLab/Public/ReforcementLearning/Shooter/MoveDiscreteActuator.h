// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actuators/AbstractActuators.h"
#include "MoveDiscreteActuator.generated.h"

/**
 * 
 */
UCLASS()
class MOVANLAB_API UMoveDiscreteActuator : public UDiscreteActuator
{
public:
	virtual FDiscreteSpace GetActionSpace() override;
	virtual void TakeAction(const FDiscretePoint& Action) override;

private:
	GENERATED_BODY()
};
