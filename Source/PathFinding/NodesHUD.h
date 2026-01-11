// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NodesHUD.generated.h"

struct FNode;

/**
 * 
 */
UCLASS()
class PATHFINDING_API ANodesHUD : public AHUD
{
	GENERATED_BODY()

protected:

	TArray<FNode> NodesArray;

	TArray<FNode> BlockedNodesArray;

	/** Node's Size X in Viewport */
	UPROPERTY(VisibleAnywhere, Category = "HUD Properties")
	float NodeSizeX = 10;
	
	/** Node's Size Y in Viewport*/
	UPROPERTY(VisibleAnywhere, Category = "HUD PRoperties")
	float NodeSizeY = 10;

public:

	UPROPERTY(EditAnywhere, Category = "AAA")
	bool HasGameStarted = false;

protected:

	void DrawGrid();
	
public:

	virtual void DrawHUD() override;

	/** MoveTemps the given arr to NodesArray. Empties the NewArr. */
	void SetNodesArray(TArray<FNode>& NewArr);

	/** Sets The Array Of Blocked Nodes */
	void SetBlockedNodesArray(TArray<FNode>& NewArr);

	void AddBlockedNode(const FNode& NewBlockedNode);

	void SetNodeSize(const float& X, const float& Y);

};
