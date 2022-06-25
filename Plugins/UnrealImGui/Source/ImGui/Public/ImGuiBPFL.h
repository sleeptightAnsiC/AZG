// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ImGuiBPFL.generated.h"

typedef int ImGuiCond; // <-- z jakiegoœ powodu Linker tego nie ³¹czy przy kompilacji, ogarn¹æ ocb - najprawdopodobniej potrzeba pliku nag³ówkowego


UCLASS()
class IMGUI_API UImGuiBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "DearImGui", meta=(DevelopmentOnly))
	static void PrintSimpleWindow(FString Name, FString Text);

	UFUNCTION(BlueprintCallable, Category = "DearImGui")
	static void PrintWatermark(FString Name, FString Text, FVector2D RelativeScreenPosition, bool bPrintTextOnly, float BackgroundAlpha, bool bDevelopmentOnly);


private:

	UFUNCTION(meta = (DevelopmentOnly))
	static void PrintWatermarkDevelopmentOnly(FString Name, FString Text, FVector2D RelativeScreenPosition, bool bPrintTextOnly, float BackgroundAlpha);
	
	static void PrintWatermarkFixed(FString Name, FString Text, FVector2D RelativeScreenPosition, bool bPrintTextOnly, float BackgroundAlpha);

	static void SetNextWindowPosRelative(FVector2D RelativeScreenPosition, ImGuiCond Condition);

	static void TextMousePosition();
};
