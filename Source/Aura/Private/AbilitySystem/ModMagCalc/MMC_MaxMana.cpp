// Copyright Anas Hanzo Al-Juboori


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligeceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligeceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligeceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligeceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Intelligece = 0.f;
	GetCapturedAttributeMagnitude(IntelligeceDef, Spec, EvaluationParameters, Intelligece);
	Intelligece = FMath::Max<float>(Intelligece, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 50.f + (2.5 * Intelligece) + (15.f * PlayerLevel);
}
