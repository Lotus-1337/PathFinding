// Fill out your copyright notice in the Description page of Project Settings.


#include "PFDefaultPawn.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Grid.h"

// Sets default values
APFDefaultPawn::APFDefaultPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject < UCameraComponent>(TEXT("Camera Component"));

}

// Called when the game starts or when spawned
void APFDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	
	Grid = NewObject<UGrid>(GetWorld());

	FVector2D GridSize = FVector2D(30, 16);

	Grid->CreateGrid(GridSize, FVector::ZeroVector);

	FNode Node;

	Node.SetLocation(FVector(-1000.0f, 1000.0f, 0.0f));
	Node.CalculateH(FVector::ZeroVector);

	UE_LOG(LogTemp, Error, TEXT("Custom Node Heuretic: %d"), Node.GetH());


	FTransform NewTransform = FTransform(FRotator(-90.0f, -90.0f, 0.0f), FVector(0.0f, 0.0f, 3520.0f), FVector::OneVector);

	SetActorTransform(NewTransform);

	StartNode  = FVector::ZeroVector;
	FinishNode = FVector::ZeroVector;

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
		UE_LOG(LogTemp, Error, TEXT("Player Controller is invalid. APFDefaultPawn::SetupPlayerInputComponent"));
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


	EIC->BindAction(MouseClickAction, ETriggerEvent::Triggered, this, &APFDefaultPawn::ClickMouse);
	 
	FInputModeGameAndUI InputMode;

	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);

	PC->SetInputMode(InputMode);

	PC->SetShowMouseCursor(true);
}

void APFDefaultPawn::ClickMouse()
{

	APlayerController* PC = Cast<APlayerController>(Controller);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller is invalid. APFDefaultPawn::ClickMouse"));
		return;
	}

	

	int32 ViewportSizeX;
	int32 ViewportSizeY;
	PC->GetViewportSize(ViewportSizeX, ViewportSizeY);

	int32 NodeSizeInViewportX = ViewportSizeX / Grid->GetGridSize().X;
	int32 NodeSizeInViewportY = ViewportSizeY / Grid->GetGridSize().Y;
	
	float MousePositionX;
	float  MousePositionY;

	PC->GetMousePosition(MousePositionX, MousePositionY);

	FVector2D ChosenNode = FVector2D(MousePositionX / NodeSizeInViewportX, MousePositionY / NodeSizeInViewportY);

	if (State == EClickingState::Start)
	{
		StartNode = FVector(ChosenNode.X, ChosenNode.Y, 0.0f);
		State = EClickingState::End;
	}
	else if (State == EClickingState::End)
	{
		FinishNode = FVector(ChosenNode.X, ChosenNode.Y, 0.0f);
		State = EClickingState::Start;
	}

	TArray<FNode*> Arr = Grid->FindPath(StartNode, FinishNode);

	for (FNode* Node : Arr)
	{

		UE_LOG(LogTemp, Log, TEXT("Node Loc: %s | Node X: %d | Node Y: %d "), *Node->GetLocation().ToString(), Node->IndexX, Node->IndexY);

	}

}
