// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PFDefaultPawn.generated.h"

class UCameraComponent;

class UGrid;
class UStartWidget;
class USettingsWidget;



enum class EGridSettings : uint8;


// What are we going to do next?
UENUM()
enum class EClickingState : uint8
{

	Start,
	End

};

UCLASS()
class PATHFINDING_API APFDefaultPawn : public APawn
{
	GENERATED_BODY()

	friend class UStartWidget;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent * CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MouseMoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MouseClickAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MouseRightAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* MouseInputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStartWidget> StartWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<USettingsWidget> SettingsWidgetClass;

protected:

	UPROPERTY(VisibleAnywhere, Category = "A* Grid")
	UGrid *Grid;

	EClickingState State;

	EGridSettings GridSettings;

	int32 StartIndexX; 
	int32 StartIndexY;

	int32 FinishIndexX; 
	int32 FinishIndexY;

	int32 NodeSizeInViewportX;
	int32 NodeSizeInViewportY;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	bool HasGameStarted;

public:
	// Sets default values for this pawn's properties
	APFDefaultPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	void SetupPathFinding();

public:
	
	void OnGameStarted();

	UFUNCTION()
	void ClickMouse();

	UFUNCTION()
	void RightClickMouse();

	FORCEINLINE void SetSettings(EGridSettings NewGridSettings)
	{
		GridSettings = NewGridSettings;
	}

};
