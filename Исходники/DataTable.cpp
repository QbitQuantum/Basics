/** Get array of UProperties that corresponds to columns in the table */
TArray<UProperty*> UDataTable::GetTablePropertyArray(const TArray<const TCHAR*>& Cells, UStruct* InRowStruct, TArray<FString>& OutProblems)
{
    TArray<UProperty*> ColumnProps;

    // Get list of all expected properties from the struct
    TArray<FName> ExpectedPropNames = DataTableUtils::GetStructPropertyNames(InRowStruct);

    // Need at least 2 columns, first column is skipped, will contain row names
    if(Cells.Num() > 1)
    {
        ColumnProps.AddZeroed( Cells.Num() );

        // first element always NULL - as first column is row names

        for (int32 ColIdx = 1; ColIdx < Cells.Num(); ++ColIdx)
        {
            const TCHAR* ColumnValue = Cells[ColIdx];

            FName PropName = DataTableUtils::MakeValidName(ColumnValue);
            if(PropName == NAME_None)
            {
                OutProblems.Add(FString::Printf(TEXT("Missing name for column %d."), ColIdx));
            }
            else
            {
                UProperty* ColumnProp = FindField<UProperty>(InRowStruct, PropName);

                for (TFieldIterator<UProperty> It(InRowStruct); It && !ColumnProp; ++It)
                {
                    const auto DisplayName = DataTableUtils::GetPropertyDisplayName(*It, FString());
                    ColumnProp = (!DisplayName.IsEmpty() && DisplayName == ColumnValue) ? *It : NULL;
                }

                // Didn't find a property with this name, problem..
                if(ColumnProp == NULL)
                {
                    OutProblems.Add(FString::Printf(TEXT("Cannot find Property for column '%s' in struct '%s'."), *PropName.ToString(), *InRowStruct->GetName()));
                }
                // Found one!
                else
                {
                    // Check we don't have this property already
                    if(ColumnProps.Contains(ColumnProp))
                    {
                        OutProblems.Add(FString::Printf(TEXT("Duplicate column '%s'."), *ColumnProp->GetName()));
                    }
                    // Check we support this property type
                    else if( !DataTableUtils::IsSupportedTableProperty(ColumnProp) )
                    {
                        OutProblems.Add(FString::Printf(TEXT("Unsupported Property type for struct member '%s'."), *ColumnProp->GetName()));
                    }
                    // Looks good, add to array
                    else
                    {
                        ColumnProps[ColIdx] = ColumnProp;
                    }

                    // Track that we found this one
                    ExpectedPropNames.Remove(ColumnProp->GetFName());
                }
            }
        }
    }

    // Generate warning for any properties in struct we are not filling in
    for(int32 PropIdx=0; PropIdx < ExpectedPropNames.Num(); PropIdx++)
    {
        const UProperty* const ColumnProp = FindField<UProperty>(InRowStruct, ExpectedPropNames[PropIdx]);
        const FString DisplayName = DataTableUtils::GetPropertyDisplayName(ColumnProp, ExpectedPropNames[PropIdx].ToString());
        OutProblems.Add(FString::Printf(TEXT("Expected column '%s' not found in input."), *DisplayName));
    }

    return ColumnProps;
}