ExcelEngine::~ExcelEngine()
{
    if ( bIsOpen )
    {
        //析构前，先保存数据，然后关闭workbook
        close();
    }
    OleUninitialize();
}