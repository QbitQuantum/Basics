TopoDS_Shape openIGES(char const *filename)
{
    IGESControl_Reader reader;
    IFSelect_ReturnStatus status = reader.ReadFile(filename);

    assert(status == IFSelect_RetDone);

    reader.TransferRoots();

    return reader.OneShape();
}