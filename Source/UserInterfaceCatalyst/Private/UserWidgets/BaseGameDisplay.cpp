// © 2024 Marco Silva. All Rights Reserved.


#include "UserWidgets/BaseGameDisplay.h"

void UBaseGameDisplay::NativeConstruct()
{
	Super::NativeConstruct();

}

int32 UBaseGameDisplay::GetLayer() const
{
	return Layer;
}
