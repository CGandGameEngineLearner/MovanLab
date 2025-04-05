// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Abilities/GameplayAbility.h"
#include "ShootAbility.generated.h"

/**
 * 
 */
UCLASS()
class MOVANLAB_API UShootAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UShootAbility();

	// 伤害效果类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};