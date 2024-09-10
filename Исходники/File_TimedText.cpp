//---------------------------------------------------------------------------
void File_TimedText::Data_Parse()
{
    //Parsing
    Ztring Value;
    Get_UTF8 (Element_Size, Value,                              "Value");

    FILLING_BEGIN();
        if (!Status[IsAccepted])
        {
            Accept();
            #ifdef MEDIAINFO_MPEG4_YES
                if (IsChapter)
                {
                    Stream_Prepare(Stream_Menu);
                }
                else
            #endif //MEDIAINFO_MPEG4_YES
                {
                    Stream_Prepare(Stream_Text);
                }
            Fill(StreamKind_Last, 0, Fill_Parameter(StreamKind_Last, Generic_Format), "Timed Text");
        }
        #ifdef MEDIAINFO_MPEG4_YES
            if (IsChapter)
            {
            }
            else
        #endif //MEDIAINFO_MPEG4_YES
            {
                Finish();
            }

        #ifdef MEDIAINFO_MPEG4_YES
            if (IsChapter && FrameInfo.DTS!=(int64u)-1 && Buffer_Offset==2)
                Fill(Stream_Menu, 0, Ztring().Duration_From_Milliseconds(FrameInfo.DTS/1000000).To_UTF8().c_str(), Value);
        #endif //MEDIAINFO_MPEG4_YES
    FILLING_END();

    Element_Offset=Buffer_Size-Buffer_Offset; //Buffer can also contain atoms after the text, ignoring them
}