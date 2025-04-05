// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MovanLabAttributeSet.h"
#include "ShooterAttributeSet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MOVANLAB_API UShooterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UShooterAttributeSet();

	// 生命值属性
	UPROPERTY(BlueprintReadOnly, Category = "Shoot|Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;

	// 使用 ATTRIBUTE_ACCESSORS 宏生成访问器函数
	ATTRIBUTE_ACCESSORS(UShooterAttributeSet, Health);

protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);
};