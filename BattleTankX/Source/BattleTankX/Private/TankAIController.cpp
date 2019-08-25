// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "BattleTankX.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//Get Player Tank
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	//Get AI Tank
	auto ControlledTank = GetPawn();
	//Get aiming component
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(PlayerTank && ControlledTank && AimingComponent)) {	return;	}
		//Tmove towards player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim at player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());


		//Fire if ready
		AimingComponent->Fire(); //TODO Re enable AI shooting 

	}



