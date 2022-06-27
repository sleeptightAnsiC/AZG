// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiBPFL.h"
#include <imgui.h>
#include <string>

static bool bPrinting = false;

const FString NullMessage = ":(";
const FString NullData = "No Data";

//Public

void UImGuiBPFL::PrintSimpleWindow(FString Name, FString Text, FVector2D RelativeScreenPosition)
{
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Name);
	UImGuiBPFL::SetNextWindowRelativePosition(RelativeScreenPosition, Once);
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

		UImGuiBPFL::SetNextWindowRelativePosition(RelativeScreenPosition, Always);
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
	if (ValidateWindowFunction(false, "StartPrintingWindow", Name, "You cannot start Printing another Window before closing the already existing one. Probably 'StopPrintingWindow()' is missing somewhere."))
	{
		bPrinting = true;

		ImGuiWindowFlags Flags = 0;
		for (ImGui_WindowFlags SimpleFlag : Properties)
		{
			Flags += GetFixedWidnowFlag(SimpleFlag);
		}

		std::string ConvertBuffer = TCHAR_TO_UTF8(*Name);
		ImGui::Begin(&*ConvertBuffer.begin(), nullptr, Flags);

		/*
		if (ImGui::Button("200x200")) { ImGui::SetWindowSize(ImVec2(200, 200)); } ImGui::SameLine();
		if (ImGui::Button("500x500")) { ImGui::SetWindowSize(ImVec2(500, 500)); } ImGui::SameLine();
		if (ImGui::Button("800x200")) { ImGui::SetWindowSize(ImVec2(800, 200)); }
		*/
	}
}

void UImGuiBPFL::StopPrintingWindow()
{
	if (ValidateWindowFunction(true, "StopPrintingWindow", NullData, NullMessage))
	{
		ImGui::End();
		bPrinting = false;
	}
}

void UImGuiBPFL::AddTextToWindow(FString Text)
{
	if (ValidateWindowFunction(true, "AddTextToWindow", Text, NullMessage))
	{
		std::string ConvertBuffer = TCHAR_TO_UTF8(*Text);
		ImGui::Text(&*ConvertBuffer.begin());
	}
}

void UImGuiBPFL::StayInSameWindowLine()
{
	if (ValidateWindowFunction(true, "StayInSameWindowLine", NullData, NullMessage))
	{
		ImGui::SameLine();
	}
}

void UImGuiBPFL::AddButtonToWindow(FString Name, bool& bClicked)
{
	bClicked = false;
	if (ValidateWindowFunction(true, "AddButtonToWindow", Name, NullMessage))
	{
		std::string ConvertBuffer = TCHAR_TO_UTF8(*Name);
		bClicked = ImGui::Button(&*ConvertBuffer.begin());
	}
}

void UImGuiBPFL::AddSeparatorToWindow()
{
	if (ValidateWindowFunction(true, "AddSeparatorToWindow", NullData, NullMessage))
	{
		ImGui::Separator();
	}
}

void UImGuiBPFL::AddSpacingToWindow()
{
	if (ValidateWindowFunction(true, "AddSpacingToWindow", NullData, NullMessage))
	{
		ImGui::Spacing();
	}
}

void UImGuiBPFL::SetNextWindowRelativePosition(FVector2D RelativeScreenPosition, ImGui_WindowConditions Condition)
{
	if (ValidateWindowFunction(false, "SetNextWindowRelativePosition", FString::Printf(TEXT("%s"), *RelativeScreenPosition.ToString()), NullMessage))
	{
		FVector2D ViewportSize
			= FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		if (ViewportSize.X > 0 && ViewportSize.Y > 0)
		{
			RelativeScreenPosition.X = FMath::Clamp(RelativeScreenPosition.X, 0, 1);
			RelativeScreenPosition.Y = FMath::Clamp(RelativeScreenPosition.Y, 0, 1);

			ImVec2 window_pos, window_pos_pivot;
			window_pos.x = RelativeScreenPosition.X * ViewportSize.X;
			window_pos.y = RelativeScreenPosition.Y * ViewportSize.Y;
			window_pos_pivot.x = RelativeScreenPosition.X;
			window_pos_pivot.y = RelativeScreenPosition.Y;

			ImGui::SetNextWindowPos(window_pos, Condition, window_pos_pivot);
		}
	}
}

void UImGuiBPFL::SetNextWindowBackgroundAlpha(float BackgroundAlpha)
{
	if (ValidateWindowFunction(false, "SetNextWindowBackgroundAlpha", FString::Printf(TEXT("%f"), BackgroundAlpha), NullMessage))
	{
		ImGui::SetNextWindowBgAlpha(BackgroundAlpha);
	}
}

void UImGuiBPFL::SetNextWindowCollapseState(bool bCollapsed) //Do-poprawy/przemyœlenia - brak Condition
{
	if (ValidateWindowFunction(false, "SetNextWindowCollapseState", FString::Printf(TEXT("%s"), bCollapsed ? TEXT("TRUE") : TEXT("FALSE")), NullMessage))
	{
			ImGui::SetNextWindowCollapsed(bCollapsed, ImGuiCond_Always);
	}
}

void UImGuiBPFL::SetNextWindowFocused()
{
	if (ValidateWindowFunction(false, "SetNextWindowFocused", NullData, NullMessage))
	{
		ImGui::SetNextWindowFocus();
	}
}




//Private


bool UImGuiBPFL::ValidateWindowFunction(bool bShallPrintingFlagBeSet, FString FunctionName, FString PassedData, FString AdditionalErrorMessage)
{
	if (bShallPrintingFlagBeSet == bPrinting)
		return true;
	else
	{
		FString Message = FString::Printf
		(
			TEXT("'ImGuiBPFL::%s' function is not executing due to bPrinting flag being set to %s / %s / Additional info: %s"), *FunctionName, bPrinting ? TEXT("TRUE") : TEXT("FALSE"), *PassedData, * AdditionalErrorMessage
		);
		//UE_LOG(LogTemp, Error, TEXT("%s"), *Message)	//logowanie na Tick'u to s³aby pomys³
		GEngine->AddOnScreenDebugMessage((int32)(GetTypeHash(Message)), 0, FColor::Red, Message);
		return false;
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

