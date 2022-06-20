// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHud.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UMainHud : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindHp(class UMyStatsComponent* StatComp);

	void UpdateHp();

	void InitializeComponent();

private:
	TWeakObjectPtr<class UMyStatsComponent> CurrentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HPGauge;


	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_MPGauge;

};
