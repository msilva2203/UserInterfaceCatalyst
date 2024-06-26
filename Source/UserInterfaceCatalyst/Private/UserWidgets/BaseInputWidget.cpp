// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/BaseInputWidget.h"

bool UBaseInputWidget::NativeOnAnyKeyPressed(const FKey& Key)
{
	if (OnAnyKeyPressed(Key)) return true;

	return false;
}

void UBaseInputWidget::NativeOnDirectionInput(EMenuNavigationType Type, int32 Value)
{
	if (IsInputBlocked()) return;

	OnDirectionInput(Type, Value);
}

void UBaseInputWidget::NativeOnActionInput(EMenuAction Action, uint8 Custom)
{
	if (IsInputBlocked()) return;

	OnActionInput(Action, Custom);
}

bool UBaseInputWidget::OnAnyKeyPressed_Implementation(const FKey& Key)
{
	return false;
}

void UBaseInputWidget::AddDirectionInput(EMenuNavigationType Type, int32 Value)
{
	NativeOnDirectionInput(Type, Value);
}

void UBaseInputWidget::AddActionInput(EMenuAction Action, uint8 Custom)
{
	NativeOnActionInput(Action, Custom);
}

void UBaseInputWidget::AddCustomAction(const FMenuCustomAction& NewAction)
{
	CustomActions.Add(NewAction);
}

bool UBaseInputWidget::RemoveCustomAction(const FMenuCustomAction& NewAction)
{
	int Index = 0;
	for (auto& Action : CustomActions)
	{
		if (Action.Key == NewAction.Key &&
			Action.Value == NewAction.Value)
		{
			CustomActions.RemoveAt(Index);
			return true;
		}
		Index++;
	}
	return false;
}

void UBaseInputWidget::SetInputBlocked(bool bNewValue)
{
	bIsInputBlocked = bNewValue;
}

bool UBaseInputWidget::IsInputBlocked()
{
	return bIsInputBlocked;
}

bool UBaseInputWidget::GetCustomActionValue(const FKeyEvent& KeyEvent, uint8& OutValue)
{
	for (auto& Action : CustomActions)
	{
		if (Action.Key == KeyEvent.GetKey() && (Action.bAllowRepeats == KeyEvent.IsRepeat() || !KeyEvent.IsRepeat()))
		{
			OutValue = Action.Value;
			return true;
		}
	}
	OutValue = 0;
	return false;
}
