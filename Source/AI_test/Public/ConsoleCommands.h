// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConsoleCommands.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType)
class  AI_TEST_API UConsoleCommands : public UActorComponent
{
	GENERATED_BODY()

public:
	UConsoleCommands();
};
