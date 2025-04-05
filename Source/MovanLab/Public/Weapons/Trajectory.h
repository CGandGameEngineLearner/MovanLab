#pragma once

#include "CoreMinimal.h"

#include "Trajectory.generated.h"

USTRUCT(BlueprintType)
struct MOVANLAB_API FTrajectory
{
	GENERATED_BODY()

	/** 是否开启蛋壳抛出特效 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShellEjectTrigger = true;

	/** 是否开启枪口火焰特效 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bMuzzleFlashTrigger = true;

	/** 是否开启弹道特效 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTracerTrigger = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ImpactPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ImpactNormal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EPhysicalSurface> ImpactSurfaceType;
	
};
