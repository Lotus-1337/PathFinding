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

	StartingNodeLocation = GridCenter;

	StartingNodeLocation -= FVector((GridSize.X / 2 * FNode::NodeSize.X), (GridSize.Y / 2 * FNode::NodeSize.Y), 0.0f);

	FVector CurrNodeLoc = StartingNodeLocation;


	int32 NodeArrSize = GridSize.X * GridSize.Y;

	int32 NodeIndex = 0;

	NodesArray.Reserve(NodeArrSize);

	

	for (int32 i = 0; i < GridSize.X; i++)
	{
		
		TArray<FNode*> NewArray;

		for (int32 j = 0; j < GridSize.Y; j++)
		{

			FNode NewNode;

			NewNode.SetIndexes(j, i);
			NewNode.SetLocation(CurrNodeLoc);

			NewArray.Add(&NewNode);

			CurrNodeLoc.X += FNode::NodeSize.X;

			NodeIndex++;

			UE_LOG(LogTemp, Log, TEXT("Created A %d th Node At Location %s"), NodeIndex, *CurrNodeLoc.ToString());

		}

		CurrNodeLoc.X += StartingNodeLocation.X;
		CurrNodeLoc.Y += FNode::NodeSize.Y;

		NodesArray.Add(NewArray);

	}

	if (NodesArray.Num() < NodeArrSize)
	{
		UE_LOG(LogTemp, Warning, TEXT("Amount of Nodes is less than Expected Arr Size. "));
		NodesArray.Shrink();
	}

}

TArray<FNode*> UGrid::FindPath(const FVector& Start, const FVector& Finish)
{

	int32 StartIndexX;
	int32 StartIndexY;

	if (!GetNodeIndexByLocation(Start, StartIndexX, StartIndexY))
	{
		UE_LOG(LogTemp, Error, TEXT("Start Location is invalid. "));
		return GetEmptyArray();
	}

	int32 FinishIndexX;
	int32 FinishIndexY;

	if (!GetNodeIndexByLocation(Finish, FinishIndexX, FinishIndexY))
	{
		UE_LOG(LogTemp, Error, TEXT("Finish Location is invalid. "));
		return GetEmptyArray();
	}

	FNode* StartNode = NodesArray[StartIndexX][StartIndexY];
	FNode* FinishNode = NodesArray[FinishIndexX][FinishIndexY];

	TArray<FNode*> EndArray = { StartNode, FinishNode };

	return EndArray;


}

bool UGrid::GetNodeIndexByLocation(const FVector& Location, int32& X, int32& Y)
{

	FVector LocationDiff = Location - StartingNodeLocation;

	X = FMath::Abs(LocationDiff.X) / FNode::NodeSize.X;
	Y = FMath::Abs(LocationDiff.Y) / FNode::NodeSize.Y;

	if (NodesArray.IsValidIndex(X) && NodesArray[X].IsValidIndex(Y))
	{
		return true;
	}

	X = 0;
	Y = 0;

	return false;

}

TArray<FNode*> UGrid::GetEmptyArray()
{

	TArray<FNode*> Arr;
	return Arr;

}