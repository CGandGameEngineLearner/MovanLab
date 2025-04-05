// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FiringWeapon.h"

#include "GameFramework/Character.h"


AFiringWeapon::AFiringWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MuzzleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MuzzleMesh"));

	MuzzleArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("MuzzleArrow"));
}

FTrajectory AFiringWeapon::ComputeTrajectory_Implementation()
{
	FTrajectory Result;
	if (!OwnerCharacter)
	{
		return Result;
	}

	APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController());
	if (PC)
	{
		FVector WorldLocation;
		FVector WorldDirection;

		// 获取屏幕中心点
		int32 ViewportSizeX, ViewportSizeY;
		PC->GetViewportSize(ViewportSizeX, ViewportSizeY);
		FVector2D ScreenCenter(ViewportSizeX / 2.f, ViewportSizeY / 2.f);

		// 将屏幕点转换为射线起点与方向
		if (PC->DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection))
		{
			Result.StartPosition = WorldLocation;
			
			FHitResult HitResult;
			FVector TraceEnd = WorldLocation + WorldDirection * 10000.f;

			Result.ImpactPosition = TraceEnd;

			FCollisionQueryParams Params;
			Params.AddIgnoredActor(OwnerCharacter);

			bool bHit = OwnerCharacter->GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, TraceEnd, ECC_Visibility, Params);

			if (bHit)
			{
				// 命中逻辑
				// 命中点坐标
				Result.ImpactPosition = HitResult.ImpactPoint;

				// 命中表面法向量
				Result.ImpactNormal = HitResult.ImpactNormal;

				Result.ImpactSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());

				if (bDrawDebugLine)
				{
					DrawDebugLine(OwnerCharacter->GetWorld(), WorldLocation, HitResult.ImpactPoint, FColor::Red, false, 1.0f, 0, 1.0f);
					DrawDebugPoint(OwnerCharacter->GetWorld(), HitResult.ImpactPoint, 10.f, FColor::Green, false, 1.0f);
					DrawDebugDirectionalArrow(OwnerCharacter->GetWorld(), HitResult.ImpactPoint, HitResult.ImpactPoint + HitResult.ImpactNormal * 100.f, 100.f, FColor::Blue, false, 1.0f, 0, 2.0f);
				}


			}
		}
		
	}
	
	return Result;
}

void AFiringWeapon::StartAttack_Implementation()
{
	bFiring = true;
	
}

void AFiringWeapon::EndAttack_Implementation()
{
	bFiring = false;
}

void AFiringWeapon::Equip_Implementation(ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
}

void AFiringWeapon::UnEquip_Implementation()
{
	OwnerCharacter = nullptr;
}


// Called when the game starts or when spawned
void AFiringWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFiringWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

