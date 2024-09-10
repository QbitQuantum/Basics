// Disassemble all functions in any classes that have matching names.
void FKismetBytecodeDisassembler::DisassembleAllFunctionsInClasses(FOutputDevice& Ar, const FString& ClassnameSubstring)
{
	FKismetBytecodeDisassembler Disasm(Ar);
		
	for (TObjectIterator<UClass> ClassIter; ClassIter; ++ClassIter)
	{
		UClass* Class = *ClassIter;

		FString ClassName = Class->GetName();
		if (FCString::Strfind(*ClassName, *ClassnameSubstring))
		{
			Ar.Logf(TEXT("Processing class %s"), *ClassName);

			for (TFieldIterator<UFunction> FunctionIter(Class, EFieldIteratorFlags::ExcludeSuper); FunctionIter; ++FunctionIter)
			{
				UFunction* Function = *FunctionIter;
				FString FunctionName = Function->GetName();
				Ar.Logf(TEXT("  Processing function %s (%d bytes)"), *FunctionName, Function->Script.Num());

				Disasm.DisassembleStructure(Function);

				Ar.Logf(TEXT(""));
			}

			Ar.Logf(TEXT(""));
			Ar.Logf(TEXT("-----------"));
			Ar.Logf(TEXT(""));
		}

	}
}