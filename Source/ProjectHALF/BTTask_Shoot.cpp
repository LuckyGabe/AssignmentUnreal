// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "EnemyCharacter.h"
#include "AIController.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    if (OwnerComp.GetAIOwner() == nullptr) { return EBTNodeResult::Failed; }

    AEnemyCharacter* EnemyCharacterClass = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (EnemyCharacterClass == nullptr) { return EBTNodeResult::Failed; }
    EnemyCharacterClass->Shoot();

    return EBTNodeResult::Succeeded;
}