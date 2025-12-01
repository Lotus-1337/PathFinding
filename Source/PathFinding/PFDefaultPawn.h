// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PFDefaultPawn.generated.h"

class UCameraComponent;

UCLASS()
class PATHFINDING_API APFDefaultPawn : public APawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent * CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MouseMoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MouseClickAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* MouseInputMapping;


protected:

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

public:
	
	UFUNCTION()
	void ClickMouse();

};
