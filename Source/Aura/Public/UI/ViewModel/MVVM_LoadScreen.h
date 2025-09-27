// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotSelected);

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

	UPROPERTY(BlueprintAssignable)
	FSlotSelected SlotSelected;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot> LoadSlotViewModelClass;

	UFUNCTION(BlueprintPure, Category = "View Model")
	UMVVM_LoadSlot* GetLoadSlotViewModelByIndex(int32 Index) const;

	UFUNCTION(BlueprintCallable, Category = "View Model | Buttons")
	void NewSlotButtonPressed(int32 Slot, const FString& EnteredName);

	UFUNCTION(BlueprintCallable, Category = "View Model | Buttons")
	void NewGameButtonPressed(int32 Slot);
	
	UFUNCTION(BlueprintCallable, Category = "View Model | Buttons")
	void SelectSlotButtonPressed(int32 Slot);

	UFUNCTION(BlueprintCallable, Category = "View Model | Buttons")
	void DeleteButtonPressed();

	UFUNCTION(BlueprintCallable, Category = "View Model | Buttons")
	void PlayButtonPressed();
	
	void LoadData();

	//NumLoadSlots
	void SetNumLoadSlots(int32 InNumLoadSlots);
	int32 GetNumLoadSlots() const {return NumLoadSlots;}
private:

	UPROPERTY()
	TMap<int32, UMVVM_LoadSlot*> LoadSlots;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_0;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_1;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> LoadSlot_2;

	UPROPERTY()
	UMVVM_LoadSlot* SelectedSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess = "true"))
	int32 NumLoadSlots;
};
