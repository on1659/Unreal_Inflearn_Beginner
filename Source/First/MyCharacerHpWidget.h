// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacerHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UMyCharacerHpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindHp(class UMyStatsComponent* StatComp);

	void UpdateHp();

private:
	TWeakObjectPtr<class UMyStatsComponent> CurrentStatComp;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* PB_HpBar;
};
 