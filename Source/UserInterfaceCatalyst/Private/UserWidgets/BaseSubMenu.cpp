// © 2024 Marco Silva. All Rights Reserved.


#include "UserWidgets/BaseSubMenu.h"
#include "UserWidgets/BaseButton.h"

void UBaseSubMenu::NativeConstruct()
{
	Super::NativeConstruct();

}

void UBaseSubMenu::NativeOnDirectionInput(EMenuNavigationType Type, int32 Value)
{
	OnDirectionInput(Type, Value);

}

void UBaseSubMenu::NativeOnActionInput(EMenuAction Action, uint8 Custom)
{
	OnActionInput(Action, Custom);

	if (Action == EMenuAction::Back)
	{
		OnBack.Broadcast();
	}
}

void UBaseSubMenu::NativeOnMenuFocus()
{
	SetVisibility(FocusedVisibility);
	OnMenuFocus();

}

void UBaseSubMenu::NativeOnMenuUnfocus()
{
	SetVisibility(UnfocusedVisibility);
	OnMenuUnfocus();

}

int32 UBaseSubMenu::CreateNavContext(const TArray<UBaseButton*>& Buttons, const FNavContextParams& Params)
{
	FNavigationContext NavContext;

	NavContext.Params = Params;
	NavContext.Buttons = Buttons;
	NavContext.NavIndex = 0;

	int32 Index = NavContexts.Add(NavContext);

	for (auto& Btn : NavContext.Buttons)
	{
		Btn->NativeOnUnHovered();
		Btn->NavContextIndex = Index;

		Btn->OnHoverHelper.AddDynamic(this, &UBaseSubMenu::OnContextButtonHovered);
		Btn->OnClickHelper.AddDynamic(this, &UBaseSubMenu::OnContextButtonClicked);
	}

	UpdateNavContext(Index, 0, true);
	return Index;
}

int32 UBaseSubMenu::UpdateNavContext(int32 ContextIndex, int32 Value, bool bForce)
{
	FNavigationContext* NavContext = &NavContexts[ContextIndex];

	if (NavContext)
	{
		int32 Num = NavContext->Buttons.Num();
		if (Value < 0 || Value > Num - 1)
		{
			if (NavContext->Params.bCircularNavigation)
			{
				if (Value < 0)
				{
					Value = Num - 1;
				}
				else
				{
					Value = 0;
				}
			}
			else
			{
				Value = FMath::Clamp<int32>(Value, 0, Num - 1);
			}
		}
		if (Value != NavContext->NavIndex || bForce)
		{
			NavContext->Buttons[NavContext->NavIndex]->NativeOnUnHovered();
			NavContext->Buttons[Value]->NativeOnHovered();
			NavContext->NavIndex = Value;

			OnNavContextUpdated.Broadcast(ContextIndex, Value);
		}
	}
	return Value;
}

int32 UBaseSubMenu::OffsetNavContext(int32 ContextIndex, int32 Value, EMenuNavigationType Type)
{
	int32 NewIndex = -1;
	FNavigationContext* NavContext = &NavContexts[ContextIndex];

	if (NavContext)
	{
		int32 Multiplier = NavContext->Params.VerticalMultiplier;
		if (Type != EMenuNavigationType::Vertical)
		{
			Multiplier = NavContext->Params.HorizontalMultiplier;
		}
		Value *= Multiplier;

		NewIndex = NavContext->NavIndex + Value;
		NewIndex = UpdateNavContext(ContextIndex, NewIndex);
	}
	return NewIndex;
}

void UBaseSubMenu::ClickNavContext(int32 ContextIndex)
{
	FNavigationContext* NavContext = &NavContexts[ContextIndex];

	if (NavContext)
	{
		NavContext->Buttons[NavContext->NavIndex]->NativeOnClick();
	}
}

void UBaseSubMenu::OnContextButtonHovered(int32 ContextIndex, int32 NavIndex)
{
	UpdateNavContext(ContextIndex, NavIndex, false);

}

void UBaseSubMenu::OnContextButtonClicked(int32 ContextIndex, int32 NavIndex)
{
	OnNavContextClicked.Broadcast(ContextIndex, NavIndex);

}
