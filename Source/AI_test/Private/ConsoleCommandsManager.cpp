// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsoleCommandsManager.h"
//#include <Runtime/Engine/Public/Net/UnrealNetwork.h>


UConsoleCommandsManager::UConsoleCommandsManager()
{
    SetIsReplicatedByDefault(true);
}

void UConsoleCommandsManager::BeginPlay()
{
    Super::BeginPlay();

    // We only want to spawn the objects on the server, so they replicate down to the client.
    if (!GetOwner()->HasAuthority())
    {
        return;
    }

    for (const TSubclassOf<UConsoleCommands>& Class : ConsoleCommandsClasses)
    {
        if (Class != nullptr)
        {
            ConsoleCommandsObjects.Add(NewObject<UConsoleCommands>(GetOwner(), Class));
        }
    }
}

bool UConsoleCommandsManager::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
{
    for (UConsoleCommands* Object : ConsoleCommandsObjects)
    {
        if (Object->ProcessConsoleExec(Cmd, Ar, Executor))
        {
            return true;
        }
    }

    return Super::ProcessConsoleExec(Cmd, Ar, Executor);
}

void UConsoleCommandsManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //DOREPLIFETIME(UConsoleCommandsManager, ConsoleCommandsObjects);
}

