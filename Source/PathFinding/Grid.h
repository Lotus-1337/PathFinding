// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid.generated.h"

USTRUCT()
struct FNode
{

	GENERATED_BODY()

	friend class UGrid;

protected:

	/** Node's G Cost ( Cost from Start ) */
	UPROPERTY(VisibleAnywhere, Category = "Node Values")
	int32 G = INT32_MAX - 1;

	/** Node's H Cost ( Heuretic [ optimistic distance to Finish ] )*/
	UPROPERTY(VisibleAnywhere, Category = "Node Values")
	int32 H = 0;

	/** Node's F Cost ( Sum Of G And H Cost ) */
	UPROPERTY(VisibleAnywhere, Category = "Node Values")
	int32 F = INT32_MAX - 1;


	UPROPERTY(VisibleAnywhere, Category = "Node Properties")
	FVector NodeLocation;

public:

	/** Parent Node Of this Node, The one that comes before it in the Path */
	FNode* ParentNode;

	/** X Index Of This Node In Nodes Array*/
	UPROPERTY(VisibleAnywhere, Category = "Node's Data")
	int32 IndexX;

	/** Y Index Of This Node In Nodes Array*/
	UPROPERTY(VisibleAnywhere, Category = "Node's Data")
	int32 IndexY;

	/** Is Node Blocked By Something? */
	UPROPERTY(VisibleAnywhere, Category = "Node Properties")
	bool IsBlocked = 0;

	/** Calculating Heuristic in Manhattan Method ( If Only Location is Passed )*/
	void CalculateH(const FVector & FinishLocation);

	/** Calculating Heuristic in Manhattan Method ( If Node Is Passed ) */
	void CalculateH(const FNode& FinishNode);

	static FVector2D NodeSize;


	void GetTopLeftCornerLocation(float& X, float& Y);

	FORCEINLINE void CalculateF()
	{
		F = G + H;
	}


	FORCEINLINE int32 GetG() const
	{
		return G;
	}

	FORCEINLINE int32 GetH() const
	{
		return H;
	}

	FORCEINLINE int32 GetF() const
	{
		return F;
	}

	FORCEINLINE FVector GetLocation() const
	{
		return NodeLocation;
	}

	FORCEINLINE void SetG(const int32& NewG)
	{
		G = NewG;
	}

	/** Only Use this Function when resetting Nodes */
	FORCEINLINE void SetH(const int32& NewH)
	{
		H = NewH;
	}

	FORCEINLINE void SetLocation(const FVector& NewLocation)
	{
		NodeLocation = NewLocation;
	}


	FORCEINLINE void SetIndexes(const int32& X, const int32& Y)
	{
		IndexX = X;
		IndexY = Y;
	}


	FORCEINLINE bool operator==(const FNode& OtherNode) const 
	{
		return IndexX == OtherNode.IndexX && IndexY == OtherNode.IndexY;
	}

	FORCEINLINE bool operator<(const FNode& B) const
	{
		return F < B.GetF();
	}

};

// Function Neccesary for TSets 
FORCEINLINE uint32 GetTypeHash(const FNode& Key)
{
	return HashCombine(::GetTypeHash(Key.IndexX), ::GetTypeHash(Key.IndexY));
}

// Struct Neccesary for Heaps
struct FCompareNodes
{
	FORCEINLINE bool operator()(const FNode& A, const FNode& B) const
	{
		return A.GetF() < B.GetF();
	}

	FORCEINLINE bool operator()(const FNode* A, const FNode* B) const
	{
		return A->GetF() < B->GetF();
	}
};

/**
 * 
 */
UCLASS()
class PATHFINDING_API UGrid : public UObject
{
	GENERATED_BODY()

protected:

	/** Array of Nodes */
	TArray<TArray<FNode>> NodesArray;

	FVector2D GridSize;

	/** Location of the Starting Node */
	FVector StartingNodeLocation;

public:

	void CreateGrid(const FVector2D & NewGridSize, const FVector & GridCenter);
	
	
	TArray<FNode> FindPath(int32 StartIndexX, int32 StartIndexY, int32 FinishIndexX, int32 FinishIndexY);

protected:

	bool GetNodeIndexByLocation(const FVector& Location, int32& X, int32& Y);

	TArray<FNode> GetEmptyArray();

	/** Reversing the Array so the first one is the Starting One instead of The Finishing One*/
	void ReverseArray(TArray<FNode>& Array);

	/** Swapping Nodes Function for convenient reversing */
	void SwapNodes(FNode& NodeA, FNode& NodeB);

	/** Returns a TArray of Nodes To Get To the Last Node */
	TArray<FNode> ReconstructPath(FNode& LastNode);

	/** Returns Array of Node's Neighbours ( Only the valid ones ) */
	void GetNeighbours(TArray<FNode*> & NeighboursArr, const FNode& Node);

	/** Restoring All the Nodes in the Set to Default Values. Pass All the sets, where there are nodes.
	Not resetting The main Array because most of the Nodes Would be cleaned without purpose. 
	Cleaning Sets is a HUGE Performance boost. */
	void CleanSet(TSet<FNode*> &SetToClean);

public:

	// INLINES


	FORCEINLINE FVector2D GetGridSize()
	{
		return GridSize;
	}

};
