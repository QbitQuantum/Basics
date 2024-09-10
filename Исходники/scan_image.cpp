int main (int argc, char **argv)
{
    unsigned long nowTime = getCurrentTime();
    // std::cout<<"nowTime: "<<getCurrentTime()<<"\n";
    if(argc < 2) return(1);

    // create a reader
    ImageScanner scanner;

    // // configure the reader
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
    /* obtain image data */
    int width = 1920, height = 1080;
    char *raw = (char*)malloc(width*height);
    get_yuv_data(argv[1], width, height, raw);
    // wrap image data
    Image image(width, height, "Y800", raw, width * height);

    // scan the image for barcodes
    int n = scanner.scan(image);
    if(0==n||-1==n)
    {
      printf("no symbols were found or -1 if an error occurs");
      return -1;
    }
    // extract results
    for(Image::SymbolIterator symbol = image.symbol_begin();
        symbol != image.symbol_end();
        ++symbol)
    {
        // do something useful with results
        cout << "decoded " << symbol->get_type_name()
             << " symbol \"" << symbol->get_data() << '"' << endl;
    }

    // clean up
    image.set_data(NULL, 0);
    free(raw);
    std::cout<<getCurrentTime()-nowTime<<"\n";
    return(0);
}