// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/ShootAbility.h"

#include "AbilitySystemComponent.h"

UShootAbility::UShootAbility()
{
	// 设置能力的激活方式
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UShootAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 假设这里已经获取到了目标的 AbilitySystemComponent
	UAbilitySystemComponent* TargetASC = nullptr; // 替换为实际的目标 ASC

	if (TargetASC && DamageEffectClass)
	{
		FGameplayEffectContextHandle Context = TargetASC->MakeEffectContext();
		Context.AddSourceObject(GetOwningActorFromActorInfo());

		FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(DamageEffectClass, 1.f, Context);
		TargetASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}    