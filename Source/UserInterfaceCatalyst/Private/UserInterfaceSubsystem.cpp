// © 2024 Marco Silva. All Rights Reserved.


#include "UserInterfaceSubsystem.h"
#include "UserWidgets/BaseGameDisplay.h"
#include "UserWidgets/BaseMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UUserInterfaceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UUserInterfaceSubsystem::Deinitialize()
{
	Super::Deinitialize();

	for (auto GameDisplay : GameDisplays)
	{
		if (GameDisplay)
			GameDisplay->RemoveFromParent();
	}
}

bool UUserInterfaceSubsystem::PushGameDisplay(UBaseGameDisplay*& OutGameDisplay, TSubclassOf<UBaseGameDisplay> GameDisplayClass,
	int32 Layer, int32 ZOrder, bool bPlayerDisplay, bool bImmediate)
{
	APlayerController* LocalPlayer = GetLocalPlayer()->PlayerController;
	OutGameDisplay = CreateWidget<UBaseGameDisplay>(LocalPlayer, GameDisplayClass);

	if (!OutGameDisplay) return false;

	if (bPlayerDisplay) OutGameDisplay->AddToPlayerScreen(ZOrder);
	else OutGameDisplay->AddToViewport(ZOrder);

	OutGameDisplay->SetLayer(Layer);
	GameDisplays.Add(OutGameDisplay);

	if (bImmediate) ShowGameDisplay(OutGameDisplay, false);
	else HideGameDisplay(OutGameDisplay);

	return true;
}

bool UUserInterfaceSubsystem::RemoveGameDisplay(UBaseGameDisplay* GameDisplay)
{
	if (GameDisplays.Contains(GameDisplay))
	{
		GameDisplays.Remove(GameDisplay);

		HideGameDisplay(GameDisplay);
		GameDisplay->RemoveFromParent();
		return true;
	}
	return false;
}

bool UUserInterfaceSubsystem::ShowGameDisplay(UBaseGameDisplay* GameDisplay, bool bForce)
{
	if (GameDisplay)
	{
		if (!CollapsedLayers.Contains(GameDisplay->GetLayer()) || bForce)
		{
			GameDisplay->SetVisibility(ESlateVisibility::HitTestInvisible);
			return true;
		}
	}
	return false;
}

bool UUserInterfaceSubsystem::HideGameDisplay(UBaseGameDisplay* GameDisplay)
{
	if (GameDisplay)
	{
		GameDisplay->SetVisibility(ESlateVisibility::Collapsed);
		return true;
	}
	return false;
}

void UUserInterfaceSubsystem::CollapseLayer(int32 Layer)
{
	if (!CollapsedLayers.Contains(Layer))
	{
		CollapsedLayers.Add(Layer);
	}
	for (auto GameDisplay : GameDisplays)
	{
		if (GameDisplay->GetLayer() == Layer)
		{
			HideGameDisplay(GameDisplay);
		}
	}
}

void UUserInterfaceSubsystem::DisplayLayer(int32 Layer)
{
	if (CollapsedLayers.Contains(Layer))
	{
		CollapsedLayers.Remove(Layer);
	}
	for (auto GameDisplay : GameDisplays)
	{
		if (GameDisplay->GetLayer() == Layer)
		{
			ShowGameDisplay(GameDisplay);
		}
	}
}

bool UUserInterfaceSubsystem::PushMenu(UBaseMenu*& OutMenu, TSubclassOf<UBaseMenu> MenuClass, bool bPlayerDisplay, bool bImmediate)
{
	APlayerController* LocalPlayer = GetLocalPlayer()->PlayerController;
	OutMenu = CreateWidget<UBaseMenu>(LocalPlayer, MenuClass);

	if (!OutMenu) return false;

	if (bPlayerDisplay) OutMenu->AddToPlayerScreen();
	else OutMenu->AddToViewport();

	HideMenu(OutMenu, true);
	if (bImmediate) ShowMenu(OutMenu, false);

	return true;
}

bool UUserInterfaceSubsystem::RemoveMenu(UBaseMenu* Menu)
{
	if (Menus.Contains(Menu))
	{
		Menus.Remove(Menu);

		HideMenu(Menu, true);
		Menu->RemoveFromParent();
		return true;
	}
	return false;
}

bool UUserInterfaceSubsystem::ShowMenu(UBaseMenu* Menu, bool bForce)
{
	if (Menu)
	{
		if (CurrentMenu == nullptr || bForce)
		{
			APlayerController* LocalPlayer = GetLocalPlayer()->PlayerController;

			HideMenu(CurrentMenu, true);
			Menu->SetVisibility(ESlateVisibility::Visible);
			Menu->NativeOnShow();
			CurrentMenu = Menu;

			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(LocalPlayer, CurrentMenu, EMouseLockMode::DoNotLock);
			LocalPlayer->bShowMouseCursor = true;

			return true;
		}
	}
	return false;
}

bool UUserInterfaceSubsystem::HideMenu(UBaseMenu* Menu, bool bForce, bool bKeepVisible)
{
	if (Menu && (Menu == CurrentMenu || bForce))
	{
		APlayerController* LocalPlayer = GetLocalPlayer()->PlayerController;

		CurrentMenu = nullptr;
		if (!bKeepVisible)
			Menu->SetVisibility(ESlateVisibility::Collapsed);
		Menu->NativeOnHide();

		UWidgetBlueprintLibrary::SetInputMode_GameOnly(LocalPlayer);
		LocalPlayer->bShowMouseCursor = false;

		return true;
	}
	return false;
}
