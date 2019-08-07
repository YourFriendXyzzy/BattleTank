// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI can't find Player!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller foundplayer: %s"), *(PlayerTank->GetName()));
	}	
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardPlayer();

}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) {return nullptr;}
	else { return Cast<ATank>(PlayerPawn);}
}

void ATankAIController::AimTowardPlayer() {
	if (!GetControlledTank() || !GetPlayerTank()) { return; }
	FVector PlayerPosition = GetPlayerTank()->GetTargetLocation();
	GetControlledTank()->AimAt(PlayerPosition);
}