//---------------------------------------------------------------------------
void File_Ibi::Ebml_DocType()
{
    Element_Name("DocType");

    //Parsing
    Ztring Data;
    Get_Local(Element_Size, Data,                               "Data"); Element_Info(Data);

    //Filling
    FILLING_BEGIN();

        if (Data==_T("MediaInfo Index"))
            Accept("Ibi");
        else
        {
            Reject("Ibi");
            return;
        }

        Buffer_MaximumSize=8*1024*1024;
    FILLING_END();
}