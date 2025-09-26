// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadScreen.generated.h"

class UMVVM_LoadSlot;
/**
 * 
 */
UCLASS()
class AURA_API UMVVM_LoadScreen : public UMVVMViewModelBase
{
	GENERATED_BODY()


public:
	void InitializeLoadSlot();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot> LoadSlotViewModelClass;

	UFUNCTION(BlueprintPure, Category = "View Model")
	UMVVM_LoadSlot* GetLoadSlotViewModelByIndex(int32 Index) const;

private:

	UPROPERTY()
	TMap<int32, UMVVM_LoadSlot*> LoadSlots;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_0;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_1;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_2;
};
