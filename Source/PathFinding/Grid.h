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
	int32 G;

	/** Node's H Cost ( Heuretic [ optimistic distance to Finish ] )*/
	UPROPERTY(VisibleAnywhere, Category = "Node Values")
	int32 H;

	/** Node's F Cost ( Sum Of G And H Cost ) */
	UPROPERTY(VisibleAnywhere, Category = "Node Values")
	int32 F;


	UPROPERTY(VisibleAnywhere, Category = "Node Properties")
	FVector NodeLocation;

public:

	/** X Index Of This Node In Nodes Array*/
	UPROPERTY(VisibleAnywhere, Category = "Node's Data")
	int32 IndexX;

	/** Y Index Of This Node In Nodes Array*/
	UPROPERTY(VisibleAnywhere, Category = "Node's Data")
	int32 IndexY;

	/** Is Node Blocked By Something? */
	UPROPERTY(VisibleAnywhere, Category = "Node Properties")
	bool IsBlocked;

	/** Calculating Heuristic in Manhattan Method */
	void CalculateH(const FVector & FinishLocation);

	static FVector2D NodeSize;


	void GetTopLeftCornerLocation(float& X, float& Y);

	FORCEINLINE void CalculateF()
	{
		F = G + H;
	}


	FORCEINLINE int32 GetG()
	{
		return G;
	}

	FORCEINLINE int32 GetH()
	{
		return H;
	}

	FORCEINLINE int32 GetF()
	{
		return F;
	}

	FORCEINLINE FVector GetLocation()
	{
		return NodeLocation;
	}

	FORCEINLINE void SetG(const int32& NewG)
	{
		G = NewG;
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

public:

	// INLINES


	FORCEINLINE FVector2D GetGridSize()
	{
		return GridSize;
	}

};
