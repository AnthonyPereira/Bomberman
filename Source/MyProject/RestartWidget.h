// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API URestartWidget : public UUserWidget
{
	GENERATED_BODY()
public: 
	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	virtual void NativeOnInitialized() override;

protected:
	UFUNCTION()
	void OnRestartClicked();


	UFUNCTION()
	void OnQuitClicked();
};
