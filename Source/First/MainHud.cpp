// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHud.h"


void UMainHud::BindHp(class UMyStatsComponent* StatComp)
{
	CurrentStatComp = StatComp;
	StatComp->OnHpChanged.AddUObject(this, &UMyCharacerHpWidget::UpdateHp);
}

void UMainHud::UpdateHp()
{
	if (CurrentStatComp.IsValid())
	{
		PB_HpBar->SetPercent(CurrentStatComp->GetHpRatio());
	}
}