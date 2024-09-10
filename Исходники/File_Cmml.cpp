//---------------------------------------------------------------------------
void File_Cmml::Identification()
{
    Element_Name("Identification");

    //Parsing
    int16u VersionMajor, VersionMinor;
    Skip_Local(8,                                               "Signature");
    Get_L2 (VersionMajor,                                       "version major");
    Get_L2 (VersionMinor,                                       "version minor");
    Skip_L8(                                                    "granule rate numerator");
    Skip_L8(                                                    "granule rate denominator");
    Skip_L1(                                                    "granule shift");

    FILLING_BEGIN();
        Stream_Prepare(Stream_General);
        Stream_Prepare(Stream_Text);
        Fill(Stream_Text, 0, Text_Format, "CMML");
        Fill(Stream_Text, 0, Text_Codec,  "CMML");

        Accept("CMML");
    FILLING_END();
}