// Copyright Anas Hanzo Al-Juboori


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


AAuraPlayerState::AAuraPlayerState()
{
	//Constructing the Ability System and the Attribute Set
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	/***************************************/
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("Attribute Set");

	// how Often the server will update clients
	SetNetUpdateFrequency(100.F);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
