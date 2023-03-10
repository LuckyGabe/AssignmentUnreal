// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"
class AGun;
class UCameraComponent;
UCLASS()
class PROJECTHALF_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	//Function to be passed to animation blueprint
	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	UFUNCTION(BlueprintPure)
		float GetHealthPercentage() const;

	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//override take damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf< AGun> gunBP;
	void OpenGate(); // opens gate on level 3
	UPROPERTY(EditAnywhere)
		float maxHealth = 100;
	UPROPERTY(EditAnywhere)
		bool IsBoss = false;

	UPROPERTY(VisibleAnywhere)
		float health;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComponent;

	UPROPERTY()
		AGun* gun;
};
