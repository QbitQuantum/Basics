int main(int argc, char *argv[])
{
    if (argc != 4 ||
            (strcmp(argv[1], "-xml") != 0 && strcmp(argv[1], "-ss") != 0))
    {
        Usage(argc, argv);
        exit(1);
    }


    aafCharacter *inFileName = new aafCharacter[strlen(argv[2]) + 1];
    aafCharacter *outFileName = new aafCharacter[strlen(argv[3]) + 1];

    size_t status = mbstowcs(inFileName, argv[2], strlen(argv[2]));
    if (status == (size_t)-1)
    {
        fprintf(stderr, "\nError: Failed to convert filename '%s' to a wide string.", argv[2]);
        exit(1);
    }
    status = mbstowcs(outFileName, argv[3], strlen(argv[3]));
    if (status == (size_t)-1)
    {
        fprintf(stderr, "\nError: Failed to convert filename '%s' to a wide string.", argv[3]);
        exit(1);
    }
    inFileName[strlen(argv[2])] = 0;
    outFileName[strlen(argv[3])] = 0;

    // remove the output file if it already exists
    remove(argv[3]);

    
    CAAFInitialize aafInit;
    IAAFFile* inFile = 0;
    IAAFFile* outFile = 0;

    check(AAFFileOpenExistingRead(inFileName, 0, &inFile));

    aafProductVersion_t v;
    v.major = 0;
    v.minor = 1;
    v.tertiary = 0;
    v.patchLevel = 0;
    v.type = kAAFVersionUnknown;

    const aafUID_t productUID = 
        {0x97e04c67, 0xdbe6, 0x4d11, {0xbc, 0xd7, 0x3a, 0x90, 0x42, 0x53, 0xa2, 0xef}};
    aafProductIdentification_t  productInfo;
	aafWChar companyName[] = L"AMW Association";
	aafWChar productName[] = L"aaffmtconv";
    productInfo.companyName = companyName;
    productInfo.productName = productName;
    productInfo.productVersion = &v;
    productInfo.productVersionString = 0;
    productInfo.productID = productUID;
    productInfo.platform = 0;

    // create output file based on choice of stored format
    if (strcmp(argv[1], "-xml") == 0)
    {
        check(AAFFileOpenNewModifyEx(outFileName, &kAAFFileKind_AafXmlText, 0, &productInfo, &outFile));
    }
    else
    {
        check(AAFFileOpenNewModify(outFileName, 0, &productInfo, &outFile));
    }

    // save copy using the selected stored format
    check(inFile->SaveCopyAs(outFile));
    
    check(outFile->Close());
    check(inFile->Close());

    outFile->Release();
    outFile = 0;
    inFile->Release();
    inFile = 0;

    delete [] inFileName;
    delete [] outFileName;

    return 0;
}