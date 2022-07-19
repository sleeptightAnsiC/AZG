// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <ImGui.h>
#include "ImGuiBPFL.generated.h"


/* structs */

UENUM(BlueprintType)
enum ImGui_WindowFlags
{
	None                         UMETA(DisplayName = "Null"),
	NoTitleBar                   UMETA(DisplayName = "NoTitleBar"),                  // Disable title-bar
	NoResize                     UMETA(DisplayName = "NoResize"),                    // Disable user resizing with the lower-right grip
	NoMove                       UMETA(DisplayName = "NoMove"),                      // Disable user moving the window
	NoScrollbar                  UMETA(DisplayName = "NoScrollbar"),                 // Disable scrollbars (window can still scroll with mouse or programmatically)
	NoScrollWithMouse            UMETA(DisplayName = "NoScrollWithMouse"),           // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
	NoCollapse                   UMETA(DisplayName = "NoCollapse"),                  // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
	AlwaysAutoResize             UMETA(DisplayName = "AlwaysAutoResize"),            // Resize every window to its content every frame
	NoBackground                 UMETA(DisplayName = "NoBackground"),                // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
	NoSavedSettings              UMETA(DisplayName = "NoSavedSettings"),             // Never load/save settings in .ini file
	NoMouseInputs                UMETA(DisplayName = "NoMouseInputs"),               // Disable catching mouse, hovering test with pass through.
	MenuBar                      UMETA(DisplayName = "MenuBar"),                     // Has a menu-bar
	HorizontalScrollbar          UMETA(DisplayName = "HorizontalScrollbar"),         // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
	NoFocusOnAppearing           UMETA(DisplayName = "NoFocusOnAppearing"),          // Disable taking focus when transitioning from hidden to visible state
	NoBringToFrontOnFocus        UMETA(DisplayName = "NoBringToFrontOnFocus"),       // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
	AlwaysVerticalScrollbar      UMETA(DisplayName = "AlwaysVerticalScrollbar"),     // Always show vertical scrollbar (even if ContentSize.y < Size.y)
	AlwaysHorizontalScrollbar    UMETA(DisplayName = "AlwaysHorizontalScrollbar"),   // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
	AlwaysUseWindowPadding       UMETA(DisplayName = "AlwaysUseWindowPadding"),      // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)
	NoNavInputs                  UMETA(DisplayName = "NoNavInputs"),                 // No gamepad/keyboard navigation within the window
	NoNavFocus                   UMETA(DisplayName = "NoNavFocus"),                  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
	UnsavedDocument              UMETA(DisplayName = "UnsavedDocument"),             // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
	NoNav                        UMETA(DisplayName = "NoNav"),
	NoDecoration                 UMETA(DisplayName = "NoDecoration"),
	NoInputs                     UMETA(DisplayName = "NoInputs")
};

UENUM(BlueprintType)
enum ImGui_WindowConditions
{
	Nothing = ImGuiCond_None				UMETA(DisplayName = "Null"),
	Once = ImGuiCond_Once					UMETA(DisplayName = "Once"),
	Always = ImGuiCond_Always				UMETA(DisplayName = "Always"),
	FirstUseEver = ImGuiCond_FirstUseEver	UMETA(DisplayName = "FirstUseEver"),
	Appearing = ImGuiCond_Appearing			UMETA(DisplayName = "Appearing")
};


UENUM(BlueprintType)
enum ImGui_DragType
{
	Drag_Float		UMETA(DisplayName = "Float"),
	Drag_Int		UMETA(DisplayName = "Int"),
	Drag_Vector2D	UMETA(DisplayName = "Vector 2D"),
	Drag_Vector		UMETA(DisplayName = "Vector"),
	Drag_Vector4	UMETA(DisplayName = "Vector 4"),
	Drag_Rotator	UMETA(DisplayName = "Rotator"),
	Drag_Transform	UMETA(DisplayName = "Transform"),
	Drag_Color		UMETA(DisplayName = "Color")
};

UENUM(BlueprintType)
enum ImGui_InputTextType
{
	InputText_None					UMETA(DisplayName = "NULL"),				//ImGuiInputTextFlags_None
	InputText_CharsDecimal			UMETA(DisplayName = "DecimalChars"),		//ImGuiInputTextFlags_CharsDecimal        // Allow 0123456789.+-*/
	//not-needed																//ImGuiInputTextFlags_CharsHexadecimal    // Allow 0123456789ABCDEFabcdef
	InputText_Uppercases			UMETA(DisplayName = "Uppercases"),			//ImGuiInputTextFlags_CharsUppercase      // Turn a..z into A..Z
	InputText_NoBlanks				UMETA(DisplayName = "NoBlanks"),			//ImGuiInputTextFlags_CharsNoBlank        // Filter out spaces, tabs
	InputText_AutoSelectAll			UMETA(DisplayName = "AutoSelectAll"),		//ImGuiInputTextFlags_AutoSelectAll       // Select entire text when first taking mouse focus
	InputText_EnterReturnsTrue		UMETA(DisplayName = "EnterReturnsTrue"),	//ImGuiInputTextFlags_EnterReturnsTrue    // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider looking at the IsItemDeactivatedAfterEdit() function.
	//not-needed																//ImGuiInputTextFlags_CallbackCompletion  // Callback on pressing TAB (for completion handling)
	//not-needed																//ImGuiInputTextFlags_CallbackHistory     // Callback on pressing Up/Down arrows (for history handling)
	//not-needed																//ImGuiInputTextFlags_CallbackAlways      // Callback on each iteration. User code may query cursor position, modify text buffer.
	//not-needed																//ImGuiInputTextFlags_CallbackCharFilter  // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
	InputText_AllowTabInput			UMETA(DisplayName = "AllowTabInput"),		//ImGuiInputTextFlags_AllowTabInput       // Pressing TAB input a '\t' character into the text field
	InputText_CtrlEnterForNewLine	UMETA(DisplayName = "CtrlEnterForNewLine"),	//ImGuiInputTextFlags_CtrlEnterForNewLine // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
	InputText_NoHorizontalScroll	UMETA(DisplayName = "NoHorizontalScroll"),	//ImGuiInputTextFlags_NoHorizontalScroll  // Disable following the cursor horizontally
	//not-needed																//ImGuiInputTextFlags_AlwaysOverwrite     // Overwrite mode
	InputText_ReadOnly				UMETA(DisplayName = "ReadOnly"),			//ImGuiInputTextFlags_ReadOnly            // Read-only mode
	InputText_Password				UMETA(DisplayName = "Password"),			//ImGuiInputTextFlags_Password            // Password mode, display all characters as '*'
	InputText_NoUndoRedo			UMETA(DisplayName = "NoUndoRedo"),			//ImGuiInputTextFlags_NoUndoRedo          // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
	InputText_CharsScientific		UMETA(DisplayName = "ScientificChars")		//ImGuiInputTextFlags_CharsScientific     // Allow 0123456789.+-*/eE (Scientific notation input)
	//not-needed																//ImGuiInputTextFlags_CallbackResize      // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
	//not-needed																//ImGuiInputTextFlags_CallbackEdit        // Callback on any edit (note that InputText() already returns true on edit, the callback is useful mainly to manipulate the underlying buffer while focus is active)
};



UCLASS()
class IMGUI_API UImGuiBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//placeholders / test

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Placeholders", meta = (DevelopmentOnly))
	static void PrintSimpleWindow(FString Name, FString Text, FVector2D ScreenPosition);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Placeholders", meta = (DevelopmentOnly))
	static void PrintSimpleWatermark(FString Name, FString Text, FVector2D ScreenPosition, bool bPrintTextOnly, float BackgroundAlpha);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Placeholders", meta = (DevelopmentOnly))
	static void TestFunction();


	/* - Functions for Blueprint Graphs -	*/

// Context creation and access

/* Main	*/

// Demo, Debug, Information		
// Styles

/* Windows */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Raw", meta = (DevelopmentOnly))
	static void StartPrintingMainWindow(FString Name, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Raw", meta = (DevelopmentOnly))
	static void StopPrintingMainWindow();

/* Child Windows */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Raw", meta = (DevelopmentOnly))
	static void StartPrintingChild(FString Name, FVector2D SizeInPixels, bool bBorder, TSet<TEnumAsByte<ImGui_WindowFlags>> Properties);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Raw", meta = (DevelopmentOnly))
	static void StopPrintingChild();

// Windows Utilities

/* Window manipulation */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Safe", meta = (DevelopmentOnly))
	static void SetNextWindowScreenPosition(FVector2D ScreenPosition, ImGui_WindowConditions Condition = Always);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Safe", meta = (DevelopmentOnly))
	static void SetNextWindowBackgroundAlpha(float BackgroundAlpha);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Safe", meta = (DevelopmentOnly))
	static void SetNextWindowCollapseState(bool bCollapsed);  //Do-poprawy/przemyœlenia - brak Condition

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Safe", meta = (DevelopmentOnly))
	static void SetNextWindowFocused();

// Content region
// Windows Scrolling
// Parameters stacks (shared)
// Parameters stacks (current window)
// Style read access

/* Cursor / Layout */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Safe", meta = (DevelopmentOnly))
	static void AddSeparator();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Safe", meta = (DevelopmentOnly))
	static void StayInSameLine();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Safe", meta = (DevelopmentOnly))
	static void AddSpacing();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Raw", meta = (DevelopmentOnly))
	static void StartPrintingGroup();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Raw", meta = (DevelopmentOnly))
	static void StopPrintingGroup();

// ID stack/scopes

/* Widgets / Text */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Safe", meta = (DevelopmentOnly))
	static void AddText(FString Text);

/* Widgets / Main */

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Raw", meta = (DevelopmentOnly))
	static UPARAM(DisplayName = "bClicked") bool AddButton(FString Name, FVector2D Size);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions|Raw", meta = (DevelopmentOnly))
	static UPARAM(DisplayName = "bClicked") bool AddCheckbox(FString Label, UPARAM(ref) bool& CheckedBool);

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

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void AddCollapsingHeader(FString Name, bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void AddRadioButtons(TSet<FString> Labels, int OldState, int& NewState, bool& bStateChanged);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void AddBullet();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void AddProgressBar(FVector2D SizeInPixels, float Progress, FString Overlay = " ");

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void StartPrintingCombo(FString Label, FString Preview, bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void StopPrintingCombo();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void StartPrintingMenu(FString Label, bool bEnabled, bool& bOpen);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void StopPrintingMenu();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void StartAddingToMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void StopAddingToMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void StartPrintingMainMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void StopPrintingMainMenuBar();

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void AddMainMenuItem(FString Label, FString Shortcut, bool bSelected, bool bEnabled, bool& bClicked);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void AddDragFloatArray(FString Label, UPARAM(ref) TArray<float>& DraggedArrayReference, float DragSpeed = 1.0f, float MinValue = 0.0f, float MaxValue = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void AddDragIntArray(FString Label, UPARAM(ref) TArray<int>& DraggedArrayReference, float DragSpeed = 1.0f, int MinValue = 0, int MaxValue = 0);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void AddSliderFloatArray(FString Label, UPARAM(ref) TArray<float>& DraggedArrayReference, float MinValue = 0.0f, float MaxValue = 100.0f);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void AddSliderIntArray(FString Label, UPARAM(ref) TArray<int>& DraggedArrayReference, int MinValue = 0, int MaxValue = 100);

	UFUNCTION(BlueprintCallable, Category = "DearImGui|C++ Functions", meta = (DevelopmentOnly))
	static void AddInputTextBox(FString Label, FString Hint, UPARAM(ref) FString& InputedString, int MaxCharactersCount, FVector2D BoxSize, TSet<TEnumAsByte<ImGui_InputTextType>> Properties, bool& bCallback);	  //finish me

private:

    static ImGuiWindowFlags GetFixedWidnowFlag(ImGui_WindowFlags Flag);	  

	static ImGuiInputTextFlags GetFixedInputTextFlag(ImGui_InputTextType Flag);

	static ImVec2 GetScreenSizeInPixels(FVector2D ScreenSize = FVector2D(0, 0));

	static ImVec2 GetRelativeScreenPosition(FVector2D ScreenSize = FVector2D(0, 0));
};







