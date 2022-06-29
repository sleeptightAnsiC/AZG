// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiBPFL.h"
#include <imgui.h>
#include <string>

static bool bPrinting = false;

const FString NullMessage = ":(";
const FString NullData = "No Data";

//Public
// placeholders - test

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

void UImGuiBPFL::TestFunction()
{
	ImGui::Begin("Test Window");


	ImGui::Text("Siema0");
	ImGui::Text("Siema1");
	ImGui::Text("Siema2");
	ImGui::Text("Siema3");

	static bool bFlag = true;
	if (ImGui::BeginMenu("Test Menu", true))
	{
		static int radioData = 1;
		ImGui::RadioButton("Test Radio Button 0", &radioData, 0);
		ImGui::RadioButton("Test Radio Button 1", &radioData, 1);
		ImGui::RadioButton("Test Radio Button 2", &radioData, 2);
		ImGui::RadioButton("Test Radio Button 3", &radioData, 3);
		ImGui::RadioButton("Test Radio Button 4", &radioData, 4);
		ImGui::EndMenu();
	}

	ImGui::End();
}


//Public
// Front-End for blueprints

void UImGuiBPFL::StartPrintingMainWindow(FString Name, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties)
{
	if (ValidateWindowFunction(false, "StartPrintingWindow", Name, "You cannot start Printing another Window before closing the already existing one. Probably 'StopPrintingWindow()' is missing somewhere."))
	{
		bPrinting = true; //global flag
		ImGuiWindowFlags Flags = 0;
		for (ImGui_WindowFlags SimpleFlag : Properties)
			Flags += GetFixedWidnowFlag(SimpleFlag);
		std::string ConvertBuffer = TCHAR_TO_UTF8(*Name);
		ImGui::Begin(&*ConvertBuffer.begin(), nullptr, Flags);
	}
}

void UImGuiBPFL::StopPrintingMainWindow()
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
		ImGui::SameLine();
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
		ImGui::Separator();
}

void UImGuiBPFL::AddSpacingToWindow()
{
	if (ValidateWindowFunction(true, "AddSpacingToWindow", NullData, NullMessage))
		ImGui::Spacing();
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
		ImGui::SetNextWindowBgAlpha(BackgroundAlpha);
}

void UImGuiBPFL::SetNextWindowCollapseState(bool bCollapsed) //Do-poprawy/przemyœlenia - brak Condition
{
	if (ValidateWindowFunction(false, "SetNextWindowCollapseState", FString::Printf(TEXT("%s"), bCollapsed ? TEXT("TRUE") : TEXT("FALSE")), NullMessage))
			ImGui::SetNextWindowCollapsed(bCollapsed, ImGuiCond_Always);
}

void UImGuiBPFL::SetNextWindowFocused()
{
	if (ValidateWindowFunction(false, "SetNextWindowFocused", NullData, NullMessage))
		ImGui::SetNextWindowFocus();
}

void UImGuiBPFL::AddCollapsingHeaderToWindow(FString Name, bool& bOpen)
{
	bOpen = false;
	if (ValidateWindowFunction(true, "AddCollapsingHeaderToWindow", Name, NullMessage))
	{
		std::string ConvertBuffer = TCHAR_TO_UTF8(*Name);
		bOpen = ImGui::CollapsingHeader(&*ConvertBuffer.begin());
	}
}

void UImGuiBPFL::StartPrintingChild(FString Name, FVector2D SizeInPixels, bool bBorder, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties)
{
	if (ValidateWindowFunction(true, "StartPrintingChildWindow", Name, NullMessage))
	{
		ImGuiWindowFlags Flags = 0;
		for (ImGui_WindowFlags SimpleFlag : Properties)
			Flags += GetFixedWidnowFlag(SimpleFlag);
		ImGui::BeginChild(GetTypeHash(Name), ImVec2(SizeInPixels.X, SizeInPixels.Y), bBorder, Flags);
	}
}

void UImGuiBPFL::StopPrintingChild()
{
	if (ValidateWindowFunction(true, "StopPrintingChildWindow", NullData, NullMessage))
		ImGui::EndChild();
}

void UImGuiBPFL::StartPrintingGroup()
{
	if (ValidateWindowFunction(true, "StartPrintingGroup", NullData, NullMessage))
		ImGui::BeginGroup();
}

void UImGuiBPFL::StopPrintingGroup()
{
	if (ValidateWindowFunction(true, "StopPrintingGroup", NullData, NullMessage))
		ImGui::EndGroup();
}

void UImGuiBPFL::AddCheckboxToWindow(FString Label, bool bOldState, bool& bNewState, bool& bStateChanged)
{
	bStateChanged = false;
	if (ValidateWindowFunction(true, "AddCheckboxToWindow", NullData, NullMessage))
	{
		std::string ConvertBuffer = TCHAR_TO_UTF8(*Label);
		if (ImGui::Checkbox(&*ConvertBuffer.begin(), &bOldState))
			bStateChanged = true;
	}
	bNewState = bOldState;
}

void UImGuiBPFL::AddRadioButtonsToWindow(TSet<FString> Labels, int OldState, int& NewState, bool& bStateChanged)
{
	bStateChanged = false;
	if (ValidateWindowFunction(true, "AddRadioButtonsToWindow", NullData, NullMessage))
	{
		int labelIterator = 0;
		for (FString label : Labels)
		{
			std::string ConvertBuffer = TCHAR_TO_UTF8(*label);
			if (ImGui::RadioButton(&*ConvertBuffer.begin(), &OldState, labelIterator))
				bStateChanged = true;
			labelIterator++;
		}
	}
	NewState = OldState;
}

void UImGuiBPFL::AddBulletToWindow()
{
	if (ValidateWindowFunction(true, "AddBulletToWindow", NullData, NullMessage))
		ImGui::Bullet();
}

void UImGuiBPFL::AddProgressBarToWindow(FVector2D SizeInPixels, float Progress, FString Overlay)
{
	if (ValidateWindowFunction(true, "AddProgressBarToWindow", Overlay, NullMessage))
	{
		std::string ConvertBuffer = TCHAR_TO_UTF8(*Overlay);
		ImGui::ProgressBar
		(
			Progress,
			SizeInPixels.X == 0 && SizeInPixels.Y == 0 ? ImVec2(-FLT_MIN, 0) : ImVec2(SizeInPixels.X, SizeInPixels.Y),
			Overlay == " " ? nullptr : &*ConvertBuffer.begin()
		);
	}
}

void UImGuiBPFL::StartPrintingCombo(FString Label, FString Preview, bool& bOpen)
{
	bOpen = false;
	if (ValidateWindowFunction(true, "StartPrintingCombo", Label + " / " + Preview, NullMessage))
	{
		std::string ConvertBuffer_0 = TCHAR_TO_UTF8(*Label);
		std::string ConvertBuffer_1 = TCHAR_TO_UTF8(*Preview);
		if (ImGui::BeginCombo(&*ConvertBuffer_0.begin(), &*ConvertBuffer_1.begin()))
			bOpen = true;
	}
}

void UImGuiBPFL::StopPrintingCombo()
{
	if (ValidateWindowFunction(true, "StopPrintingCombo", NullData, NullMessage))
		ImGui::EndCombo();
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

