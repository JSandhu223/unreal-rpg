#include "AbilitySystem/AuraAbilitySystemComponent.h"

// Gets called when when ability actor info is set on AuraCharacter and AuraEnemy
void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	// Bind this delegate from the 'AbilitySystemComponent' parent class to our callback
	// This delegate triggers when a gameplay effect is applied
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	// The Widget Controller will bind to this delegate and receive the asset tag container
	this->EffectAssetTags.Broadcast(TagContainer);
}
