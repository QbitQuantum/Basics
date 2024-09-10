TEST(IGESImportTestSuite, testImportIGES_1)
{
    Standard_CString aFileName = (Standard_CString) iges_file_1;
    IGESControl_Reader Reader;
    int status = Reader.ReadFile(aFileName);
    ASSERT_EQ(status,IFSelect_RetDone);
    TopoDS_Shape tdsshape;
    if ( status == IFSelect_RetDone )
    {
        Reader.TransferRoots();
        tdsshape = Reader.OneShape();
    }
    ASSERT_FALSE(tdsshape.IsNull());
}