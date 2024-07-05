// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "CatalystInputSubsystem.generated.h"

UENUM(BlueprintType)
enum class EInputDeviceType : uint8
{
	MouseKeyboard,
	Gamepad
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FValueDelegate, EInputDeviceType, DeviceValue, int32, GamepadValue);

/**
 * 
 */
UCLASS()
class USERINTERFACECATALYST_API UCatalystInputSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:

	UFUNCTION(BlueprintCallable, Category = "Catalyst Input")
	void UpdateInputDeviceType(EInputDeviceType NewValue);

	UFUNCTION(BlueprintCallable, Category = "Catalyst Input")
	void UpdateGamepadType(int32 NewValue);

public:

	UPROPERTY(BlueprintAssignable, Category = "Catalyst Input")
	FValueDelegate OnInputDeviceTypeChanged;

private:

	UPROPERTY()
	EInputDeviceType InputDeviceType;

	UPROPERTY()
	int32 GamepadType;

};
