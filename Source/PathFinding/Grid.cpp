// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

FVector2D FNode::NodeSize = FVector2D(80.0f, 80.0f);

void FNode::CalculateH(const FVector & FinishLocation)
{
	H = ( FMath::Abs(NodeLocation.X - FinishLocation.X) / FNode::NodeSize.X ) + 
		( FMath::Abs(NodeLocation.Y - FinishLocation.X) / FNode::NodeSize.Y );
}

void FNode::GetTopLeftCornerLocation(float& X, float& Y)
{

	X = NodeLocation.X -= ( FNode::NodeSize.X / 2 );
	Y = NodeLocation.Y -= ( FNode::NodeSize.Y / 2 );

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
		
		TArray<FNode> NewArray;

		for (int32 j = 0; j < GridSize.Y; j++)
		{

			FNode NewNode;

			NewNode.SetIndexes(i, j);
			NewNode.SetLocation(CurrNodeLoc);

			NewArray.Add(NewNode);

			CurrNodeLoc.X += FNode::NodeSize.X;

			NodeIndex++;

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

TArray<FNode> UGrid::FindPath(int32 StartIndexX, int32 StartIndexY, int32 FinishIndexX, int32 FinishIndexY)
{

	FNode StartNode = NodesArray[StartIndexX][StartIndexY];
	FNode FinishNode = NodesArray[FinishIndexX][FinishIndexY];

	TArray<FNode> EndArray = { StartNode, FinishNode };

	TArray<FNode> OpenList;
	TSet<FNode> OpenSet;
	TSet<FNode> ClosedSet;
	
	OpenList.Heapify(FCompareNodes());


	return ReconstructPath(EndArray.Last());

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

TArray<FNode> UGrid::GetEmptyArray()
{

	return TArray<FNode>();

}

TArray<FNode> UGrid::ReconstructPath(FNode& LastNode)
{

	FNode *TraversalNode = &LastNode;

	TArray<FNode> NewArray;

	while (TraversalNode)
	{

		NewArray.Add(*TraversalNode);

		if (!TraversalNode->ParentNode)
		{
			break;
		}

		TraversalNode = TraversalNode->ParentNode;


	}

	ReverseArray(NewArray);

	return NewArray;

}

void UGrid::ReverseArray(TArray<FNode>& Array)
{

	int32 ArrSize = Array.Num() / 2;

	for (int32 i = 0; i < ArrSize; i++)
	{
	
		SwapNodes(Array[i], Array[ArrSize - 1 - i]);

	}


}

void UGrid::SwapNodes(FNode& NodeA, FNode& NodeB)
{

	FNode TempNode = NodeA;

	NodeA = NodeB;

	NodeB = TempNode;

}