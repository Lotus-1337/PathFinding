// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/CheckBox.h"

#include "SettingsWidget.generated.h"

class UVerticalBox;
class UButton;
class UCheckBox;

class APFDefaultPawn;

/**
 * 
 */
UCLASS()
class PATHFINDING_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* OptionsBox;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* EuclideanCheckBox;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* GreedyCheckBox;

	UPROPERTY(VisibleAnywhere, Category = "Pawn")
	APFDefaultPawn* Pawn;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	UStartWidget* StartWidget;

public:

	FORCEINLINE void SetStartWidget(UStartWidget* NewStartWidget)
	{
		StartWidget = NewStartWidget;
	}

	FORCEINLINE void SetPawn(APFDefaultPawn* NewPawn)
	{
		Pawn = NewPawn;
	}

	UFUNCTION()
	void OnEuclideanCheckChanged(bool bIsChecked);

	UFUNCTION()
	void OnGreedyCheckChanged(bool bIsChecked);

	UFUNCTION()
	void OnGoBackToMainMenu();

	void SetSettings(const bool& IsEucChecked, const bool& IsGreedyChecked);


};
