// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHALF_API UBTService_SetPlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
		UBTService_SetPlayerLocation();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
