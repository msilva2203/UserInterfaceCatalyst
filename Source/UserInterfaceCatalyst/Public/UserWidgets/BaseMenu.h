// © 2024 Marco Silva. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/BaseInputWidget.h"
#include "BaseMenu.generated.h"

class UBaseSubMenu;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVisibilityUpdate);

/**
 * 
 */
UCLASS()
class USERINTERFACECATALYST_API UBaseMenu : public UBaseInputWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnAnalogValueChanged(const FGeometry& MyGeometry, const FAnalogInputEvent& InAnalogEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDirectionInput(EMenuNavigationType Type, int32 Value) override;
	virtual void NativeOnActionInput(EMenuAction Action, uint8 Custom = 0) override;

	virtual void NativeOnShow();
	virtual void NativeOnHide();

public:

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void FocusSubMenu(UBaseSubMenu* SubMenu);

	UFUNCTION(BlueprintPure, Category = "Menu")
	UBaseSubMenu* GetFocusedSubMenu() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Menu")
	void OnShow();

	UFUNCTION(BlueprintImplementableEvent, Category = "Menu")
	void OnHide();

public:

	UPROPERTY(BlueprintAssignable, Category = "Menu")
	FOnVisibilityUpdate OnMenuShown;

	UPROPERTY(BlueprintAssignable, Category = "Menu")
	FOnVisibilityUpdate OnMenuHidden;

private:
	UPROPERTY()
	UBaseSubMenu* FocusedSubMenu;

	void HandleActionInput(EUINavigationAction NavigationAction, uint8 Custom = 0);
	void HandleDirectionInput(EUINavigation NavigationDirection);
};
