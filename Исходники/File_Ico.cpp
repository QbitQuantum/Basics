//---------------------------------------------------------------------------
void File_Ico::Data_Parse()
{
    //Parsing
    int32u Size, Offset;
    int16u BitsPerPixel;
    int8u Width, Height;
    Get_L1 (Width,                                      "Width");
    Get_L1 (Height,                                     "Height");
    Skip_L1(                                            "Colour count");
    Skip_L1(                                            "Reserved");
    Skip_L2(                                            Type==1?"Colour planes":"X hotspot");
    Get_L2 (BitsPerPixel,                               Type==1?"Bits per pixel":"Y hotspot");
    Get_L4 (Size,                                       "Size of the bitmap data");
    Get_L4 (Offset,                                     "Offset of the bitmap data");

    FILLING_BEGIN_PRECISE();
        stream Stream;
        Stream.Width=Width;
        Stream.Height=Height;
        Stream.BitsPerPixel=BitsPerPixel;
        Stream.Size=Size;
        Stream.Offset=Offset;
        Streams.push_back(Stream);

        IcoDataSize+=Size;
        if (Offset>File_Size || File_Offset+Buffer_Offset+Element_Size+IcoDataSize>File_Size)
            Reject("ICO");
        Count--;
        if (Count==0)
        {
            if (File_Offset+Buffer_Offset+Element_Size+IcoDataSize!=File_Size)
                Reject("ICO");
            else
            {
                Accept("ICO");
                Finish("ICO");
            }
        }
    FILLING_END();
}