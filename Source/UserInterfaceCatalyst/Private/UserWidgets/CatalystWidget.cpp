// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/CatalystWidget.h"

void UCatalystWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CatalystInputSubsystem = GetOwningLocalPlayer()->GetSubsystem<UCatalystInputSubsystem>();
}
