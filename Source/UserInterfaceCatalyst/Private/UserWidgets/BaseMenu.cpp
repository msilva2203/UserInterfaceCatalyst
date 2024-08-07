// © 2024 Marco Silva. All Rights Reserved.


#include "UserWidgets/BaseMenu.h"
#include "UserWidgets/BaseSubMenu.h"
#include "Kismet/KismetInputLibrary.h"

void UBaseMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetIsFocusable(true);
}

void UBaseMenu::NativeConstruct()
{
	Super::NativeConstruct();

}

FReply UBaseMenu::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	EUINavigation NavigationDirection;
	EUINavigationAction NavigationAction;

	// 1. Get key
	FKey Key = InKeyEvent.GetKey();

	if (Key.IsGamepadKey())
	{
		CatalystInputSubsystem->UpdateInputDeviceType(EInputDeviceType::Gamepad);
	}
	else
	{
		CatalystInputSubsystem->UpdateInputDeviceType(EInputDeviceType::MouseKeyboard);
	}

	// 2. Notify any key presses
	if (NativeOnAnyKeyPressed(Key)) return FReply::Handled();
	if (FocusedSubMenu)
	{
		if (FocusedSubMenu->NativeOnAnyKeyPressed(Key)) return FReply::Handled();
	}

	// 2. Get navigation action
	NavigationAction = UKismetInputLibrary::Key_GetNavigationActionFromKey(InKeyEvent);

	if (NavigationAction != EUINavigationAction::Invalid)
	{
		if (!InKeyEvent.IsRepeat())
			HandleActionInput(NavigationAction);
		return FReply::Handled();
	}

	// 3. Get navigation direction
	NavigationDirection = UKismetInputLibrary::Key_GetNavigationDirectionFromKey(InKeyEvent);

	if (NavigationDirection != EUINavigation::Invalid)
	{
		HandleDirectionInput(NavigationDirection);
		return FReply::Handled();
	}

	// 4. Check for custom actions
	uint8 CustomValue = 0;
	if (!IsInputBlocked())
	{
		if (GetCustomActionValue(InKeyEvent, CustomValue))
		{
			NativeOnActionInput(EMenuAction::Custom, CustomValue);
		}
	}

	if (FocusedSubMenu)
	{
		if (!FocusedSubMenu->IsInputBlocked())
		{
			if (FocusedSubMenu->GetCustomActionValue(InKeyEvent, CustomValue))
			{
				FocusedSubMenu->NativeOnActionInput(EMenuAction::Custom, CustomValue);
			}
		}
	}

	return FReply::Handled();
}

FReply UBaseMenu::NativeOnAnalogValueChanged(const FGeometry& MyGeometry, const FAnalogInputEvent& InAnalogEvent)
{
	EUINavigation NavigationDirection;

	NavigationDirection = UKismetInputLibrary::Key_GetNavigationDirectionFromAnalog(InAnalogEvent);
	
	if (NavigationDirection != EUINavigation::Invalid)
	{
		if (InAnalogEvent.GetKey().IsGamepadKey())
		{
			CatalystInputSubsystem->UpdateInputDeviceType(EInputDeviceType::Gamepad);
		}
		else
		{
			CatalystInputSubsystem->UpdateInputDeviceType(EInputDeviceType::MouseKeyboard);
		}
		HandleDirectionInput(NavigationDirection);
		return FReply::Handled();
	}

	return FReply::Handled();
}

FReply UBaseMenu::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& InMouseEvent)
{
	FKey Key = InMouseEvent.GetEffectingButton();

	if (Key.IsValid())
	{
		NativeOnAnyKeyPressed(Key);

		if (FocusedSubMenu)
			FocusedSubMenu->NativeOnAnyKeyPressed(Key);

		CatalystInputSubsystem->UpdateInputDeviceType(EInputDeviceType::MouseKeyboard);
	}

	return FReply::Handled();
}

FReply UBaseMenu::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Delta = InMouseEvent.GetCursorDelta();

	if (Delta.X != 0.0f || Delta.Y != 0.0f)
	{
		CatalystInputSubsystem->UpdateInputDeviceType(EInputDeviceType::MouseKeyboard);
	}

	return FReply::Handled();
}

void UBaseMenu::NativeOnDirectionInput(EMenuNavigationType Type, int32 Value)
{
	Super::NativeOnDirectionInput(Type, Value);

}

void UBaseMenu::NativeOnActionInput(EMenuAction Action, uint8 Custom)
{
	Super::NativeOnActionInput(Action, Custom);

}

void UBaseMenu::NativeOnShow()
{
	OnShow();
	OnMenuShown.Broadcast();
}

void UBaseMenu::NativeOnHide()
{
	OnHide();
	OnMenuHidden.Broadcast();
}

void UBaseMenu::FocusSubMenu(UBaseSubMenu* SubMenu)
{
	if (!SubMenu) return;

	if (FocusedSubMenu)
	{
		FocusedSubMenu->NativeOnMenuUnfocus();
	}

	FocusedSubMenu = SubMenu;
	FocusedSubMenu->NativeOnMenuFocus();
}

UBaseSubMenu* UBaseMenu::GetFocusedSubMenu() const
{
	return FocusedSubMenu;
}

void UBaseMenu::HandleActionInput(EUINavigationAction NavigationAction, uint8 Custom)
{
	if (!FocusedSubMenu) return;

	switch (NavigationAction)
	{
	case EUINavigationAction::Accept:
		NativeOnActionInput(EMenuAction::Accept);
		FocusedSubMenu->NativeOnActionInput(EMenuAction::Accept);
		break;
	case EUINavigationAction::Back:
		NativeOnActionInput(EMenuAction::Back);
		FocusedSubMenu->NativeOnActionInput(EMenuAction::Back);
		break;
	case EUINavigationAction::Invalid:
		NativeOnActionInput(EMenuAction::Custom, Custom);
		break;
	default:
		break;
	}
}

void UBaseMenu::HandleDirectionInput(EUINavigation NavigationDirection)
{
	if (!FocusedSubMenu) return;

	switch (NavigationDirection)
	{
	case EUINavigation::Left:
		NativeOnDirectionInput(EMenuNavigationType::Horizontal, -1);
		FocusedSubMenu->NativeOnDirectionInput(EMenuNavigationType::Horizontal, -1);
		break;
	case EUINavigation::Right:
		NativeOnDirectionInput(EMenuNavigationType::Horizontal, 1);
		FocusedSubMenu->NativeOnDirectionInput(EMenuNavigationType::Horizontal, 1);
		break;
	case EUINavigation::Up:
		NativeOnDirectionInput(EMenuNavigationType::Vertical, -1);
		FocusedSubMenu->NativeOnDirectionInput(EMenuNavigationType::Vertical, -1);
		break;
	case EUINavigation::Down:
		NativeOnDirectionInput(EMenuNavigationType::Vertical, 1);
		FocusedSubMenu->NativeOnDirectionInput(EMenuNavigationType::Vertical, 1);
		break;
	case EUINavigation::Next:
	case EUINavigation::Previous:
	case EUINavigation::Num:
	case EUINavigation::Invalid:
	default:
		break;
	}
}
