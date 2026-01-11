// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWidget.h"

#include "PFDefaultPawn.h"
#include "Grid.h"

#include "StartWidget.h"

bool USettingsWidget::Initialize()
{

	Super::Initialize();

	EuclideanCheckBox->OnCheckStateChanged.AddDynamic(this, &USettingsWidget::OnEuclideanCheckChanged);

	GreedyCheckBox->OnCheckStateChanged.AddDynamic(this, &USettingsWidget::OnGreedyCheckChanged);

	return true;

}

void USettingsWidget::OnEuclideanCheckChanged(bool bIsChecked)
{
	
	bool IsGreedyChecked = GreedyCheckBox->GetCheckedState() == ECheckBoxState::Checked;

	SetSettings(bIsChecked, IsGreedyChecked);

}

void USettingsWidget::OnGreedyCheckChanged(bool bIsChecked)
{

	bool IsEucChecked = EuclideanCheckBox->GetCheckedState() == ECheckBoxState::Checked;

	SetSettings(IsEucChecked, bIsChecked);

}

void USettingsWidget::OnGoBackToMainMenu()
{

	if (!StartWidget)
	{
		return;
	}

	StartWidget->SetVisibility(ESlateVisibility::Visible);

	RemoveFromParent();

}

void USettingsWidget::SetSettings(const bool& IsEucChecked, const bool& IsGreedyChecked)
{

	if (IsEucChecked && IsGreedyChecked)
	{
		Pawn->SetSettings(EGridSettings::GREEDY_EUCLIDEAN);
	}
	else if (IsEucChecked)
	{
		Pawn->SetSettings(EGridSettings::EUCLIDEAN);
	}
	else if (IsGreedyChecked)
	{
		Pawn->SetSettings(EGridSettings::GREEDY);
	}
	else
	{
		Pawn->SetSettings(EGridSettings::NORMAL);
	}

}