// © 2024 Marco Silva. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseGameDisplay.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACECATALYST_API UBaseGameDisplay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Base Game Display")
	void SetLayer(const int32 NewValue);

	UFUNCTION(BlueprintPure, Category = "Base Game Display")
	int32 GetLayer() const;

private:
	UPROPERTY()
	int32 Layer;
};
