// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ShootWeapon.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "ProjectSettings/CollisionChannels.h"


AShootWeapon::AShootWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShootMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MuzzleMesh"));
}

void AShootWeapon::Fire_Implementation()
{
	UAnimInstance* AnimInstance = ShootMeshComponent->GetAnimInstance();
	float PlayRate = ShootMontage->GetPlayLength() * FiringRate;
	AnimInstance->Montage_Play(ShootMontage,PlayRate);
	
	// todo: 射击

	FTrajectory Trajectory = ComputeTrajectory_Implementation();

	if (!ShootWeaponFire||ShootWeaponFire->IsPendingKillPending())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		ShootWeaponFire = GetWorld()->SpawnActor<AShootWeaponFire>(WeaponFireActorClass,SpawnParams);
	}
	ShootWeaponFire->Fire(Trajectory);

	AController* OwnerController = OwnerCharacter->GetController();

	IGenericTeamAgentInterface* OwnerGenericTeamAgentInterface = Cast<IGenericTeamAgentInterface>(OwnerController);
	if (!OwnerGenericTeamAgentInterface)
	{
		return;
	}

	if (!Trajectory.ImpactActor)
	{
		return;
	}
	

	if (OwnerGenericTeamAgentInterface->GetTeamAttitudeTowards(*Trajectory.ImpactActor) == ETeamAttitude::Type::Friendly)
	{
		return;
	}
	
	
	if (IAbilitySystemInterface* TargetASInterface = Cast<IAbilitySystemInterface>(Trajectory.ImpactActor))
	{
		
		if (UAbilitySystemComponent* TargetASC = TargetASInterface->GetAbilitySystemComponent())
		{
			
			// 1. 创建效果上下文
			FGameplayEffectContextHandle EffectContextHandle = OwnerAbilitySystemComponent->MakeEffectContext();

			// 2. 设置Instigator和EffectCauser
			AActor* OwnerActor = OwnerAbilitySystemComponent->GetAvatarActor();
			AActor* InstigatorActor = OwnerActor;
			AActor* CauserActor = this;
			
			

			EffectContextHandle.AddInstigator(InstigatorActor, CauserActor);
			EffectContextHandle.Get()->SetEffectCauser(CauserActor);

			// 3. 创建效果规格
			GameplayEffectSpecHandle = OwnerAbilitySystemComponent->MakeOutgoingSpec(
				GameplayEffectClass, WeaponLevel, EffectContextHandle);

			// 4. 应用效果到目标
			if (GameplayEffectSpecHandle.IsValid())
			{
				OwnerAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(), TargetASC);
				OnHitDelegate.Broadcast(Trajectory.ImpactActor);
			}

			
		}
	}
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

	FVector WorldLocation = ShootMeshComponent->GetSocketLocation(MuzzleSocketName);
	FVector WorldDirection;
	FVector TraceEnd;
	Result.StartPosition = ShootMeshComponent->GetSocketLocation(MuzzleSocketName);
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);
	
	if (APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController()))
	{
		
		// 获取屏幕中心点
		int32 ViewportSizeX, ViewportSizeY;
		PC->GetViewportSize(ViewportSizeX, ViewportSizeY);
		FVector2D ScreenCenter(ViewportSizeX / 2.f, ViewportSizeY / 2.f);

		// 将屏幕点转换为射线起点与方向
		if (PC->DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection))
		{
			
			TraceEnd = WorldLocation + WorldDirection * ShootRange;

			Result.ImpactPosition = TraceEnd;
		}
		
	}
	else
	{
		FVector OutLocation;
		FRotator OutRotation;
		ShootMeshComponent->GetSocketWorldLocationAndRotation(MuzzleSocketName, OutLocation, OutRotation);
		WorldDirection = OutRotation.RotateVector(FVector::UnitX());
		TraceEnd = WorldLocation + WorldDirection * ShootRange;
		Result.ImpactPosition = TraceEnd;
		
	}
	
	bool bHit = OwnerCharacter->GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, TraceEnd, ECC_ShootWeaponTrajectory, Params);

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

		Result.ImpactActor = HitResult.GetActor();

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
		GameplayAbilitySpecHandle = OwnerAbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(ShootAbilityClass, 1, 0));
		OwnerAbilitySystemComponent->InitAbilityActorInfo(OwnerCharacter, OwnerCharacter);
	}
}

void AShootWeapon::UnEquip_Implementation()
{
	Super::UnEquip_Implementation();
	
	if (GameplayAbilitySpecHandle.IsValid())
	{
		// 移除指定技能
		OwnerAbilitySystemComponent->ClearAbility(GameplayAbilitySpecHandle);
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

