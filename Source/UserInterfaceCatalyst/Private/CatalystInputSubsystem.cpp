// Fill out your copyright notice in the Description page of Project Settings.


#include "CatalystInputSubsystem.h"

void UCatalystInputSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UCatalystInputSubsystem::Deinitialize()
{
	Super::Deinitialize();

}

void UCatalystInputSubsystem::UpdateInputDeviceType(EInputDeviceType NewValue)
{
	if (InputDeviceType != NewValue)
	{
		InputDeviceType = NewValue;
		OnInputDeviceTypeChanged.Broadcast(InputDeviceType, GamepadType);
	}

}

void UCatalystInputSubsystem::UpdateGamepadType(int32 NewValue)
{
	if (GamepadType != NewValue)
	{
		GamepadType = NewValue;
		OnInputDeviceTypeChanged.Broadcast(InputDeviceType, GamepadType);
	}

}
