	/**
	 * Helper method to close a specified blueprint (if it is open in the blueprint-editor).
	 * 
	 * @param  BlueprintObj		The blueprint you want the editor closed for.
	 */
	static void CloseBlueprint(UBlueprint* const BlueprintObj)
	{
		IAssetEditorInstance* EditorInst = FAssetEditorManager::Get().FindEditorForAsset(BlueprintObj, /*bool bFocusIfOpen =*/false);
		if (EditorInst != nullptr)
		{
			UE_LOG(LogBlueprintAutomationTests, Log, TEXT("Closing '%s' so we don't invalidate the open version when unloading it."), *BlueprintObj->GetName());
			EditorInst->CloseWindow();
		}
	}