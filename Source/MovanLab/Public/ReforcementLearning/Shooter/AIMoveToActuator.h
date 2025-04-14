// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Actuators/AbstractActuators.h"

#include "AIMoveToActuator.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAIMoveToSignature, const FVector&, MovementInput);

/**
 * 
 */
UCLASS()
class MOVANLAB_API UAIMoveToActuator : public UBoxActuator
{
	GENERATED_BODY()

	
public:
	
	/** Toggle for whether this actuator moves the Agent along the X dimension */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actuator Settings")
	bool bHasXDimension = true;

	/** Toggle for whether this actuator moves the Agent along the Z dimension */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actuator Settings")
	bool bHasZDimension = true;

	/** Toggle for whether this actuator moves the Agent along the Y dimension */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actuator Settings")
	bool bHasYDimension = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actuator Settings")
	float MinX = -1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actuator Settings")
	float MaxX = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actuator Settings")
	float MinY = -1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actuator Settings")
	float MaxY = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actuator Settings")
	float MinZ = -1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actuator Settings")
	float MaxZ = 1000.0f;
	

	UPROPERTY()
	APawn* Target;

	/** Toggle for clipping agent movement to the specified Max/Min */
	UPROPERTY(EditAnywhere, Category = "Actuator Settings")
	bool bClipMovementInputs = true;

	/** A delegate invoked when this actuator receives input from a brain. Useful for debugging and logging */
	UPROPERTY(BlueprintAssignable)
	FOnAIMoveToSignature OnAIMoveToSignatureDelegate;

	virtual FBoxSpace GetActionSpace() override;

	virtual void TakeAction(const FBoxPoint& Action) override;

	FVector ConvertActionToAIMoveTargetLocation(const FBoxPoint& Action);
	
};
