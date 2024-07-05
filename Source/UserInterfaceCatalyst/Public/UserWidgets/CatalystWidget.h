// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CatalystInputSubsystem.h"
#include "CatalystWidget.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACECATALYST_API UCatalystWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

public:

	UPROPERTY(BlueprintReadOnly, Category = "Catalyst Widget")
	UCatalystInputSubsystem* CatalystInputSubsystem;
};
