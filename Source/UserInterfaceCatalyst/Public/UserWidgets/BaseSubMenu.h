// © 2024 Marco Silva. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseInputWidget.h"
#include "BaseSubMenu.generated.h"

class UBaseButton;

USTRUCT(BlueprintType)
struct FNavContextParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nav Container Params")
	bool bCircularNavigation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nav Container Params")
	int32 VerticalMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nav Container Params")
	int32 HorizontalMultiplier = 0;

};

USTRUCT(BlueprintType)
struct FNavigationContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation Container")
	FNavContextParams Params;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation Container")
	TArray<UBaseButton*> Buttons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation Container")
	int32 NavIndex;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNavContextDelegate, int32, ContextIndex, int32, NavIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFocus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBack);

/**
 * 
 */
UCLASS()
class USERINTERFACECATALYST_API UBaseSubMenu : public UBaseInputWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeOnDirectionInput(EMenuNavigationType Type, int32 Value) override;
	virtual void NativeOnActionInput(EMenuAction Action, uint8 Custom = 0) override;

	virtual void NativeOnMenuFocus();
	virtual void NativeOnMenuUnfocus();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void OnMenuFocus();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void OnMenuUnfocus();

	UFUNCTION(BlueprintCallable, Category = "Sub Menu")
	int32 CreateNavContext(const TArray<UBaseButton*>& Buttons, const FNavContextParams& Params);

	UFUNCTION(BlueprintCallable, Category = "Sub Menu")
	int32 UpdateNavContext(int32 ContextIndex, int32 Value, bool bForce = false);

	UFUNCTION(BlueprintCallable, Category = "Sub Menu")
	int32 OffsetNavContext(int32 ContextIndex, int32 Value, EMenuNavigationType Type = EMenuNavigationType::Vertical);

	UFUNCTION(BlueprintCallable, Category = "Sub Menu")
	void ClickNavContext(int32 ContextIndex);

	UFUNCTION(BlueprintPure, Category = "Sub Menu")
	int32 GetNavContextCurrentIndex(int32 ContextIndex);

	UPROPERTY(BlueprintAssignable, Category = "Sub Menu")
	FOnFocus OnMenuFocused;

	UPROPERTY(BlueprintAssignable, Category = "Sub Menu")
	FOnFocus OnMenuUnFocused;

	UPROPERTY(BlueprintAssignable, Category = "Sub Menu")
	FOnNavContextDelegate OnNavContextUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Sub Menu")
	FOnNavContextDelegate OnNavContextClicked;

	UPROPERTY(BlueprintAssignable, Category = "Sub Menu")
	FOnBack OnBack;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sub Menu")
	ESlateVisibility FocusedVisibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sub Menu")
	ESlateVisibility UnfocusedVisibility;

private:
	UFUNCTION()
	void OnContextButtonHovered(int32 ContextIndex, int32 NavIndex);

	UFUNCTION()
	void OnContextButtonClicked(int32 ContextIndex, int32 NavIndex);

	UPROPERTY()
	TArray<FNavigationContext> NavContexts;
};
