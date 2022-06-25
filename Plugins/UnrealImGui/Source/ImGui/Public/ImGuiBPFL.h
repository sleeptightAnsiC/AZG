// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ImGuiBPFL.generated.h"


UCLASS()
class IMGUI_API UImGuiBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta=(DevelopmentOnly))
	static void PrintSimpleWindow(FString Name, FString Text);

	UFUNCTION(BlueprintCallable, Category = "DearImGui")
	static void PrintWatermark(FString Name, FString Text, bool bPrintTextOnly, bool bNoBackground, bool bDevelopmentOnly);


private:

	UFUNCTION(meta = (DevelopmentOnly))
	static void PrintWatermarkDevelopmentOnly(FString Name, FString Text, bool bPrintTextOnly, bool bNoBackground);
	
	static void PrintWatermarkFixed(FString Name, FString Text, bool bPrintTextOnly, bool bNoBackground);
};
