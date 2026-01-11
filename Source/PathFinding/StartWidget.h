// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartWidget.generated.h"

class UVerticalBox;
class UButton;

class APFDefaultPawn;

/**
 * 
 */
UCLASS()
class PATHFINDING_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* OptionsBox;

	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(VisibleAnywhere, Category = "Pawn")
	APFDefaultPawn* Pawn;

public:

	UFUNCTION()
	void Start();

	UFUNCTION()
	void ShowSettings();

	UFUNCTION()
	void Exit();

	FORCEINLINE void SetPawn(APFDefaultPawn* NewPawn)
	{
		Pawn = NewPawn;
	}


};
