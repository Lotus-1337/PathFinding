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

	/** Node's Size X in Viewport */
	UPROPERTY(VisibleAnywhere, Category = "HUD Properties")
	float NodeSizeX = 10;
	
	/** Node's Size Y in Viewport*/
	UPROPERTY(VisibleAnywhere, Category = "HUD PRoperties")
	float NodeSizeY = 10;

	
public:

	virtual void DrawHUD() override;

	/** MoveTemps the given arr to NodesArray. Empties the NewArr. */
	void SetNodesArray(TArray<FNode>& NewArr);

	void SetNodeSize(const float& X, const float& Y);

};
