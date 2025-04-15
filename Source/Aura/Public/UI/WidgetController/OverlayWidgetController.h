// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * this is how we Create a new dynamic delegate. with one parameter.
 * 1. Use DECLARE_DYNAMIC_MULTICAST_DELEGATE_With how many Params you need
 * 2. The name of the Delegate followed with Signature
 * 3. type of the Params separated by a coma
 * 4. the name of that param
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	/*
	 * Function Declarations
	 */
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependancies() override;

	/*
	 * Variables Declarations
	 */
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FOnHealthChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FOnMaxManaChangedSignature OnMaxManaChanged;
	
	

protected:
	/*
	 *Functions Declarations 
	 */
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
