// Fill out your copyright notice in the Description page of Project Settings.


#include "ReforcementLearning/Shooter/MoveDiscreteActuator.h"


FDiscreteSpace UMoveDiscreteActuator::GetActionSpace()
{
	FDiscreteSpace Result;
	Result.Add(9);
	return Result;
}

void UMoveDiscreteActuator::TakeAction(const FDiscretePoint& Action)
{
	Super::TakeAction(Action);
}
