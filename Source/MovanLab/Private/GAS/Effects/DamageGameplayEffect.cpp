// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/DamageGameplayEffect.h"

#include "GAS/Attributes/HealthAttributeSet.h"

UDamageGameplayEffect::UDamageGameplayEffect()

{
	// 设置效果的持续时间为瞬间
	DurationPolicy = EGameplayEffectDurationType::Instant;

	// 创建一个修改生命值的 Modifier
	FGameplayModifierInfo ModifierInfo;
	ModifierInfo.Attribute = UHealthAttributeSet::GetHealthAttribute();
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;
	ModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(-10.f)); // 每次射击减少 10 点生命值

	Modifiers.Add(ModifierInfo);
}    