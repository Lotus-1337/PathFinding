// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

FVector2D FNode::NodeSize = FVector2D(100.0f, 100.0f);

void FNode::CalculateH(const FVector & FinishLocation)
{
	H = ( FMath::Abs(NodeLocation.X - FinishLocation.X) / FNode::NodeSize.X ) + 
		( FMath::Abs(NodeLocation.Y - FinishLocation.X) / FNode::NodeSize.Y );
}

void UGrid::CreateGrid(const FVector2D& NewGridSize, const FVector & GridCenter)
{

	GridSize = NewGridSize;

	FVector StartingNodeLoc = GridCenter;

	StartingNodeLoc -= FVector((GridSize.X / 2 * FNode::NodeSize.X), (GridSize.Y / 2 * FNode::NodeSize.Y), 0.0f);

	FVector CurrNodeLoc = StartingNodeLoc;


	int32 NodeArrSize = GridSize.X * GridSize.Y;

	int32 NodeIndex = 0;

	NodesArray.Reserve(NodeArrSize);

	for (int32 i = 0; i < GridSize.X; i++)
	{

		for (int32 j = 0; j < GridSize.Y; j++)
		{

			FNode NewNode;

			NewNode.SetIndexes(j, i);
			NewNode.SetLocation(CurrNodeLoc);

			NodesArray.Add(NewNode);

			CurrNodeLoc.X += FNode::NodeSize.X;

			NodeIndex++;

			UE_LOG(LogTemp, Log, TEXT("Created A %d th Node At Location %s"), NodeIndex, *CurrNodeLoc.ToString());

		}

		CurrNodeLoc.X += StartingNodeLoc.X;
		CurrNodeLoc.Y += FNode::NodeSize.Y;

	}

	if (NodesArray.Num() < NodeArrSize)
	{
		UE_LOG(LogTemp, Warning, TEXT("Amount of Nodes is less than Expected Arr Size. "));
		NodesArray.Shrink();
	}

}