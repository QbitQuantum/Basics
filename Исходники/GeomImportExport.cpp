Standard_Integer GeomImportExport::ReadIGES(const QString& aFileName,
                                         TopoDS_Shape& aShape)
{

    IGESControl_Reader Reader;

    Standard_Integer status = Reader.ReadFile(aFileName.toAscii().data());

    if (status != IFSelect_RetDone) return status;
    Reader.TransferRoots();
    aShape = Reader.OneShape();     

    return status;
}