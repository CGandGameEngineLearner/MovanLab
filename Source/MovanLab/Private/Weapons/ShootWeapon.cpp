// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ShootWeapon.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"


AShootWeapon::AShootWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShootMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MuzzleMesh"));
}

void AShootWeapon::Fire_Implementation()
{
	UAnimInstance* AnimInstance = ShootMeshComponent->GetAnimInstance();
	AnimInstance->Montage_Play(ShootMontage);
	
	// todo: 射击

	FTrajectory Trajectory = ComputeTrajectory_Implementation();

	if (!ShootWeaponFire||ShootWeaponFire->IsPendingKillPending())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		ShootWeaponFire = GetWorld()->SpawnActor<AShootWeaponFire>(WeaponFireActorClass,SpawnParams);
	}
	ShootWeaponFire->Fire(Trajectory);
}

void AShootWeapon::CheckFire_Implementation()
{
	if (!bFiring)
	{
		return;
	}
	UAnimInstance* AnimInstance = ShootMeshComponent->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}
	
	
	// 检查是否有蒙太奇正在播放
	if (AnimInstance->Montage_IsPlaying(nullptr))
	{
		return;
	}

	
	IShootInterface::Execute_Fire(this);
	
}

FTrajectory AShootWeapon::ComputeTrajectory_Implementation()
{
	FTrajectory Result;
	Result.ShootMeshComponent = ShootMeshComponent;
	
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

		
		Result.StartPosition = ShootMeshComponent->GetSocketLocation(MuzzleSocketName);

		// 将屏幕点转换为射线起点与方向
		if (PC->DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection))
		{
			
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

				Result.ImpactCharacter = Cast<ACharacter>(HitResult.GetActor());

			}
		}
		
	}
	
	return Result;
}

void AShootWeapon::StartAttack_Implementation()
{
	bFiring = true;
	
}

void AShootWeapon::EndAttack_Implementation()
{
	bFiring = false;

	
	
	
}

void AShootWeapon::Equip_Implementation(ACharacter* InOwner, FName AttachSocketName)
{
	Super::Equip_Implementation(InOwner, AttachSocketName);

	if (OwnerAbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		SpecHandle = OwnerAbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(ShootAbilityClass, 1, 0));
		OwnerAbilitySystemComponent->InitAbilityActorInfo(OwnerCharacter, OwnerCharacter);
	}
	
}

void AShootWeapon::UnEquip_Implementation()
{
	Super::UnEquip_Implementation();
	
	if (SpecHandle.IsValid())
	{
		// 移除指定技能
		OwnerAbilitySystemComponent->ClearAbility(SpecHandle);
	}

}


// Called when the game starts or when spawned
void AShootWeapon::BeginPlay()
{
	Super::BeginPlay();
	MuzzleSocket = ShootMeshComponent->GetSocketByName("Muzzle");
	checkf(MuzzleSocket, TEXT("MuzzleSocket not found"));
	ShellEjectSocket = ShootMeshComponent->GetSocketByName("ShellEject");
	checkf(ShellEjectSocket, TEXT("ShellEjectSocket not found"));
}

// Called every frame
void AShootWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFire();
}

