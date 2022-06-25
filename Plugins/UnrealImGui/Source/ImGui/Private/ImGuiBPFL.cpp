// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiBPFL.h"
#include <imgui.h>
#include <string>



void UImGuiBPFL::PrintSimpleWindow(FString Name, FString Text)
{
	std::string ConvertBuffor = TCHAR_TO_UTF8(*Name);
	ImGui::Begin(&*ConvertBuffor.begin(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Begin(&*ConvertBuffor.begin(), nullptr,
		//ImGuiWindowFlags_AlwaysAutoResize +
		//ImGuiWindowFlags_NoBackground +
		//ImGuiWindowFlags_NoCollapse +
		ImGuiWindowFlags_NoSavedSettings +
		//ImGuiWindowFlags_NoResize +
		//ImGuiWindowFlags_NoInputs +
		ImGuiWindowFlags_None
	);
	ConvertBuffor = TCHAR_TO_UTF8(*Text);
	ImGui::Text(&*ConvertBuffor.begin());
	
	ImGui::End();
}

void UImGuiBPFL::PrintWatermark(FString Name, FString Text, bool bPrintTextOnly, bool bNoBackground, bool bDevelopmentOnly)
{
	// This function is just a Front-End for blueprints
	// for PrintWatermark functionality check function PrintWatermarkFixed

	if(bDevelopmentOnly)
		UImGuiBPFL::PrintWatermarkDevelopmentOnly(Name, Text, bPrintTextOnly, bNoBackground);
	else
		UImGuiBPFL::PrintWatermarkFixed(Name, Text, bPrintTextOnly, bNoBackground);
}
void UImGuiBPFL::PrintWatermarkDevelopmentOnly(FString Name, FString Text, bool bPrintTextOnly, bool bNoBackground)
{
	// This function is development only
	// for PrintWatermark functionality check function PrintWatermarkFixed

	UImGuiBPFL::PrintWatermarkFixed(Name, Text, bPrintTextOnly, bNoBackground);
}
void UImGuiBPFL::PrintWatermarkFixed(FString Name, FString Text, bool bPrintTextOnly, bool bNoBackground)
{
	//Main functionality for PrintWatermark

	auto flags =
		ImGuiWindowFlags_AlwaysAutoResize +
		ImGuiWindowFlags_NoSavedSettings +
		ImGuiWindowFlags_NoCollapse +
		ImGuiWindowFlags_NoInputs +
		ImGuiWindowFlags_None;
	if (bPrintTextOnly)
		flags += ImGuiWindowFlags_NoTitleBar;
	if (bNoBackground)
		flags += ImGuiWindowFlags_NoBackground;

	std::string ConvertBuffor
		= TCHAR_TO_UTF8(*Name);
	ImGui::Begin(&*ConvertBuffor.begin(), nullptr, flags);
	ConvertBuffor = TCHAR_TO_UTF8(*Text);
	ImGui::Text(&*ConvertBuffor.begin());
	ImGui::End();
}

