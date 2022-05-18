// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsoleCommands.h"



UConsoleCommands::UConsoleCommands()
{
    SetIsReplicatedByDefault(true);

    for (TFieldIterator<UFunction> It(GetClass()); It; ++It)
    {
        if (GetClass()->IsChildOf(Cast<UClass>(It.GetStruct())))
        {
            It->FunctionFlags |= FUNC_Exec;
        }
    }
}

