// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"


class AActor;
class UObject;
class UWorld;
struct FGameplayEffectSpec;


/**
 * 此宏定义了用于访问和初始化属性的帮助程序函数。
 *
 * 示例:
 *		ATTRIBUTE_ACCESSORS(UMovanLabHealthSet, Health)
 * 这相当于创建了以下函数:
 *		static FGameplayAttribute GetHealthAttribute();
 *		float GetHealth() const;
 *		void SetHealth(float NewVal);
 *		void InitHealth(float NewVal);
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



/**
* 用于广播属性事件的 delegate，其中一些参数在客户端上可能为 null：
* @param EffectInstigator 此事件的原始煽动 Actor
* @param EffectCauser 导致更改的物理 actor
* @param EffectMagnitude 原始幅值，这是在钳制之前
* @param OldValue 更改前的属性值
* @param NewValue 更改后的值
*/
DECLARE_MULTICAST_DELEGATE_FiveParams(FAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/, float /*EffectMagnitude*/, float /*OldValue*/, float /*NewValue*/);

