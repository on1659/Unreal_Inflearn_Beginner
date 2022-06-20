// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacerHpWidget.h"
#include "MyStatsComponent.h"
#include "Components/ProgressBar.h"

void UMyCharacerHpWidget::BindHp(class UMyStatsComponent* StatComp)
{
	CurrentStatComp = StatComp;
	if (StatComp)
	{
		StatComp->OnHpChanged.AddUObject(this, &UMyCharacerHpWidget::UpdateHp);
	}
}

void UMyCharacerHpWidget::UpdateHp()
{
	if (CurrentStatComp.IsValid())
	{
		PB_HpBar->SetPercent(CurrentStatComp->GetHpRatio());
	}
}