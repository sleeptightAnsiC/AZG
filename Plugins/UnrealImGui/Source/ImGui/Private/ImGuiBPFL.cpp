// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiBPFL.h"
#include <imgui.h>
#include <string>



void UImGuiBPFL::Print(FString Name, FString Text)
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

