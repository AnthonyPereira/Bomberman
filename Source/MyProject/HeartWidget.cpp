// Fill out your copyright notice in the Description page of Project Settings.

#include "HeartWidget.h"

#include <Components/Image.h>

void UHeartWidget::Hide()
{
	HeartImage->Visibility = ESlateVisibility::Hidden;
}
