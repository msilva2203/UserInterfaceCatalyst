// © 2024 Marco Silva. All Rights Reserved.


#include "UserWidgets/BaseGameDisplay.h"

void UBaseGameDisplay::NativeConstruct()
{
	Super::NativeConstruct();

}

void UBaseGameDisplay::SetLayer(const int32 NewValue)
{
	Layer = NewValue;
}

int32 UBaseGameDisplay::GetLayer() const
{
	return Layer;
}
