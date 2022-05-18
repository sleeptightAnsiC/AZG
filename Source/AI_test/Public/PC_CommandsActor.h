// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ConsoleCommandsManager.h"
#include "PC_CommandsActor.generated.h"

UCLASS()
class AI_TEST_API APC_CommandsActor : public APlayerController
{
    GENERATED_BODY()
    APC_CommandsActor();

    virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;

    UPROPERTY(EditDefaultsOnly)
    UConsoleCommandsManager* ConsoleCommandsManager;

    /* ... */
};
