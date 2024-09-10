void
ArxDbgUtils::getWcsToUcsMatrix(AcGeMatrix3d& m, AcDbDatabase* db)
{
    getUcsToWcsMatrix(m, db);
    m.invert();
}