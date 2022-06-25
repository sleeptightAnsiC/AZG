// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiBPFL.h"
#include <imgui.h>
#include <string>

//Public

void UImGuiBPFL::PrintSimpleWindow(FString Name, FString Text)
{
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Name);
	ImGui::Begin(&*ConvertBuffer.begin(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Begin(&*ConvertBuffer.begin(), nullptr,
		//ImGuiWindowFlags_AlwaysAutoResize +
		//ImGuiWindowFlags_NoBackground +
		//ImGuiWindowFlags_NoCollapse +
		ImGuiWindowFlags_NoSavedSettings +
		//ImGuiWindowFlags_NoResize +
		//ImGuiWindowFlags_NoInputs +
		ImGuiWindowFlags_None
	);
	ConvertBuffer = TCHAR_TO_UTF8(*Text);
	ImGui::Text(&*ConvertBuffer.begin());
	
	ImGui::End();
}

void UImGuiBPFL::PrintWatermark(FString Name, FString Text, FVector2D RelativeScreenPosition, bool bPrintTextOnly, float BackgroundAlpha, bool bDevelopmentOnly)
{
	// This function is just a Front-End for blueprints
	// for PrintWatermark functionality check function PrintWatermarkFixed

	if(bDevelopmentOnly)
		UImGuiBPFL::PrintWatermarkDevelopmentOnly(Name, Text, RelativeScreenPosition, bPrintTextOnly, BackgroundAlpha);
	else
		UImGuiBPFL::PrintWatermarkFixed(Name, Text, RelativeScreenPosition, bPrintTextOnly, BackgroundAlpha);
}



//Private

void UImGuiBPFL::PrintWatermarkDevelopmentOnly(FString Name, FString Text, FVector2D RelativeScreenPosition, bool bPrintTextOnly, float BackgroundAlpha)
{
	// This function is development only
	// for PrintWatermark functionality check function PrintWatermarkFixed

	UImGuiBPFL::PrintWatermarkFixed(Name, Text, RelativeScreenPosition, bPrintTextOnly, BackgroundAlpha);
}

void UImGuiBPFL::PrintWatermarkFixed(FString Name, FString Text, FVector2D RelativeScreenPosition, bool bPrintTextOnly, float BackgroundAlpha)
{
	//Main functionality for PrintWatermark
	
	auto flags =
		ImGuiWindowFlags_AlwaysAutoResize +
		ImGuiWindowFlags_NoCollapse +
		ImGuiWindowFlags_NoInputs +
		ImGuiWindowFlags_NoFocusOnAppearing +
		ImGuiWindowFlags_NoNav +
		ImGuiWindowFlags_NoMove +
		ImGuiWindowFlags_None;
	if (bPrintTextOnly)
		flags += ImGuiWindowFlags_NoTitleBar;

	UImGuiBPFL::SetNextWindowPosRelative(RelativeScreenPosition, ImGuiCond_Always);
	ImGui::SetNextWindowBgAlpha(BackgroundAlpha);

	std::string ConvertBuffer
		= TCHAR_TO_UTF8(*Name);
	ImGui::Begin(&*ConvertBuffer.begin(), nullptr, flags);
	ConvertBuffer = TCHAR_TO_UTF8(*Text);
	ImGui::Text(&*ConvertBuffer.begin());

	ImGui::End();
}

void UImGuiBPFL::SetNextWindowPosRelative(FVector2D RelativeScreenPosition, ImGuiCond Condition)
{
	FVector2D ViewportSize
		= FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ImVec2 window_pos, window_pos_pivot;
	window_pos.x = RelativeScreenPosition.X * ViewportSize.X;
	window_pos.y = RelativeScreenPosition.Y * ViewportSize.Y;
	window_pos_pivot.x = RelativeScreenPosition.X;
	window_pos_pivot.y = RelativeScreenPosition.Y;

	ImGui::SetNextWindowPos(window_pos, Condition, window_pos_pivot);
}

void UImGuiBPFL::TextMousePosition()
{
	ImGuiIO& io = ImGui::GetIO();
	if (ImGui::IsMousePosValid())
		ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
	else
		ImGui::Text("Mouse Position: <invalid>");
}

