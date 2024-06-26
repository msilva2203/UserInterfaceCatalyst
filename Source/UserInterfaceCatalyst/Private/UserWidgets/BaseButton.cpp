// © 2024 Marco Silva. All Rights Reserved.


#include "UserWidgets/BaseButton.h"

void UBaseButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BTN)
	{
		BTN->IsFocusable = false;

		BTN->OnClicked.AddDynamic(this, &UBaseButton::NativeOnClick);
		BTN->OnHovered.AddDynamic(this, &UBaseButton::NativeOnMouseHovered);
		BTN->OnUnhovered.AddDynamic(this, &UBaseButton::NativeOnMouseUnHovered);
	}
}

void UBaseButton::NativeOnClick()
{
	OnClick();

	OnClicked.Broadcast();
	OnClickHelper.Broadcast(NavContextIndex, NavIndex);

}

void UBaseButton::NativeOnHovered()
{
	OnHovered();
	OnButtonHovered.Broadcast();

}

void UBaseButton::NativeOnMouseHovered()
{
	OnMouseHovered();
	OnHoverHelper.Broadcast(NavContextIndex, NavIndex);

}

void UBaseButton::NativeOnUnHovered()
{
	OnUnHovered();
	OnButtonUnhovered.Broadcast();

}

void UBaseButton::NativeOnMouseUnHovered()
{
	OnMouseUnHovered();

}

void UBaseButton::SetNavIndex(int32 NewValue)
{
	NavIndex = NewValue;
}
