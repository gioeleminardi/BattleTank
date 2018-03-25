// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ATank *ControlledTank = GetControlledTank();
	ATank *PlayerTank = GetPlayerTank();
	if (ControlledTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Controlled AI Tank is null"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controlled AI Tank is: %s"), *(ControlledTank->GetName()));
	}

	if (PlayerTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Player Tank is null"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank is: %s"), *(PlayerTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
		//Move towards the player

		//AimAt player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//Fire if ready
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
