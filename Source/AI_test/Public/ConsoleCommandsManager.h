// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConsoleCommands.h"
#include "ConsoleCommandsManager.generated.h"


//class AI_TEST_API UConsoleCommands;

UCLASS(Within = PlayerController, BlueprintType)
class AI_TEST_API UConsoleCommandsManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UConsoleCommandsManager();

    virtual void BeginPlay() override;

    virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;

    UPROPERTY(EditDefaultsOnly)
        TArray<TSubclassOf<UConsoleCommands>> ConsoleCommandsClasses;

private:
    UPROPERTY(Transient, Replicated)
        TArray<UConsoleCommands*> ConsoleCommandsObjects;
};
