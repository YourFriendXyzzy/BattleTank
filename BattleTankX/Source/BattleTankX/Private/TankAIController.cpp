// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();


}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//Get AI Tank
	auto ControlledTank = Cast<ATank>(GetPawn());
	//Get Player Tank
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());



	
	if (PlayerTank) {
		//TODO move towards player

		// Aim at player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//Fire if ready
		ControlledTank->Fire(); //Limit Firing rate

	}
}


