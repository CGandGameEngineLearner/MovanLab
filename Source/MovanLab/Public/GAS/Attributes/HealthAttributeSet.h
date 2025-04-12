// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MovanLabAttributeSet.h"
#include "HealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MOVANLAB_API UHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UHealthAttributeSet();

private:
	// 生命值属性
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	// 最大生命值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

public:
	// 使用 ATTRIBUTE_ACCESSORS 宏生成访问器函数
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health);

	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth);

	// 生命值发生改变时广播
	mutable FAttributeEvent OnHealthChanged;

	// 生命值为零时广播
	mutable FAttributeEvent OnOutOfHealth;


private:
	bool bOutOfHealth = false;

protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
};