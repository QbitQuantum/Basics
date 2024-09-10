EStatusCode VariablesTest::Run()
{

    CPPStatementsParser parser;
    InputFile inputFile;
    EStatusCode status = eSuccess;

    Hummus::Singleton<Hummus::Trace>::GetInstance()->SetLogSettings(scResultBasePath + "variablesLog.txt",true,true);

    inputFile.OpenFile(scSamplesBasePath + "variables.h");

    EStatusCodeAndHeaderUnit result = parser.Parse(
                                          inputFile.GetInputStream(),
                                          inputFile.GetFilePath(),
                                          StringToStringMap(),
                                          StringList()
                                      );

    if(result.first != eSuccess)
    {
        cout<<"VariablesTest::Run, failed to parse source\n";
        return eFailure;
    }

    HeaderUnit* parsedTree = result.second;
    CPPNamespace* globalNamespace = parsedTree->GetGlobalNamespace();

    do
    {
        if(VerifySimplePrimitiveVariables(globalNamespace) != eSuccess)
        {
            cout<<"VariablesTest::Run, failed simple variables definition\n";
            status = eFailure;
        }

        if(VerifySpecialStorageVariables(globalNamespace) != eSuccess)
        {
            cout<<"VariablesTest::Run, failed special storage variables definition\n";
            status = eFailure;
        }

        if(VerifyPointerArraysAndInitializers(globalNamespace) != eSuccess)
        {
            cout<<"VariablesTest::Run, failed pointers and arrays and initializers definition\n";
            status = eFailure;
        }

        if(VerifyFunctionPointers(globalNamespace) != eSuccess)
        {
            cout<<"VariablesTest::Run, failed function pointers definition\n";
            status = eFailure;
        }
    }
    while(false);

    delete parsedTree;

    Hummus::Singleton<Hummus::Trace>::Reset();
    return status;

}