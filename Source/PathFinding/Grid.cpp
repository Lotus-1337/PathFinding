// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

FVector2D FNode::NodeSize = FVector2D(80.0f, 80.0f);

void FNode::CalculateH(const FVector & FinishLocation)
{
	H = ( FMath::Abs(NodeLocation.X - FinishLocation.X) / FNode::NodeSize.X ) + 
		( FMath::Abs(NodeLocation.Y - FinishLocation.X) / FNode::NodeSize.Y );
}

void FNode::CalculateH(const FNode& FinishNode)
{
	H = (FMath::Abs(IndexX - FinishNode.IndexX)) +
		(FMath::Abs(IndexY - FinishNode.IndexY));
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

	TArray<FNode> PathArray;

	FNode *StartNode = &NodesArray[StartIndexX][StartIndexY];
	FNode *FinishNode = &NodesArray[FinishIndexX][FinishIndexY];

	TArray<FNode*> OpenList;
	TSet<FNode*> OpenSet;
	TSet<FNode*> ClosedSet;

	TArray<FNode*> UsedNodes = { StartNode };
	
	OpenList.Heapify(FCompareNodes());

	OpenList.HeapPush(StartNode, FCompareNodes());

	FNode *CurrentNode = StartNode;

	TArray<FNode*> NeighboursArray;

	int32 Iteration = 0;
	int32 NeighboursI = 0;

	while (OpenList.Num())
	{

		UE_LOG(LogTemp, Log, TEXT("Iteration of PathFinding: %d"), Iteration);

		/** Current Node now becomes the best Node available. The best node is deleted from the heap */
		OpenList.HeapPop(CurrentNode, FCompareNodes());

		if (CurrentNode == FinishNode)
		{
			
			PathArray = ReconstructPath(*CurrentNode);
			
			CleanArray(UsedNodes);

			return PathArray;

		}

		OpenSet.Remove(CurrentNode);
		ClosedSet.Add(CurrentNode);

		GetNeighbours(NeighboursArray, *CurrentNode);

		for (FNode* Neighbour : NeighboursArray)
		{

			UE_LOG(LogTemp, Log, TEXT("Neighbour Iteration : %d"), NeighboursI);

			if (ClosedSet.Contains(Neighbour))
			{
				continue;
			}

			int32 NewG = CurrentNode->GetG() + 1;

			if (OpenSet.Contains(Neighbour) && NewG >= Neighbour->GetG())
			{
				UE_LOG(LogTemp, Log, TEXT("Line 133. "));
				continue;
			}

			if (OpenSet.Contains(Neighbour))
			{
				OpenSet.Remove(Neighbour);
				OpenList.Remove(Neighbour);
				OpenList.Heapify(FCompareNodes());
			}

			Neighbour->ParentNode = CurrentNode;

			Neighbour->SetG(NewG);
			Neighbour->CalculateH(*FinishNode);

			Neighbour->CalculateF();
	
			OpenList.HeapPush(Neighbour, FCompareNodes());

			NeighboursI++;

			UsedNodes.Add(Neighbour);

		}
		
		Iteration++;

	}

	PathArray = ReconstructPath(*CurrentNode);

	CleanArray(UsedNodes);

	return PathArray;

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
			UE_LOG(LogTemp, Warning, TEXT("Parent Node is Nullptr. "));
			break;
		}

		TraversalNode = TraversalNode->ParentNode;

		UE_LOG(LogTemp, Log, TEXT("Succesfull Iteration. "));


	}

	ReverseArray(NewArray);

	return NewArray;

}

void UGrid::GetNeighbours(TArray<FNode*>& NeighboursArr, const FNode& Node)
{

	if (!NodesArray.IsValidIndex(Node.IndexX) || !NodesArray.IsValidIndex(Node.IndexY))
	{
		UE_LOG(LogTemp, Error, TEXT("Given Node doesnt't Exist. "));
		return;
	}

	if (NeighboursArr.Num()) // if it's not 0
	{
		UE_LOG(LogTemp, Error, TEXT("Given Array is going to get forcefully empty. All the Elements are going to be removed. "));
		NeighboursArr.Empty();
	}

	// Checking if each Neighbour Node exists and if is not blocked, if so, it's added to the neighboursArray
	if (NodesArray.IsValidIndex(Node.IndexX + 1) && !NodesArray[Node.IndexX + 1][Node.IndexY].IsBlocked)
	{
		NeighboursArr.Add(&NodesArray[Node.IndexX + 1][Node.IndexY]);
	}

	if (NodesArray.IsValidIndex(Node.IndexX - 1) && !NodesArray[Node.IndexX - 1][Node.IndexY].IsBlocked)
	{
		NeighboursArr.Add(&NodesArray[Node.IndexX - 1][Node.IndexY]);
	}

	if (NodesArray[Node.IndexX].IsValidIndex(Node.IndexY + 1) && !NodesArray[Node.IndexX][Node.IndexY + 1].IsBlocked)
	{
		NeighboursArr.Add(&NodesArray[Node.IndexX][Node.IndexY + 1]);
	}

	if (NodesArray[Node.IndexX].IsValidIndex(Node.IndexY - 1) && !NodesArray[Node.IndexX][Node.IndexY - 1].IsBlocked)
	{
		NeighboursArr.Add(&NodesArray[Node.IndexX][Node.IndexY - 1]);
	}

}

void UGrid::ReverseArray(TArray<FNode>& Array)
{

	int32 ArrSize = Array.Num();

	for (int32 i = 0; i < ArrSize / 2; i++)
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

void UGrid::CleanArray(TArray<FNode*>& ArrToClean)
{

	for (FNode* Node : ArrToClean)
	{

		Node->SetG(INT32_MAX - 1);

		Node->SetH(0);

		Node->CalculateF();

		Node->ParentNode = nullptr;

	}

}

FNode * UGrid::GetNodeByIndex(int32& X, int32& Y)
{

	if (!NodesArray.IsValidIndex(X) || !NodesArray[X].IsValidIndex(Y))
	{
		return nullptr;
	}

	return &NodesArray[X][Y];

}

void UGrid::BlockNodeAtIndex(int32 X, int32 Y)
{
	if (!NodesArray.IsValidIndex(X) || !NodesArray[X].IsValidIndex(Y))
	{
		UE_LOG(LogTemp, Error, TEXT("Given Indexes are invalid. UGrid::BlockNodeAtIndex"));
		return;
	}
	NodesArray[X][Y].IsBlocked = true;

}