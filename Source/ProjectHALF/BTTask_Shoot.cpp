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
    if (OwnerComp.GetAIOwner() == nullptr) { return EBTNodeResult::Failed; } //if owner isn't AI return fail

    AEnemyCharacter* EnemyCharacterClass = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (EnemyCharacterClass == nullptr) { return EBTNodeResult::Failed; } //if cast failed, node failed and return

    //if everything's alright, shoot and return node successful
    EnemyCharacterClass->Shoot();
    return EBTNodeResult::Succeeded;
}