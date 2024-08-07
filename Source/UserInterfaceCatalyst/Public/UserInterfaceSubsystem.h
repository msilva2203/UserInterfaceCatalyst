// © 2024 Marco Silva. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "UserInterfaceSubsystem.generated.h"

class UBaseGameDisplay;
class UBaseMenu;

/**
 * 
 */
UCLASS()
class USERINTERFACECATALYST_API UUserInterfaceSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/* GAME DISPLAYS */

	UFUNCTION(BlueprintCallable, Category = "User Interface Subsystem")
	bool PushGameDisplay(UBaseGameDisplay*& OutGameDisplay, TSubclassOf<UBaseGameDisplay> GameDisplayClass,
		int32 Layer, int32 ZOrder = 0, bool bPlayerDisplay = true, bool bImmediate = true);

	UFUNCTION(BlueprintCallable, Category = "User Interface Subsystem")
	bool RemoveGameDisplay(UBaseGameDisplay* GameDisplay);

	UFUNCTION(BlueprintCallable, Category = "User Interface Subsystem")
	bool ShowGameDisplay(UBaseGameDisplay* GameDisplay, bool bForce = false);

	UFUNCTION(BlueprintCallable, Category = "User Interface Subsystem")
	bool HideGameDisplay(UBaseGameDisplay* GameDisplay);

	UFUNCTION(BlueprintCallable, Category = "user Interface Subsystem")
	void CollapseLayer(int32 Layer);

	UFUNCTION(BlueprintCallable, Category = "user Interface Subsystem")
	void DisplayLayer(int32 Layer);

	/* MENUS */

	UFUNCTION(BlueprintCallable, Category = "User Interface Subsystem")
	bool PushMenu(UBaseMenu*& OutMenu, TSubclassOf<UBaseMenu> MenuClass, 
		bool bPlayerDisplay = true, bool bImmediate = true);

	UFUNCTION(BlueprintCallable, Category = "User Interface Subsystem")
	bool RemoveMenu(UBaseMenu* Menu);

	UFUNCTION(BlueprintCallable, Category = "User Interface Subsystem")
	bool ShowMenu(UBaseMenu* Menu, bool bForce = false);

	UFUNCTION(BlueprintCallable, Category = "User Interface Subsystem")
	bool HideMenu(UBaseMenu* Menu, bool bForce = false, bool bKeepVisible = false);

private:
	UPROPERTY()
	TArray<int32> CollapsedLayers;

	UPROPERTY()
	TArray<UBaseGameDisplay*> GameDisplays;

	UPROPERTY()
	TArray<UBaseMenu*> Menus;

	UPROPERTY();
	UBaseMenu* CurrentMenu;
};
