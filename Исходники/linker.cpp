/**
 * Return the path name of the UObject represented by the specified export.
 * (can be used with StaticFindObject)
 * 
 * @param	ExportIndex				index into the ExportMap for the resource to get the name for
 * @param	FakeRoot				Optional name to replace use as the root package of this object instead of the linker
 * @param	bResolveForcedExports	if true, the package name part of the return value will be the export's original package,
 *									not the name of the package it's currently contained within.
 *
 * @return	the path name of the UObject represented by the resource at ExportIndex
 */
FString FLinker::GetExportPathName(int32 ExportIndex, const TCHAR* FakeRoot,bool bResolveForcedExports/*=false*/)
{
	FString Result;

	bool bForcedExport = false;
	for ( FPackageIndex LinkerIndex = FPackageIndex::FromExport(ExportIndex); !LinkerIndex.IsNull(); LinkerIndex = Exp(LinkerIndex).OuterIndex )
	{ 
		const FObjectExport Export = Exp(LinkerIndex);

		// don't append a dot in the first iteration
		if ( Result.Len() > 0 )
		{
			// if this export is not a UPackage but this export's Outer is a UPackage, we need to use subobject notation
			if ((Export.OuterIndex.IsNull() || GetExportClassName(Export.OuterIndex) == NAME_Package)
			  && GetExportClassName(LinkerIndex) != NAME_Package)
			{
				Result = FString(SUBOBJECT_DELIMITER) + Result;
			}
			else
			{
				Result = FString(TEXT(".")) + Result;
			}
		}
		Result = Export.ObjectName.ToString() + Result;
		bForcedExport = bForcedExport || Export.bForcedExport;
	}

	if ( bForcedExport && FakeRoot == NULL && bResolveForcedExports )
	{
		// Result already contains the correct path name for this export
		return Result;
	}

	return (FakeRoot ? FakeRoot : LinkerRoot->GetPathName()) + TEXT(".") + Result;
}