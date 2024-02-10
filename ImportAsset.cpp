// Fill out your copyright notice in the Description page of Project Settings.


#include "ImportAsset.h"
#include "AssetImportTask.h"
#include "AssetToolsModule.h"

UAssetImportTask* UImportAsset::CreateImportTask(FString SourcePath, FString DestinationPath, UFactory* ExtraFactory,
                                                 UObject* ExtraOption, bool& bOutputSuccess, FString& OutputInfoMessage)
{
	//create asset import task
	UAssetImportTask* AstImpTask = NewObject<UAssetImportTask>();

	//set up settings of asset import task
	AstImpTask->Filename = SourcePath;
	AstImpTask->DestinationPath = FPaths::GetPath(DestinationPath);
	AstImpTask->DestinationName = FPaths::GetCleanFilename(DestinationPath);
	AstImpTask->bSave = false;
	AstImpTask->bAutomated = true;
	AstImpTask->bAsync = false;
	AstImpTask->bReplaceExisting = true;
	AstImpTask->bReplaceExistingSettings = false;
	AstImpTask->Factory = ExtraFactory;
	AstImpTask->Options = ExtraOption;

	//return asset import task
	bOutputSuccess = true;
	OutputInfoMessage = FString::Printf(TEXT("Create import task succeed"));
	return AstImpTask;
}

UObject* UImportAsset::ProcessImportTask(UAssetImportTask* ImportTask, bool& bOutputSuccess, FString& OutputInfoMessage)
{
	//check if import task exist
	if(ImportTask == nullptr)
	{
		bOutputSuccess = false;
		OutputInfoMessage = FString::Printf(TEXT("Import task not found"));
		return nullptr;
	}
	
	//Get asset tool module and import asset
	FAssetToolsModule* AssetTools = FModuleManager::LoadModulePtr<FAssetToolsModule>("AssetTools");
	AssetTools->Get().ImportAssetTasks({ImportTask});

	//Some import task may create multiple assets, we manually get the right asset
	UObject* ImportedAsset = StaticLoadObject(UObject::StaticClass(), nullptr, *FPaths::Combine(ImportTask->DestinationPath, ImportTask->DestinationName));

	//return the asset#
	bOutputSuccess = true;
	OutputInfoMessage = FString::Printf(TEXT("Import asset succeed"));
	return ImportedAsset;
}

UObject* UImportAsset::ImportAsset(FString SourcePath, FString DestinationPath, bool& bOutputSuccess,
	FString& OutputInfoMessage)
{
	UAssetImportTask* AssetImportTask = CreateImportTask(SourcePath, DestinationPath, nullptr, nullptr, bOutputSuccess, OutputInfoMessage);
	if(!bOutputSuccess)
	{
		return nullptr;
	}
	UObject* ImportedAsset = ProcessImportTask(AssetImportTask, bOutputSuccess, OutputInfoMessage);
	if(!bOutputSuccess)
	{
		return nullptr;
	}
	
	bOutputSuccess = true;
	OutputInfoMessage = FString::Printf(TEXT("Asset import succeed"));
	return ImportedAsset;
	
}
