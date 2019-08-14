// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANKX_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	//Called Every Tick
	virtual void Tick(float DeltaTime) override;
	//Called at begin play
	void BeginPlay() override;


private:
	// gets player tank
	ATank* PlayerTank = nullptr;
	//gets AI tank
	ATank* ControlledTank = nullptr;
	//acceptance radius = how close the ai tank will get to the player
	float AcceptanceRadius = 3000;

};
