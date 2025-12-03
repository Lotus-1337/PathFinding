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

	FLinearColor Color = FLinearColor::Red;

	for (FNode& Node : NodesArray)
	{

		float X = Node.IndexX * NodeSizeX;
		float Y = Node.IndexY * NodeSizeY;

		DrawRect(Color, X, Y, NodeSizeX, NodeSizeY);

	}

}