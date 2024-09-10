//---------------------------------------------------------------------------
void File_Celt::Identification()
{
    Element_Name("Identification");

    //Parsing
    Ztring celt_version;
    int32u Celt_version_id, sample_rate, nb_channels;
    Skip_Local(8,                                               "celt_codec_id");
    Get_Local(20, celt_version,                                 "celt_version");
    Get_L4 (Celt_version_id,                                    "celt_version_id");
    Skip_L4(                                                    "header_size");
    Get_L4 (sample_rate,                                        "rate");
    Get_L4 (nb_channels,                                        "nb_channels");
    Skip_L4(                                                    "frame_size");
    Skip_L4(                                                    "overlap");
    Skip_L4(                                                    "bytes_per_packet");
    Skip_L4(                                                    "extra_headers");

    //Filling
    FILLING_BEGIN()
        Accept("CELT");

        Stream_Prepare(Stream_Audio);
        Fill(Stream_Audio, 0, Audio_Format, "CELT");
        Fill(Stream_Audio, 0, Audio_Codec, "CELT");

        if (!celt_version.empty())
        {
            //Fill(Stream_Audio, 0, Audio_Encoded_Library, celt_version); //Need more info about hte different possibilities, in the meanwhile trusting more the comment part
            Fill(Stream_Audio, 0, Audio_SamplingRate, sample_rate);
            Fill(Stream_Audio, 0, Audio_Channel_s_, nb_channels);
        }

    FILLING_END();

    //Filling
    Identification_Done=true;
}