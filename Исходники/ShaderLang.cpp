static bool GenerateBuiltInSymbolTable(
        EShLanguage language, EShSpec spec, const TBuiltInResource& resources,
        TInfoSink& infoSink, TSymbolTable& symbolTable)
{
    TBuiltIns builtIns;

    builtIns.initialize(language, spec, resources);
    return InitializeSymbolTable(builtIns.getBuiltInStrings(), language, spec, resources, infoSink, symbolTable);
}