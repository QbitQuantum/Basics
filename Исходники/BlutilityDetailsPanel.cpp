FReply FEditorUtilityInstanceDetails::OnExecuteAction(TWeakObjectPtr<UFunction> WeakFunctionPtr)
{
    if (UFunction* Function = WeakFunctionPtr.Get())
    {
        FScopedTransaction Transaction( NSLOCTEXT("UnrealEd", "BlutilityAction", "Blutility Action") );
        FEditorScriptExecutionGuard ScriptGuard;

        UClass* MinRequiredClass = Function->GetOuterUClass();

        // Execute this function on any objects that support it
        for (auto SelectedObjectIt = SelectedObjectsList.CreateConstIterator(); SelectedObjectIt; ++SelectedObjectIt)
        {
            UObject* Object = (*SelectedObjectIt).Get();

            if ((Object != NULL) && (Object->IsA(MinRequiredClass)))
            {
                Object->ProcessEvent(Function, NULL);

                if (UGlobalEditorUtilityBase* BlutilityInstance = Cast<UGlobalEditorUtilityBase>(Object))
                {
                    BlutilityInstance->PostExecutionCleanup();
                }
            }
        }
    }

    return FReply::Handled();
}