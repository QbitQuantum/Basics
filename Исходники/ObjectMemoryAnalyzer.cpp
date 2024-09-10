void FObjectMemoryAnalyzer::PrintSubObjects(FOutputDevice& Ar, const FString& Indent, UObject* Parent, uint32 PrintFlags)
{
	TArray<UObject*> ReferencedObjects;
	GetReferencedObjects(Parent, ReferencedObjects);

	for( int32 ObjIndex = 0; ObjIndex < ReferencedObjects.Num(); ObjIndex++ )
	{
		UObject* SubObj = ReferencedObjects[ObjIndex];
		const FObjectMemoryUsage& Annotation = GetObjectMemoryUsage(SubObj);

		if (!Annotation.IsRoot())
		{
			Ar.Logf( TEXT("%-100s %-10d %-10d %-10d %-10d"), *FString::Printf(TEXT("%s%s %s"), *Indent, *SubObj->GetClass()->GetName(), *SubObj->GetName()),
					 (int32)Annotation.InclusiveMemoryUsage, (int32)Annotation.ExclusiveMemoryUsage, 
					 (int32)(Annotation.InclusiveResourceSize/1024), (int32)(Annotation.ExclusiveResourceSize/1024) );

			if (!!(PrintFlags&EPrintFlags::PrintReferencer))
			{
				for (int32 i=0; i < Annotation.NonRootReferencer.Num(); ++i)
				{
					Ar.Logf(TEXT("%s  >> NonRootRef: %s"), *Indent, *Annotation.NonRootReferencer[i]->GetName());
				}

				for (int32 i=0; i < Annotation.RootReferencer.Num(); ++i)
				{
					Ar.Logf(TEXT("%s  >> RootRef: %s"), *Indent, *Annotation.RootReferencer[i]->GetName());
				}
			}
			
			if (!!(PrintFlags&EPrintFlags::PrintReferences))
			{
				PrintSubObjects(Ar, Indent + TEXT(" -> "), SubObj, PrintFlags);
			}
		}
	}
}