// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"

#include "Kismet/KismetSystemLibrary.h"
#include "SettingsWidget.h"

#include "PFDefaultPawn.h"

bool UStartWidget::Initialize()
{

	Super::Initialize();

	StartButton->OnClicked.AddDynamic(this, &UStartWidget::Start);

	SettingsButton->OnClicked.AddDynamic(this, &UStartWidget::ShowSettings);

	ExitButton->OnClicked.AddDynamic(this, &UStartWidget::Exit);

	return true;
	
}

void UStartWidget::Start()
{
	if (!Pawn)
	{
		return;
	}

	Pawn->OnGameStarted();

}

void UStartWidget::ShowSettings()
{

	if (!Pawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn is invalid. "));
		return;
	}

	USettingsWidget* SettingsWidget = CreateWidget<USettingsWidget>(Pawn->GetWorld(), Pawn->SettingsWidgetClass);

	if (!SettingsWidget)
	{
		return;
	}

	SetVisibility(ESlateVisibility::Collapsed);

	SettingsWidget->SetPawn(Pawn);
	SettingsWidget->SetStartWidget(this);


}

void UStartWidget::Exit()
{

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (!PC)
	{
		return;
	}

	UKismetSystemLibrary::QuitGame(PC, PC, EQuitPreference::Quit, true);

}