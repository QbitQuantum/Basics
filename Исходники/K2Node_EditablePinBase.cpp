void UK2Node_EditablePinBase::ExportCustomProperties(FOutputDevice& Out, uint32 Indent)
{
	for (int32 PinIndex = 0; PinIndex < UserDefinedPins.Num(); ++PinIndex)
	{
		const FUserPinInfo& PinInfo = *UserDefinedPins[PinIndex].Get();

		Out.Logf( TEXT("%sCustomProperties UserDefinedPin "), FCString::Spc(Indent));
		Out.Logf( TEXT("Name=%s "), *PinInfo.PinName);
		Out.Logf( TEXT("IsArray=%s "), (PinInfo.PinType.bIsArray ? TEXT("1") : TEXT("0")));
		Out.Logf( TEXT("IsReference=%s "), (PinInfo.PinType.bIsReference ? TEXT("1") : TEXT("0")));
		
		if (PinInfo.PinType.PinCategory.Len() > 0)
		{
			Out.Logf( TEXT("Category=%s "), *PinInfo.PinType.PinCategory);
		}

		if (PinInfo.PinType.PinSubCategory.Len() > 0)
		{
			Out.Logf( TEXT("SubCategory=%s "), *PinInfo.PinType.PinSubCategory);
		}

		if (PinInfo.PinType.PinSubCategoryObject.IsValid())
		{
			Out.Logf( TEXT("SubCategoryObject=%s "), *PinInfo.PinType.PinSubCategoryObject.Get()->GetPathName());
		}

		if (PinInfo.PinDefaultValue.Len() > 0)
		{
			Out.Logf( TEXT("DefaultValue=%s "), *PinInfo.PinDefaultValue);
		}

		Out.Logf( TEXT("\r\n"));
	}
}