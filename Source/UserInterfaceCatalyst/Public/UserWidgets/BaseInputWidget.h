// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseInputWidget.generated.h"


UENUM(BlueprintType)
enum class EMenuNavigationType : uint8
{
	Horizontal,
	Vertical
};

UENUM(BlueprintType)
enum class EMenuAction : uint8
{
	Accept,
	Back,
	Custom
};

USTRUCT(BlueprintType)
struct FMenuCustomAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Custom Action")
	uint8 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Custom Action")
	FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Custom Action")
	bool bAllowRepeats;
};


/**
 * 
 */
UCLASS()
class USERINTERFACECATALYST_API UBaseInputWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnDirectionInput(EMenuNavigationType Type, int32 Value);
	virtual void NativeOnActionInput(EMenuAction Action, uint8 Custom = 0);

	UFUNCTION(BlueprintImplementableEvent, Category = "Input Widget")
	void OnDirectionInput(EMenuNavigationType Type, int32 Value);

	UFUNCTION(BlueprintImplementableEvent, Category = "Input Widget")
	void OnActionInput(EMenuAction Action, uint8 Custom = 0);

	UFUNCTION(BlueprintCallable, Category = "Input Widget")
	void AddDirectionInput(EMenuNavigationType Type, int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Input Widget")
	void AddActionInput(EMenuAction Action, uint8 Custom = 0);

	UFUNCTION(BlueprintCallable, Category = "Input Widget")
	void AddCustomAction(const FMenuCustomAction& NewAction);

	UFUNCTION(BlueprintCallable, Category = "Input Widget")
	bool RemoveCustomAction(const FMenuCustomAction& NewAction);

	bool GetCustomActionValue(const FKeyEvent& KeyEvent, uint8& OutValue);

private:
	UPROPERTY()
	TArray<FMenuCustomAction> CustomActions;

};
