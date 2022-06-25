// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiBPFL.h"
#include <imgui.h>
#include <string>

//Public

void UImGuiBPFL::PrintSimpleWindow(FString Name, FString Text, FVector2D RelativeScreenPosition)
{
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Name);
	UImGuiBPFL::SetNextWindowPosRelative(RelativeScreenPosition, ImGuiCond_Always);
	ImGui::Begin(&*ConvertBuffer.begin(), nullptr,
		//ImGuiWindowFlags_AlwaysAutoResize +
		//ImGuiWindowFlags_NoBackground +
		//ImGuiWindowFlags_NoCollapse +
		//ImGuiWindowFlags_NoResize +
		//ImGuiWindowFlags_NoInputs +
		ImGuiWindowFlags_NoSavedSettings +
		ImGuiWindowFlags_AlwaysAutoResize +
		ImGuiWindowFlags_NoMove +
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

	//ImGui::SetNextWindowFocus();	//TODO: always-on-top

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

ImGuiWindowFlags UImGuiBPFL::GetFixedWidnowFlag(ImGui_WindowFlags Flag)
{
	switch (Flag)
	{
	case NoTitleBar:
		return ImGuiWindowFlags_NoTitleBar;
		break;
	case NoResize:
		return ImGuiWindowFlags_NoResize;
		break;
	case NoMove:
		return ImGuiWindowFlags_NoMove;
		break;
	case NoScrollbar:
		return ImGuiWindowFlags_NoScrollbar;
		break;
	case NoScrollWithMouse:
		return ImGuiWindowFlags_NoScrollWithMouse;
		break;
	case NoCollapse:
		return ImGuiWindowFlags_NoCollapse;
		break;
	case AlwaysAutoResize:
		return ImGuiWindowFlags_AlwaysAutoResize;
		break;
	case NoBackground:
		return ImGuiWindowFlags_NoBackground;
		break;
	case NoSavedSettings:
		return ImGuiWindowFlags_NoSavedSettings;
		break;
	case NoMouseInputs:
		return ImGuiWindowFlags_NoMouseInputs;
		break;
	case MenuBar:
		return ImGuiWindowFlags_MenuBar;
		break;
	case HorizontalScrollbar:
		return ImGuiWindowFlags_HorizontalScrollbar;
		break;
	case NoFocusOnAppearing:
		return ImGuiWindowFlags_NoFocusOnAppearing;
		break;
	case NoBringToFrontOnFocus:
		return ImGuiWindowFlags_NoBringToFrontOnFocus;
		break;
	case AlwaysVerticalScrollbar:
		return ImGuiWindowFlags_AlwaysVerticalScrollbar;
		break;
	case AlwaysHorizontalScrollbar:
		return ImGuiWindowFlags_AlwaysHorizontalScrollbar;
		break;
	case AlwaysUseWindowPadding:
		return ImGuiWindowFlags_AlwaysUseWindowPadding;
		break;
	case NoNavInputs:
		return ImGuiWindowFlags_NoNavInputs;
		break;
	case NoNavFocus:
		return ImGuiWindowFlags_NoNavFocus;
		break;
	case UnsavedDocument:
		return ImGuiWindowFlags_UnsavedDocument;
		break;
	case NoNav:
		return ImGuiWindowFlags_NoNav;
		break;
	case NoDecoration:
		return ImGuiWindowFlags_NoDecoration;
		break;
	case NoInputs:
		return ImGuiWindowFlags_NoInputs;
		break;
	case None:
		return ImGuiWindowFlags_None;
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("'ImGuiWindowFlags UImGuiBPFL::GetFixedWidnowFlag(ImGui_WindowFlags Flag)' method just returned 'None' due to reching defailt case in switch on ImGui_WindowFlags. Probably new value was added to enum but not to switch."));
		return ImGuiWindowFlags_None;
		break;
	}
}

