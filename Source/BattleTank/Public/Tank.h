// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel *BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret *TurretToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent *TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Input)
	UTankMovementComponent *TankMovementComponent = nullptr;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel *Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 100000.f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float FireCooldown = 7;
	double LastFireTime = 0;
};