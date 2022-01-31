// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartWidget.h"
#include "MyProjectPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <Components/Button.h>

void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	if (RestartButton != nullptr) {
		RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartClicked);
	}

	if (QuitButton != nullptr) {
		QuitButton->OnClicked.AddDynamic(this, &URestartWidget::OnQuitClicked);
	}

}

void URestartWidget::OnRestartClicked()
{
	AMyProjectPlayerController* PlayerController = Cast<AMyProjectPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr) {
		PlayerController->HideRestartWidget();
	}
	UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
}

void URestartWidget::OnQuitClicked()
{
	AMyProjectPlayerController* PlayerController = Cast<AMyProjectPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr) {
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);

	}

}
