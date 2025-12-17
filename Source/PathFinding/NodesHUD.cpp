// Fill out your copyright notice in the Description page of Project Settings.


#include "NodesHUD.h"

#include "Grid.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"

void ANodesHUD::SetNodesArray(TArray<FNode>& NewArr)
{

	NodesArray = NewArr;

}

void ANodesHUD::SetBlockedNodesArray(TArray<FNode>& NewArr)
{
	BlockedNodesArray = NewArr;
}

void ANodesHUD::AddBlockedNode(const FNode& NewBlockedNode)
{
	BlockedNodesArray.Add(NewBlockedNode);
}

void ANodesHUD::SetNodeSize(const float& X, const float& Y)
{

	NodeSizeX = X;
	NodeSizeY = Y;

}


void ANodesHUD::DrawHUD()
{

	Super::DrawHUD();

	DrawGrid();

	if (!Canvas)
	{
		UE_LOG(LogTemp, Error, TEXT("Canvas is invalid. "));
		return;
	}

	FLinearColor Color = Color = FLinearColor::Green;

	int32 Index = 0;
	int32 LastIndex = NodesArray.Num() - 1;

	for (FNode& Node : NodesArray)
	{

		if (Index == 0 || Index == LastIndex)
		{
			Color = FLinearColor::Green;
		}
		else
		{
			Color = FLinearColor::Blue;
		}

		float X = Node.IndexX * NodeSizeX;
		float Y = Node.IndexY * NodeSizeY;

		DrawRect(Color, X, Y, NodeSizeX, NodeSizeY);

		Index++;

	}

	for (FNode& BlockedNode : BlockedNodesArray)
	{
		float X = BlockedNode.IndexX * NodeSizeX;
		float Y = BlockedNode.IndexY * NodeSizeY;
		DrawRect(FLinearColor::Gray, X, Y, NodeSizeX, NodeSizeY);
	}

}

void ANodesHUD::DrawGrid()
{

	if (!Canvas)
	{
		UE_LOG(LogTemp, Error, TEXT("Canvas is Invalid. ANodesHUD::DrawGrid()"));
		return;
	}

	for (int32 X = NodeSizeX; X <= Canvas->SizeX; X += NodeSizeX)
	{
		DrawLine(X, 0.0f, X, Canvas->SizeY, FLinearColor::White);
	}

	for (int32 Y = NodeSizeY; Y <= Canvas->SizeY; Y += NodeSizeY)
	{
		DrawLine(0.0f, Y, Canvas->SizeX, Y, FLinearColor::White);
	}

}