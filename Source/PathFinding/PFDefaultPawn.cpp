// Fill out your copyright notice in the Description page of Project Settings.


#include "PFDefaultPawn.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
APFDefaultPawn::APFDefaultPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject < UCameraComponent>(TEXT("Camera Component"));

}

// Called when the game starts or when spawned
void APFDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APFDefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APFDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PC = Cast<APlayerController>(Controller);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller is invalid."));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	if (!Subsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Subsystem is invalid. "));
		return;
	}

	Subsystem->AddMappingContext(MouseInputMapping, 0);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!EIC)
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component is invalid. "));
		return;
	}


	EIC->BindAction(MouseMoveAction, ETriggerEvent::Triggered, this, &APFDefaultPawn::MoveMouse);
	EIC->BindAction(MouseClickAction, ETriggerEvent::Triggered, this, &APFDefaultPawn::ClickMouse);
	 
	FInputModeGameAndUI InputMode;

	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);

	PC->SetInputMode(InputMode);
}

void APFDefaultPawn::MoveMouse()
{

}

void APFDefaultPawn::ClickMouse()
{

}
