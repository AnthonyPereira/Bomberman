// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectPlayerController.h"
#include "RestartWidget.h"
#include "HUDWidget.h"




void AMyProjectPlayerController::ShowRestartWidget()
{
	
	if (BP_RestartWidget != nullptr) {
		if (HUDWidget != nullptr) {
			HUDWidget->RemoveFromParent();
			HUDWidget->Destruct();
		}

		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		RestartWidget = CreateWidget<URestartWidget>(this, BP_RestartWidget);
		RestartWidget->AddToViewport();
		
	}
}

void AMyProjectPlayerController::HideRestartWidget()
{
	if (RestartWidget != nullptr)
	{
		RestartWidget->RemoveFromParent();
		RestartWidget->Destruct();
		SetPause(false);
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void AMyProjectPlayerController::UpdateHUDWidget(int Health)
{
	if (HUDWidget != nullptr) {
		HUDWidget->UpdateHealthBar(Health);
	}
}

void AMyProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (BP_HUDWidget != nullptr) {
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		HUDWidget->AddToViewport();
	}
}
