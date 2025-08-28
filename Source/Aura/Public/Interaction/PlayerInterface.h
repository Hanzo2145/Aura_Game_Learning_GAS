// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"


UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IPlayerInterface
{
	GENERATED_BODY()

	
public:

	UFUNCTION(BlueprintNativeEvent)
	void AddToXP(int32 InXP);

	UFUNCTION(BlueprintNativeEvent)
	void AddToPlayerLevel(const int32 InPlayerLevel);

	UFUNCTION(BlueprintNativeEvent)
	void AddToAttributesPoints(const int32 InAttributesPoints);

	UFUNCTION(BlueprintNativeEvent)
	void AddToSpellPoints(const int32 InSpellPoints);

	UFUNCTION(BlueprintNativeEvent)
	int32 GetXP() const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetAttributesPointsRewards(const int32 InLevel) const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetSpellPointsRewards(const int32 InLevel) const;

	UFUNCTION(BlueprintNativeEvent)
	int32 FindLevelForXP(const int32 InXP);

	UFUNCTION(BlueprintNativeEvent)
	int32 GetAttributesPoints() const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetSpellPoints() const;

	UFUNCTION(BlueprintNativeEvent)
	void LevelUp();
};
