// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiBPFL.h"
#include <imgui.h>
#include <string>

static bool bPrinting = false;

const FString NullMessage = "No message provided :(";

//Public

void UImGuiBPFL::PrintSimpleWindow(FString Name, FString Text, FVector2D RelativeScreenPosition)
{
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Name);
	UImGuiBPFL::SetNextWindowPosRelative(RelativeScreenPosition, ImGuiCond_Once);
	ImGui::Begin(&*ConvertBuffer.begin(), nullptr,
		//ImGuiWindowFlags_AlwaysAutoResize +
		//ImGuiWindowFlags_NoBackground +
		//ImGuiWindowFlags_NoCollapse +
		//ImGuiWindowFlags_NoResize +
		//ImGuiWindowFlags_NoInputs +
		ImGuiWindowFlags_NoSavedSettings +
		ImGuiWindowFlags_AlwaysAutoResize +
		//ImGuiWindowFlags_NoMove +
		ImGuiWindowFlags_None
	);
	ConvertBuffer = TCHAR_TO_UTF8(*Text);
	ImGui::Text(&*ConvertBuffer.begin());
	
	ImGui::End();
}

void UImGuiBPFL::PrintSimpleWatermark(FString Name, FString Text, FVector2D RelativeScreenPosition, bool bPrintTextOnly, float BackgroundAlpha)
{	
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

		//ImGui::SetWindowFocus(&*ConvertBuffer.begin());	 //Always-On-Top Placeholder

		ConvertBuffer = TCHAR_TO_UTF8(*Text);
		ImGui::Text(&*ConvertBuffer.begin());

		ImGui::End();
}

void UImGuiBPFL::StartPrintingWindow(FString Name, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties)
{
	if (TryWindowFunction(false, "StartPrintingWindow", "You cannot start Printing another Window before closing the already existing one. Probably 'StopPrintingWindow()' is missing somewhere."))
	{
		bPrinting = true;

		ImGuiWindowFlags Flags = 0;
		for (ImGui_WindowFlags SimpleFlag : Properties)
		{
			Flags += GetFixedWidnowFlag(SimpleFlag);
		}

		std::string ConvertBuffer = TCHAR_TO_UTF8(*Name);
		ImGui::Begin(&*ConvertBuffer.begin());

		/*
		if (ImGui::Button("200x200")) { ImGui::SetWindowSize(ImVec2(200, 200)); } ImGui::SameLine();
		if (ImGui::Button("500x500")) { ImGui::SetWindowSize(ImVec2(500, 500)); } ImGui::SameLine();
		if (ImGui::Button("800x200")) { ImGui::SetWindowSize(ImVec2(800, 200)); }
		*/
	}
}

void UImGuiBPFL::StopPrintingWindow()
{
	if (TryWindowFunction(true, "StopPrintingWindow", NullMessage))
	{
		ImGui::End();
		bPrinting = false;
	}
}

void UImGuiBPFL::AddTextToWindow(FString Text)
{
	if (TryWindowFunction(true, "AddTextToWindow", NullMessage))
	{
		static std::string ConvertBuffer = TCHAR_TO_UTF8(*Text);
		ImGui::Text(&*ConvertBuffer.begin());
	}
}




//Private


bool UImGuiBPFL::TryWindowFunction(bool bShallBePrinting, FString FunctionName, FString AdditionalErrorMessage)
{
	if (bShallBePrinting == bPrinting)
		return true;
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'ImGuiBPFL::%s' function has not executed due to bPrinting flag being set to %s / Additional info: %s"), *FunctionName, bPrinting ? TEXT("TRUE") : TEXT("FALSE"), *AdditionalErrorMessage)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("'ImGuiBPFL::%s' function has not executed due to bPrinting flag being set to %s / Additional info: %s"), *FunctionName, bPrinting ? TEXT("TRUE") : TEXT("FALSE"), *AdditionalErrorMessage));
		return false;
	}
}

void UImGuiBPFL::SetNextWindowPosRelative(FVector2D RelativeScreenPosition, ImGuiCond Condition)
{
	FVector2D ViewportSize
		= FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	if (ViewportSize.X > 0 && ViewportSize.Y > 0)
	{  
		ImVec2 window_pos, window_pos_pivot;
		window_pos.x = RelativeScreenPosition.X * ViewportSize.X;
		window_pos.y = RelativeScreenPosition.Y * ViewportSize.Y;
		window_pos_pivot.x = RelativeScreenPosition.X;
		window_pos_pivot.y = RelativeScreenPosition.Y;

		ImGui::SetNextWindowPos(window_pos, Condition, window_pos_pivot);
	}
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
	case NoResize:
		return ImGuiWindowFlags_NoResize;
	case NoMove:
		return ImGuiWindowFlags_NoMove;
	case NoScrollbar:
		return ImGuiWindowFlags_NoScrollbar;
	case NoScrollWithMouse:
		return ImGuiWindowFlags_NoScrollWithMouse;
	case NoCollapse:
		return ImGuiWindowFlags_NoCollapse;
	case AlwaysAutoResize:
		return ImGuiWindowFlags_AlwaysAutoResize;
	case NoBackground:
		return ImGuiWindowFlags_NoBackground;
	case NoSavedSettings:
		return ImGuiWindowFlags_NoSavedSettings;
	case NoMouseInputs:
		return ImGuiWindowFlags_NoMouseInputs;
	case MenuBar:
		return ImGuiWindowFlags_MenuBar;
	case HorizontalScrollbar:
		return ImGuiWindowFlags_HorizontalScrollbar;
	case NoFocusOnAppearing:
		return ImGuiWindowFlags_NoFocusOnAppearing;
	case NoBringToFrontOnFocus:
		return ImGuiWindowFlags_NoBringToFrontOnFocus;
	case AlwaysVerticalScrollbar:
		return ImGuiWindowFlags_AlwaysVerticalScrollbar;
	case AlwaysHorizontalScrollbar:
		return ImGuiWindowFlags_AlwaysHorizontalScrollbar;
	case AlwaysUseWindowPadding:
		return ImGuiWindowFlags_AlwaysUseWindowPadding;
	case NoNavInputs:
		return ImGuiWindowFlags_NoNavInputs;
	case NoNavFocus:
		return ImGuiWindowFlags_NoNavFocus;
	case UnsavedDocument:
		return ImGuiWindowFlags_UnsavedDocument;
	case NoNav:
		return ImGuiWindowFlags_NoNav;
	case NoDecoration:
		return ImGuiWindowFlags_NoDecoration;
	case NoInputs:
		return ImGuiWindowFlags_NoInputs;;
	case None:
		return ImGuiWindowFlags_None;
	default:
		UE_LOG(LogTemp, Warning, TEXT("'ImGuiWindowFlags UImGuiBPFL::GetFixedWidnowFlag(ImGui_WindowFlags Flag)' method just returned 'None' due to reching defailt case in switch on ImGui_WindowFlags. Probably new value was added to enum but not to switch."));
		return ImGuiWindowFlags_None;
		break;
	}
}

