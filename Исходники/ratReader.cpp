ratReader::ratReader(Read *r, int fd): Reader(r)
{
    // Init: 
    buffer = NULL;
    loaded = false;
    rat    = NULL;
    use_scanline_engine = true;
    parms = new IMG_FileParms();
    
    // Read knobs:
    ratReaderFormat* rrf = dynamic_cast<ratReaderFormat*>(r->handler());
    if (rrf)
    {
        if (rrf->reverse_scanlines())
            parms->orientImage(IMG_ORIENT_LEFT_FIRST, IMG_ORIENT_TOP_FIRST);

        use_scanline_engine = rrf->use_scanline_engine(); 
    }
    else
        parms->orientImage(IMG_ORIENT_LEFT_FIRST, IMG_ORIENT_Y_NONE);

    // Set some of the settings, which are assumed currently by both ::engines. 
    // Leaving them as they are would require some serious switches in logic bellow.
    parms->setDataType(IMG_FLOAT);
    parms->setInterleaved(IMG_INTERLEAVED);
    parms->setComponentOrder(IMG_COMPONENT_RGBA);
    
    // Create and open rat file, get stats:
    rat = IMG_File::open(r->filename(), parms);

    // TODO: Meta data attempt:
    #if defined(DEBUG)
    UT_String info;
    rat->getAdditionalInfo(info);
    iop->warning("Rat info: %s\n", info.buffer());
    for (int i = 0; i < rat->getNumOptions(); i++)
    {
        iop->warning("%s: %s", rat->getOptionName(i), rat->getOptionValue(i));
    }
    UT_SharedPtr<UT_Options> opt;
    UT_WorkBuffer wbuf;
    if (opt = rat->imageTextureOptions())
    {
        wbuf.strcpy("DSM Options: ");
        opt->appendPyDictionary(wbuf);
        iop->warning("Options %i: %s\n", opt->getNumOptions(), wbuf.buffer());
    }
    #endif
    if (!rat)
    {
        iop->error("Failed to open .rat file.");
    }
    const IMG_Stat &stat = rat->getStat();
    depth = 0;
    #if defined(DEBUG)
    iop->warning("Rat opened: %s", r->filename());
    #endif

    // Since RAT can store varying bitdepth per plane, pixel-byte algebra doesn't 
    // help in finding out a number of channels. We need to iterate over planes. 
    for (int i = 0; i < stat.getNumPlanes(); i++)
    {
        IMG_Plane *plane = stat.getPlane(i);

        // The easiest yet not unequivocal way to determine 2d versus deep RAT files:
        if (!strcmp(plane->getName(), "Depth-Complexity"))
            iop->warning("ratReader will treat DCM files as a 2d images. (ignoring deep pixels)");

        #if defined(DEBUG)
        iop->warning("Plane name: %s", plane->getName());
        #endif
        depth += IMGvectorSize(plane->getColorModel()); 
    } 

    ChannelSet mask;
    for (int i = 0; i < stat.getNumPlanes(); i++)
    {
        IMG_Plane *plane = stat.getPlane(i);
        const int  nchan = IMGvectorSize(plane->getColorModel());

        for (int j = 0; j < nchan; j++)
        {
            std::string chan = std::string(plane->getComponentName(j) ? plane->getComponentName(j): "r"); 

            if      (chan == "r") chan = "red"; 
            else if (chan == "g") chan = "green";
            else if (chan == "b") chan = "blue"; 
            else if (chan == "a") chan = "alpha";

            std::string chan_name = std::string(plane->getName()) + std::string(".") + chan;
            std::set<Channel> channels;
            lookupChannels(channels, chan_name.c_str());

            if (!channels.empty()) 
            {
                for (std::set<Channel>::iterator it = channels.begin(); it != channels.end(); it++) 
                {
                    Channel channel = *it;
                    channel_map[channel]= chan_name.c_str();
                    std::pair<int, int> idx(i, j);
                    rat_chan_index[channel] = idx;
                     
                    #if defined(DEBUG)
                    iop->warning("Rat %s (%i,%i) becomes %s", chan_name.c_str(), i, j, getName(channel));
                    #endif
                    mask += channel;
                }
            }
            else
                iop->warning("Can't create a channel from %s", chan_name.c_str());
        }
    }
    // Set info:
    #if defined(DEBUG)
    iop->warning("Channel number: %i", depth);
    #endif
    set_info(stat.getDataWidth(), stat.getDataHeight(), depth);
    info_.channels(mask);
}