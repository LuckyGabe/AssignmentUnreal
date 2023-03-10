// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"

class USphereComponent;
UCLASS()
class PROJECTHALF_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBarrel();

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BarrelMesh;

	void Explode();

public:	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere)
		float Damage = 100;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* Explosion;

	UPROPERTY(EditAnywhere)
		float ExplosionRadius = 500;

	UPROPERTY(EditAnywhere)
		float Health = 20;
	UPROPERTY(EditAnywhere)
		USoundBase* ExplosionSound;
	bool bExploded = false;
};
