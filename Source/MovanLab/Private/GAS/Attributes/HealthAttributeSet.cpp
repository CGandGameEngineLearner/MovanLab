#include "GAS/Attributes/HealthAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"


UHealthAttributeSet::UHealthAttributeSet()
	: Health(100.f)
{
}

void UHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, 100.f);
	}
}

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer& TargetTags = *Data.EffectSpec.CapturedTargetTags.GetAggregatedTags();

	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags);
	
	

	// 处理生命值变化
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

		// 当前值已经是修改后的值
		float CurrentHealth = GetHealth();
        
		// 使用 Data.EvaluatedData.Magnitude 获取本次修改的变化量
		// 变化量为正表示增加，为负表示减少
		float ChangeAmount = Data.EvaluatedData.Magnitude;
        
		// 计算旧值 = 当前值 - 变化量
		float OldHealth = CurrentHealth - ChangeAmount;

		// 获取效果源（施加效果的对象）
		UAbilitySystemComponent* SourceASC = Data.EffectSpec.GetEffectContext().GetOriginalInstigatorAbilitySystemComponent();

		// 获取效果源的控制器
		AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;

		const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();

		AActor* DamageCauser = EffectContext.GetEffectCauser();

		// 属性已更改，触发相应事件
		OnHealthChanged.Broadcast(SourceActor, DamageCauser, ChangeAmount, OldHealth, CurrentHealth);
        
		// 检查生命值是否为零
		if (GetHealth() <= 0.0f && !bOutOfHealth)
		{
			bOutOfHealth = true;
			OnOutOfHealth.Broadcast(SourceActor, DamageCauser, ChangeAmount, OldHealth, CurrentHealth);
		}
		else if (GetHealth() > 0.0f)
		{
			bOutOfHealth = false;
		}
	}

	
}

void UHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, Health, OldValue);


}

void UHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
}    