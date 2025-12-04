// Fill out your copyright notice in the Description page of Project Settings.


#include "NodesHUD.h"

#include "Grid.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"

void ANodesHUD::SetNodesArray(TArray<FNode>&& NewArr)
{

	NodesArray = NewArr;

}

void ANodesHUD::SetNodeSize(const float& X, const float& Y)
{

	NodeSizeX = X;
	NodeSizeY = Y;

}


void ANodesHUD::DrawHUD()
{

	Super::DrawHUD();


	if (!Canvas)
	{
		UE_LOG(LogTemp, Error, TEXT("Canvas is invalid. "));
		return;
	}

	FLinearColor Color = FLinearColor::Green;

	int32 Index = 0;
	int32 LastIndex = NodesArray.Num() - 1;

	for (FNode& Node : NodesArray)
	{

		if (Index == 0 || Index == LastIndex)
		{
			Color = FLinearColor::Blue;
		}

		float X = Node.IndexX * NodeSizeX;
		float Y = Node.IndexY * NodeSizeY;

		DrawRect(Color, X, Y, NodeSizeX, NodeSizeY);


	}

}