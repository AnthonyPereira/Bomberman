// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeartWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UHeartWidget : public UUserWidget
{
	GENERATED_BODY()
	

	UPROPERTY(meta = (BindWidget))
	class UImage* HeartImage;

	void Hide();
};
