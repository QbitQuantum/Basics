FString DumpComponentsToString(UObject *Object)
{
    UnMarkAllObjects(EObjectMark(OBJECTMARK_TagExp | OBJECTMARK_TagImp));

    FStringOutputDevice Output;
    Output.Logf(TEXT("Components for '%s':\r\n"), *Object->GetFullName());
    ExportProperties(NULL, Output, Object->GetClass(), (uint8*)Object, 2, NULL, NULL, Object, PPF_SubobjectsOnly);
    Output.Logf(TEXT("<--- DONE!\r\n"));
    return Output;
}