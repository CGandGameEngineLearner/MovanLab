#pragma once

#include "CoreMinimal.h"

#include "Trajectory.generated.h"

USTRUCT(BlueprintType)
struct MOVANLAB_API FTrajectory
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ImpactPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ImpactNormal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EPhysicalSurface> ImpactSurfaceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ACharacter> ImpactCharacter = nullptr;
};
