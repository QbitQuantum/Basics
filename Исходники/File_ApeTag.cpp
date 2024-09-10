//---------------------------------------------------------------------------
void File_ApeTag::Data_Parse()
{
    //If footer
    if (Element_Code==(int64u)-1)
    {
        HeaderFooter();
        Finish("ApeTag");
        return;
    }

    //Parsing
    Ztring Value;
    Get_UTF8(Element_Size, Value,                               "Value"); Element_Info(Value);

    //Filling
    transform(Key.begin(), Key.end(), Key.begin(), (int(*)(int))toupper); //(int(*)(int)) is a patch for unix
         if (Key=="ALBUM")          Fill(Stream_General, 0, General_Album, Value);
    else if (Key=="ARTIST")         Fill(Stream_General, 0, General_Performer, Value);
    else if (Key=="AUTHOR")         Fill(Stream_General, 0, General_WrittenBy, Value);
    else if (Key=="BAND")           Fill(Stream_General, 0, General_Performer, Value);
    else if (Key=="COMMENT")        Fill(Stream_General, 0, General_Comment, Value);
    else if (Key=="COMMENTS")       Fill(Stream_General, 0, General_Comment, Value);
    else if (Key=="COMPOSER")       Fill(Stream_General, 0, General_Composer, Value);
    else if (Key=="CONTENTGROUP")   Fill(Stream_General, 0, General_Genre, Value);
    else if (Key=="COPYRIGHT")      Fill(Stream_General, 0, General_Copyright, Value);
    else if (Key=="DISK")
    {
                                    if (Value.find(_T("/"))!=Error)
                                    {
                                        Fill(Stream_General, 0, General_Part_Position_Total, Value.SubString(_T("/"), _T("")));
                                        Fill(Stream_General, 0, General_Part_Position, Value.SubString(_T(""), _T("/")));
                                    }
                                    else
                                        Fill(Stream_General, 0, General_Track_Position, Value);
    }
    else if (Key=="ENCODEDBY")      Fill(Stream_General, 0, General_EncodedBy, Value);
    else if (Key=="GENRE")          Fill(Stream_General, 0, General_Genre, Value);
    else if (Key=="ORIGARTIST")     Fill(Stream_General, 0, General_Original_Performer, Value);
    else if (Key=="TITLE")          Fill(Stream_General, 0, General_Title, Value);
    else if (Key=="TRACK")
    {
                                    if (Value.find(_T("/"))!=Error)
                                    {
                                        Fill(Stream_General, 0, General_Track_Position_Total, Value.SubString(_T("/"), _T("")));
                                        Fill(Stream_General, 0, General_Track_Position, Value.SubString(_T(""), _T("/")));
                                    }
                                    else
                                        Fill(Stream_General, 0, General_Track_Position, Value);
    }
    else if (Key=="UNSYNCEDLYRICS") Fill(Stream_General, 0, General_Lyrics, Value);
    else if (Key=="WWW")            Fill(Stream_General, 0, General_Title_Url, Value);
    else if (Key=="YEAR")           Fill(Stream_General, 0, General_Recorded_Date, Value);
    else if (Key=="CONTENT GROUP DESCRIPTION") Fill(Stream_General, 0, General_Title, Value);
    else if (Key=="ORIGINAL ALBUM/MOVIE/SHOW TITLE") Fill(Stream_General, 0, General_Original_Album, Value);
    else if (Key=="ORIGINAL ARTIST(S)/PERFORMER(S)") Fill(Stream_General, 0, General_Original_Performer, Value);
    else if (Key=="MP3GAIN_MINMAX") Fill(Stream_Audio, 0, "MP3Gain, Min/Max", Value);
    else if (Key=="MP3GAIN_UNDO") Fill(Stream_Audio, 0, "MP3Gain, Undo", Value);
    else if (Key=="REPLAYGAIN_TRACK_GAIN") Fill(Stream_Audio, 0, Audio_ReplayGain_Gain, Value.To_float64(), 2, true);
    else if (Key=="REPLAYGAIN_TRACK_PEAK") Fill(Stream_Audio, 0, Audio_ReplayGain_Peak, Value.To_float64(), 6, true);
    else                            Fill(Stream_General, 0, Key.c_str(), Value);
}