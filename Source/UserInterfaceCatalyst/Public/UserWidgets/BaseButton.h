// © 2024 Marco Silva. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/CatalystWidget.h"
#include "Components/Button.h"
#include "BaseButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonContainerHelper, int32, ContextIndex, int32, NavIndex);

/**
 * 
 */
UCLASS()
class USERINTERFACECATALYST_API UBaseButton : public UCatalystWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	virtual void NativeOnClick();

	UFUNCTION()
	virtual void NativeOnHovered();

	UFUNCTION()
	virtual void NativeOnMouseHovered();

	UFUNCTION()
	virtual void NativeOnUnHovered();

	UFUNCTION()
	virtual void NativeOnMouseUnHovered();

	UFUNCTION(BlueprintImplementableEvent, Category = "Button")
	void OnHovered();

	UFUNCTION(BlueprintImplementableEvent, Category = "Button")
	void OnMouseHovered();

	UFUNCTION(BlueprintImplementableEvent, Category = "Button")
	void OnUnHovered();

	UFUNCTION(BlueprintImplementableEvent, Category = "Button")
	void OnMouseUnHovered();

	UFUNCTION(BlueprintImplementableEvent, Category = "Button")
	void OnClick();

	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetNavIndex(int32 NewValue);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button")
	int32 NavIndex;

	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonAction OnClicked;

	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonAction OnButtonHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonAction OnButtonUnhovered;

	UPROPERTY()
	FOnButtonContainerHelper OnHoverHelper;

	UPROPERTY()
	FOnButtonContainerHelper OnClickHelper;

	UPROPERTY()
	int32 NavContextIndex;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BTN;

};
