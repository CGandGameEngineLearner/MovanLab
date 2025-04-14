// Fill out your copyright notice in the Description page of Project Settings.


#include "ReforcementLearning/Shooter/AIMoveToActuator.h"


#include "Blueprint/AIBlueprintHelperLibrary.h"


class UNavigationSystemV1;

FBoxSpace UAIMoveToActuator::GetActionSpace()
{
	FBoxSpace OutSpace;
	
	if (bHasXDimension)
	{
		OutSpace.Add(MinX, MaxX);
	}

	if (bHasYDimension)
	{
		OutSpace.Add(MinY, MaxY);
	}

	if (bHasZDimension)
	{
		OutSpace.Add(MinZ, MaxZ);
	}
	return OutSpace;
}

void UAIMoveToActuator::TakeAction(const FBoxPoint& Action)
{
	int Offset = 0;

	APawn* LocalTarget = Target;

	if (Target == nullptr)
	{
		Target = Cast<APawn>(TryGetOwner());
	}

	if (Target != nullptr)
	{
		const FVector ActionVector = ConvertActionToAIMoveTargetLocation(Action);
		
		this->OnAIMoveToSignatureDelegate.Broadcast(ActionVector);

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Target->GetController(), ActionVector);
	}
}

FVector UAIMoveToActuator::ConvertActionToAIMoveTargetLocation(const FBoxPoint& Action)
{
	FVector OutVector;
	int		Offset = 0;
	
	if (bHasXDimension)
	{
		OutVector.X = Action[Offset];
		Offset++;
	}

	if (bHasYDimension)
	{
		OutVector.Y = Action[Offset];
		Offset++;
	}

	if (bHasZDimension)
	{
		OutVector.Z = Action[Offset];
		Offset++;
	}



	
	if(this->bClipMovementInputs)
	{
		if (bHasXDimension)
		{
			OutVector.X = FMath::Clamp(OutVector.X, MinX, MaxX);
		}

		if (bHasYDimension)
		{
			OutVector.Y = FMath::Clamp(OutVector.Y, MinY, MaxY);
		}

		if (bHasZDimension)
		{
			OutVector.Z = FMath::Clamp(OutVector.Z, MinZ, MaxZ);
		}
	}
	

	


	return  OutVector;
}

