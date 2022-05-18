// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_CommandsActor.h"

APC_CommandsActor::APC_CommandsActor()
{
    ConsoleCommandsManager = CreateDefaultSubobject<UConsoleCommandsManager>(TEXT("ConsoleCommandsManager"));
}

bool APC_CommandsActor::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
{
    bool bHandled = Super::ProcessConsoleExec(Cmd, Ar, Executor);

    if (!bHandled && ConsoleCommandsManager != nullptr)
    {
        bHandled |= ConsoleCommandsManager->ProcessConsoleExec(Cmd, Ar, Executor);
    }

    return bHandled;
}