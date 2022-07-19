// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiBPFL.h"
#include <imgui.h>
//#include <imgui_internal.h>
#include <string>


//Public
// placeholders - test

void UImGuiBPFL::PrintSimpleWindow(FString Name, FString Text, FVector2D ScreenPosition)
{
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Name);
	UImGuiBPFL::SetNextWindowScreenPosition(ScreenPosition, Once);
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

void UImGuiBPFL::PrintSimpleWatermark(FString Name, FString Text, FVector2D ScreenPosition, bool bPrintTextOnly, float BackgroundAlpha)
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

		UImGuiBPFL::SetNextWindowScreenPosition(ScreenPosition, Always);
		ImGui::SetNextWindowBgAlpha(BackgroundAlpha);

		std::string ConvertBuffer
			= TCHAR_TO_UTF8(*Name);
		ImGui::Begin(&*ConvertBuffer.begin(), nullptr, flags);

		//ImGui::SetWindowFocus(&*ConvertBuffer.begin());	 //Always-On-Top Placeholder

		ConvertBuffer = TCHAR_TO_UTF8(*Text);
		ImGui::Text(&*ConvertBuffer.begin());

		ImGui::End();
}


//Public

// Context creation and access

/* Main */

// Demo, Debug, Information	
	
// Styles

/* Windows */

void UImGuiBPFL::StartPrintingMainWindow(FString Name, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties)
{
	char* NameConverted = TCHAR_TO_ANSI(*Name);

	ImGuiWindowFlags Flags = 0;
	for (ImGui_WindowFlags SimpleFlag : Properties)
		Flags += GetFixedWidnowFlag(SimpleFlag);

	ImGui::Begin(NameConverted, nullptr, Flags);
}

void UImGuiBPFL::StopPrintingMainWindow()
{
	ImGui::End();
}

/* Child Windows */

void UImGuiBPFL::StartPrintingChild(FString Name, FVector2D SizeInPixels, bool bBorder, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties)
{
	ImGuiWindowFlags Flags = 0;
	for (ImGui_WindowFlags SimpleFlag : Properties)
		Flags += GetFixedWidnowFlag(SimpleFlag);
	ImGui::BeginChild(GetTypeHash(Name), ImVec2(SizeInPixels.X, SizeInPixels.Y), bBorder, Flags);
}

void UImGuiBPFL::StopPrintingChild()
{
	ImGui::EndChild();
}

// Windows Utilities

/* Window manipulation */

void UImGuiBPFL::SetNextWindowScreenPosition(FVector2D ScreenPosition, ImGui_WindowConditions Condition)
{
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	if (ViewportSize.X > 0 && ViewportSize.Y > 0)
	{
		ImVec2 WindowPosition = GetScreenSizeInPixels(ScreenPosition);
		ImVec2 WindowPivot = GetRelativeScreenPosition(ScreenPosition);

		ImGui::SetNextWindowPos(WindowPosition, Condition, WindowPivot);
	}
}

void UImGuiBPFL::SetNextWindowBackgroundAlpha(float BackgroundAlpha)
{
	ImGui::SetNextWindowBgAlpha(BackgroundAlpha);
}

void UImGuiBPFL::SetNextWindowCollapseState(bool bCollapsed) //Do-poprawy/przemyœlenia - brak Condition
{
	ImGui::SetNextWindowCollapsed(bCollapsed, ImGuiCond_Always);
}

void UImGuiBPFL::SetNextWindowFocused()
{
	ImGui::SetNextWindowFocus();
}

// Content region
// Windows Scrolling
// Parameters stacks (shared)
// Parameters stacks (current window)
// Style read access

/* Cursor / Layout */

void UImGuiBPFL::AddSeparator()
{
	ImGui::Separator();
}

void UImGuiBPFL::StayInSameLine()
{
	ImGui::SameLine();
}

void UImGuiBPFL::AddSpacing()
{
	ImGui::Spacing();
}

void UImGuiBPFL::StartPrintingGroup()
{
	ImGui::BeginGroup();
}

void UImGuiBPFL::StopPrintingGroup()
{
	ImGui::EndGroup();
}

// ID stack/scopes


/* Widgets / Text */

void UImGuiBPFL::AddText(FString Text)
{
	char* TextConverted = TCHAR_TO_ANSI(*Text);
	ImGui::Text(TextConverted);
}

/* Widgets / Main */

bool UImGuiBPFL::AddButton(FString Name, FVector2D Size)
{
	char* NameConverted = TCHAR_TO_ANSI(*Name);
	ImVec2 SizeInPixels = GetScreenSizeInPixels(Size);

	return ImGui::Button(NameConverted, SizeInPixels);
}

bool UImGuiBPFL::AddCheckbox(FString Label, bool& CheckedBool)
{
	char* LabelConverted = TCHAR_TO_ANSI(*Label);
	return ImGui::Checkbox(LabelConverted, &CheckedBool);
}



// Widgets: Combo Box
// Widgets: Drag Sliders
// Widgets: Regular Sliders
// Widgets: Input with Keyboard
// Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little color square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
// Widgets: Trees
// Widgets: Selectables
// Widgets: List Boxes
// Widgets: Data Plotting
// Widgets: Value() Helpers.
// Widgets: Menus
// Tooltips
// Popups: begin/end functions
// Popups: open/close functions
// Popups: open+begin combined functions helpers
// Popups: query functions
// Tables
// Tables: Headers & Columns declaration
// Tables: Sorting
// Tables: Miscellaneous functions
// Legacy Columns API (prefer using Tables!)
// Tab Bars, Tabs
// Logging/Capture
// Drag and Drop
// Disabling [BETA API]
// Clipping
// Focus, Activation
// Item/Widgets Utilities and Query Functions
// Viewports
// Miscellaneous Utilities
// Text Utilities
// Color Utilities
// Inputs Utilities: Keyboard
// Inputs Utilities: Mouse
// Clipboard Utilities
// Settings/.Ini Utilities
// Debug Utilities
// Memory Allocators


void UImGuiBPFL::AddCollapsingHeader(FString Name, bool& bOpen)
{
	bOpen = false;
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Name);
	bOpen = ImGui::CollapsingHeader(&*ConvertBuffer.begin());
}

void UImGuiBPFL::AddRadioButtons(TSet<FString> Labels, int OldState, int& NewState, bool& bStateChanged)
{
	bStateChanged = false;
	int labelIterator = 0;
	for (FString label : Labels)
	{
		std::string ConvertBuffer = TCHAR_TO_UTF8(*label);
		if (ImGui::RadioButton(&*ConvertBuffer.begin(), &OldState, labelIterator))
			bStateChanged = true;
		labelIterator++;
	}
	NewState = OldState;
}

void UImGuiBPFL::AddBullet()
{
	ImGui::Bullet();
}

void UImGuiBPFL::AddProgressBar(FVector2D SizeInPixels, float Progress, FString Overlay)
{
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Overlay);
	ImGui::ProgressBar
	(
		Progress,
		SizeInPixels.X == 0 && SizeInPixels.Y == 0 ? ImVec2(-FLT_MIN, 0) : ImVec2(SizeInPixels.X, SizeInPixels.Y),
		Overlay == " " ? nullptr : &*ConvertBuffer.begin()
	);
}

void UImGuiBPFL::StartPrintingCombo(FString Label, FString Preview, bool& bOpen)
{
	bOpen = false;
	std::string ConvertBuffer_0 = TCHAR_TO_UTF8(*Label);
	std::string ConvertBuffer_1 = TCHAR_TO_UTF8(*Preview);
	if (ImGui::BeginCombo(&*ConvertBuffer_0.begin(), &*ConvertBuffer_1.begin()))
		bOpen = true;
}

void UImGuiBPFL::StopPrintingCombo()
{
	ImGui::EndCombo();
}

void UImGuiBPFL::StartPrintingMenu(FString Label, bool bEnabled, bool& bOpen)
{
	bOpen = false;
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Label);
	bOpen =
		ImGui::BeginMenu(&*ConvertBuffer.begin(), bEnabled);
}

void UImGuiBPFL::StopPrintingMenu()
{
	ImGui::EndMenu();
}

void UImGuiBPFL::StartAddingToMenuBar()
{
	ImGui::BeginMenuBar();
}

void UImGuiBPFL::StopAddingToMenuBar()
{
	ImGui::EndMenuBar();
}

void UImGuiBPFL::StartPrintingMainMenuBar()
{
	ImGui::BeginMainMenuBar();
}

void UImGuiBPFL::StopPrintingMainMenuBar()
{
	ImGui::EndMainMenuBar();	
}

void UImGuiBPFL::AddMainMenuItem(FString Label, FString Shortcut, bool bSelected, bool bEnabled, bool& bClicked)
{
	std::string LabelConvertBuffer = TCHAR_TO_UTF8(*Label);
	std::string ShortcutConvertBuffer = TCHAR_TO_UTF8(*Shortcut);
	bClicked = 
		ImGui::MenuItem(&*LabelConvertBuffer.begin(), &*LabelConvertBuffer.begin(), bSelected, bEnabled);
}

void UImGuiBPFL::AddDragFloatArray(FString Label, UPARAM(ref) TArray<float>& DraggedArrayReference, float DragSpeed, float MinValue, float MaxValue)
{
	float* PassByRefArray = new float[DraggedArrayReference.Num()];
	for (int i = 0; i < DraggedArrayReference.Num(); i++)
		PassByRefArray[i] = DraggedArrayReference[i];
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Label);
	ImGui::DragScalarN(&*ConvertBuffer.begin(), ImGuiDataType_Float, PassByRefArray, DraggedArrayReference.Num(), DragSpeed, &MinValue, &MaxValue);
	for (int i = 0; i < DraggedArrayReference.Num(); i++)
		DraggedArrayReference[i] = PassByRefArray[i];
	delete[] PassByRefArray;
}

void UImGuiBPFL::AddDragIntArray(FString Label, UPARAM(ref) TArray<int>& DraggedArrayReference, float DragSpeed, int MinValue, int MaxValue)
{
	int* PassByRefArray = new int[DraggedArrayReference.Num()];
	for (int i = 0; i < DraggedArrayReference.Num(); i++)
		PassByRefArray[i] = DraggedArrayReference[i];
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Label);
	ImGui::DragScalarN(&*ConvertBuffer.begin(), ImGuiDataType_S32, PassByRefArray, DraggedArrayReference.Num(), DragSpeed, &MinValue, &MaxValue);
	for (int i = 0; i < DraggedArrayReference.Num(); i++)
		DraggedArrayReference[i] = PassByRefArray[i];
	delete[] PassByRefArray;
}

void UImGuiBPFL::AddSliderFloatArray(FString Label, UPARAM(ref) TArray<float>& DraggedArrayReference, float MinValue, float MaxValue)
{
	float* PassByRefArray = new float[DraggedArrayReference.Num()];
	for (int i = 0; i < DraggedArrayReference.Num(); i++)
		PassByRefArray[i] = DraggedArrayReference[i];
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Label);
	ImGui::SliderScalarN(&*ConvertBuffer.begin(), ImGuiDataType_Float, PassByRefArray, DraggedArrayReference.Num(), &MinValue, &MaxValue);
	for (int i = 0; i < DraggedArrayReference.Num(); i++)
		DraggedArrayReference[i] = PassByRefArray[i];
	delete[] PassByRefArray;
}

void UImGuiBPFL::AddSliderIntArray(FString Label, UPARAM(ref) TArray<int>& DraggedArrayReference, int MinValue, int MaxValue)
{
	int* PassByRefArray = new int[DraggedArrayReference.Num()];
	for (int i = 0; i < DraggedArrayReference.Num(); i++)
		PassByRefArray[i] = DraggedArrayReference[i];
	std::string ConvertBuffer = TCHAR_TO_UTF8(*Label);
	ImGui::SliderScalarN(&*ConvertBuffer.begin(), ImGuiDataType_S32, PassByRefArray, DraggedArrayReference.Num(), &MinValue, &MaxValue);
	for (int i = 0; i < DraggedArrayReference.Num(); i++)
		DraggedArrayReference[i] = PassByRefArray[i];
	delete[] PassByRefArray;
}

void UImGuiBPFL::AddInputTextBox(FString Label, FString Hint, UPARAM(ref) FString& InputedString, int MaxCharactersCount, FVector2D BoxSize, TSet<TEnumAsByte<ImGui_InputTextType>> Properties, bool& bCallback)
{
	char* LabelConverted = TCHAR_TO_ANSI(*Label);
	char* HintConverted = TCHAR_TO_ANSI(*Hint);
	char* InputedFStingConverted = TCHAR_TO_ANSI(*InputedString);

	int MaxCharactersCountConverted = MaxCharactersCount == 0 ? sizeof(InputedFStingConverted) : MaxCharactersCount;
	ImVec2 BoxSizeConverted = GetScreenSizeInPixels(BoxSize);

	ImGuiInputTextFlags Flags = 0;
	for (ImGui_InputTextType SimpleFlag : Properties)
		Flags += GetFixedInputTextFlag(SimpleFlag);

	bCallback =
		ImGui::InputTextExSafe(LabelConverted, HintConverted, InputedFStingConverted, MaxCharactersCountConverted, BoxSizeConverted, Flags);

	InputedString = FString(ANSI_TO_TCHAR(InputedFStingConverted));
}

//TEST Func

void UImGuiBPFL::TestFunction()
{
	ImGui::Begin("Test Window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	static char teststring[] = "hello";
	if (ImGui::InputTextExSafe("test input box", "test hint", teststring, 100, ImVec2(0, 0), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		FString Message = "Inputed";
		GEngine->AddOnScreenDebugMessage((int32)(GetTypeHash(Message)), 2, FColor::Red, Message);
		UE_LOG(LogTemp, Error, TEXT("Inputed"))
	}
	ImGui::End();
	//ImGui::InputText()
}

//Private

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

ImGuiInputTextFlags UImGuiBPFL::GetFixedInputTextFlag(ImGui_InputTextType Flag)
{
	switch (Flag)
	{
	case InputText_None:
		return ImGuiInputTextFlags_None;
	case InputText_CharsDecimal:
		return ImGuiInputTextFlags_CharsDecimal;
	case InputText_Uppercases:
		return ImGuiInputTextFlags_CharsUppercase;
	case InputText_NoBlanks:
		return ImGuiInputTextFlags_CharsNoBlank;
	case InputText_AutoSelectAll:
		return ImGuiInputTextFlags_AutoSelectAll;
	case InputText_EnterReturnsTrue:
		return ImGuiInputTextFlags_EnterReturnsTrue;
	case InputText_AllowTabInput:
		return ImGuiInputTextFlags_AllowTabInput;
	case InputText_CtrlEnterForNewLine:
		return ImGuiInputTextFlags_CtrlEnterForNewLine;
	case InputText_NoHorizontalScroll:
		return ImGuiInputTextFlags_NoHorizontalScroll;
	case InputText_ReadOnly:
		return ImGuiInputTextFlags_ReadOnly;
	case InputText_Password:
		return ImGuiInputTextFlags_Password;
	case InputText_NoUndoRedo:
		return ImGuiInputTextFlags_NoUndoRedo;
	case InputText_CharsScientific:
		return ImGuiInputTextFlags_CharsScientific;
	default:
		FString Message = "'ImGuiInputTextFlags UImGuiBPFL::GetFixedInputTextFlag(ImGui_InputTextType Flag)' method just returned 'None' due to reching default case in switch on ImGui_InputTextType. Probably new value was added to enum but not to switch.";
		GEngine->AddOnScreenDebugMessage((int32)(GetTypeHash(Message)), 0, FColor::Red, Message);
		return ImGuiWindowFlags_None;
		break;
	}
}

ImVec2 UImGuiBPFL::GetScreenSizeInPixels(FVector2D ScreenSize)
{
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ImVec2 Pixels;

	GEngine->AddOnScreenDebugMessage((int32)(GetTypeHash(ViewportSize.ToString())), 0, FColor::Red, ViewportSize.ToString());

	if (ScreenSize.X < 0 || ScreenSize.X > ViewportSize.X)
		Pixels.x = 0;
	else
	{
		if (ScreenSize.X <= 1)
			Pixels.x = (float)(ScreenSize.X * ViewportSize.X);
		else
			Pixels.x = (float)(ScreenSize.X);
	}

	if (ScreenSize.Y < 0 || ScreenSize.Y > ViewportSize.Y)
		Pixels.y = 0;
	else
	{
		if (ScreenSize.Y <= 1)
			Pixels.y = (float)(ScreenSize.Y * ViewportSize.Y);
		else
			Pixels.y = (float)(ScreenSize.Y);
	}

	FVector2D test = { Pixels.x, Pixels.y };
	GEngine->AddOnScreenDebugMessage((int32)(GetTypeHash(test.ToString())), 0, FColor::Red, test.ToString());

	return Pixels;
}

ImVec2 UImGuiBPFL::GetRelativeScreenPosition(FVector2D ScreenSize)
{
	FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ImVec2 RelativePosition;

	GEngine->AddOnScreenDebugMessage((int32)(GetTypeHash(ViewportSize.ToString())), 0, FColor::Red, ViewportSize.ToString());

	if (ScreenSize.X < 0 || ScreenSize.X > ViewportSize.X)
		RelativePosition.x = 0;
	else
	{
		if (ScreenSize.X <= 1)
			RelativePosition.x = (float)(ScreenSize.X);
		else
			RelativePosition.x = (float)(ScreenSize.X / ViewportSize.X);
	}

	if (ScreenSize.Y < 0 || ScreenSize.Y > ViewportSize.Y)
		RelativePosition.y = 0;
	else
	{
		if (ScreenSize.Y <= 1)
			RelativePosition.y = (float)(ScreenSize.Y);
		else
			RelativePosition.y = (float)(ScreenSize.Y / ViewportSize.Y);
	}

	FVector2D test = { RelativePosition.x, RelativePosition.y };
	GEngine->AddOnScreenDebugMessage((int32)(GetTypeHash(test.ToString())), 0, FColor::Red, test.ToString());

	return RelativePosition;
}