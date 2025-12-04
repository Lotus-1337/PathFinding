// Fill out your copyright notice in the Description page of Project Settings.


#include "PFDefaultPawn.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Grid.h"
#include "NodesHUD.h"

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

	FVector2D GridSize = FVector2D(32, 18);

	Grid->CreateGrid(GridSize, FVector::ZeroVector);


	FTransform NewTransform = FTransform(FRotator(-90.0f, -90.0f, 0.0f), FVector(0.0f, 0.0f, 970.0f), FVector::OneVector);

	SetActorTransform(NewTransform);

	StartIndexX = 0;
	StartIndexY = 0;

	FinishIndexX = 0;
	FinishIndexY = 0;

	State = EClickingState::Start;

	APlayerController* PC = Cast<APlayerController>(Controller);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller is invalid. APFDefaultPawn::BeginPlay"));
		return;
	}

	ANodesHUD* NodesHUD = Cast<ANodesHUD>(PC->GetHUD());

	if (!NodesHUD)
	{
		UE_LOG(LogTemp, Error, TEXT("Nodes HUD is invalid. APFDefaultPawn::BeginPlay"));
		return;
	}

	int32 ViewportSizeX;
	int32 ViewportSizeY;
	PC->GetViewportSize(ViewportSizeX, ViewportSizeY);

	UE_LOG(LogTemp, Warning, TEXT("Viewport Size: X: %d | Y: %d"), ViewportSizeX, ViewportSizeY);

	//	How many Nodes Per ViewportSize? 
	NodeSizeInViewportX = ViewportSizeX / Grid->GetGridSize().X;
	NodeSizeInViewportY = ViewportSizeY / Grid->GetGridSize().Y;

	NodesHUD->SetNodeSize(NodeSizeInViewportX, NodeSizeInViewportY);

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


	EIC->BindAction(MouseClickAction, ETriggerEvent::Started, this, &APFDefaultPawn::ClickMouse);
	 
	FInputModeGameAndUI InputMode;

	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);

	PC->SetInputMode(InputMode);

	PC->SetShowMouseCursor(true);
}

void APFDefaultPawn::ClickMouse()
{


	SetupPathFinding();

	TArray<FNode> Arr = Grid->FindPath(StartIndexX, StartIndexY, FinishIndexX, FinishIndexY);

	for (FNode& Node : Arr)
	{

		UE_LOG(LogTemp, Log, TEXT("Node Loc: %s | Node X: %d | Node Y: %d "), *Node.GetLocation().ToString(), Node.IndexX, Node.IndexY);

	}

	APlayerController* PC = Cast<APlayerController>(Controller);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller is invalid. APFDefaultPawn::ClickMouse"));
		return;
	}

	ANodesHUD* NodesHUD = Cast<ANodesHUD>(PC->GetHUD());

	if (!NodesHUD)
	{
		UE_LOG(LogTemp, Error, TEXT("Nodes HUD is invalid. APFDefaultPawn::ClickMouse"));
		return;
	}

	NodesHUD->SetNodesArray(MoveTemp(Arr));

}

void APFDefaultPawn::SetupPathFinding()
{
	APlayerController* PC = Cast<APlayerController>(Controller);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller is invalid. APFDefaultPawn::ClickMouse"));
		return;
	}

	float MousePositionX;
	float  MousePositionY;

	PC->GetMousePosition(MousePositionX, MousePositionY);


	if (State == EClickingState::Start)
	{
		
		StartIndexX = MousePositionX / NodeSizeInViewportX;
		StartIndexY = MousePositionY / NodeSizeInViewportY;

		UE_LOG(LogTemp, Log, TEXT("StartNode : %d, %d"), StartIndexX, StartIndexY);
		State = EClickingState::End;

	}
	else if (State == EClickingState::End)
	{

		FinishIndexX = MousePositionX / NodeSizeInViewportX;
		FinishIndexY = MousePositionY / NodeSizeInViewportY;

		UE_LOG(LogTemp, Log, TEXT("FinishNode : %d, %d"), FinishIndexX, FinishIndexY);
		State = EClickingState::Start;

	}
}