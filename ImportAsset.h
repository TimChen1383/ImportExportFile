// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AssetImportTask.h"
#include "ImportAsset.generated.h"

/**
 * 
 */

class UAssetImportTask;
class UFactory;

UCLASS()
class CPPPRACTICE_API UImportAsset : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * 
	 * @param SourcePath The path of source file
	 * @param DestinationPath The path od imported asset
	 * @param ExtraFactory Optional.Some asset require special factory to import
	 * @param ExtraOption Optional. Some asset has extra settings
	 * @param bOutputSuccess record output success or not
	 * @param OutputInfoMessage record output information if needed
	 * @return return asset import task
	 */
	UFUNCTION(BlueprintCallable, Category="ImportAsset")
	static UAssetImportTask* CreateImportTask(FString SourcePath, FString DestinationPath, UFactory* ExtraFactory, UObject* ExtraOption, bool& bOutputSuccess, FString& OutputInfoMessage);

	/**
	 * 
	 * @param ImportTask 
	 * @param bOutputSuccess 
	 * @param OutputInfoMessage 
	 * @return return imported asset
	 */
	UFUNCTION(BlueprintCallable, Category="ImportAsset")
	static UObject* ProcessImportTask(UAssetImportTask* ImportTask, bool& bOutputSuccess, FString& OutputInfoMessage);

	/**
	 * combine 2 function together
	 * @param SourcePath The path of source file
	 * @param DestinationPath The path od imported asset
	 * @param bOutputSuccess record output success or not
	 * @param OutputInfoMessage record output information if needed
	 * @return return imported asset - just for test, actually not necessary
	 */
	UFUNCTION(BlueprintCallable, Category="ImportAsset")
	static UObject* ImportAsset(FString SourcePath, FString DestinationPath, bool& bOutputSuccess, FString& OutputInfoMessage);
};
