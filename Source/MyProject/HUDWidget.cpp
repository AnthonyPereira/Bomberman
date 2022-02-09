// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "HeartWidget.h"

#include <Components/ProgressBar.h>
#include <Components/WrapBox.h>


void UHUDWidget::UpdateHealthPercent(float HealthPercent)
{
	HealthBar->SetPercent(1-HealthPercent);
}

void UHUDWidget::UpdateHealthBar(int current) {
	HeartBar->GetAllChildren()[current]->SetVisibility(ESlateVisibility::Hidden);
}
