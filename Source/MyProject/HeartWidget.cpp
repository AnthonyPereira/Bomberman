// Fill out your copyright notice in the Description page of Project Settings.


#include <Components/Image.h>
#include "HeartWidget.h"

void UHeartWidget::Hide()
{
	HeartImage->Visibility = ESlateVisibility::Hidden;
}
