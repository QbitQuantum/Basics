bool flif_decode(IO& io, Images &images, int quality, int scale, uint32_t (*callback)(int,int), Images &partial_images) {
    if (scale != 1 && scale != 2 && scale != 4 && scale != 8 && scale != 16 && scale != 32 && scale != 64 && scale != 128) {
                e_printf("Invalid scale down factor: %i\n", scale);
                return false;
    }

    char buff[5];
    if (!io.gets(buff,5)) { e_printf("Could not read header from file: %s\n",io.getName()); return false; }
    if (!strcmp(buff,"!<ar")) {
       // FLIF file in an archive, try to find find the main image
       if (!io.gets(buff,5)) return false;
       if (strcmp(buff,"ch>\n")) return false;
       char ar_header[61];
       while (true) {
          if (!io.gets(ar_header,61)) { e_printf("Archive does not contain a FLIF image\n"); return false; }
          if (!strncmp(ar_header,"__image.flif/",13)) {
            if (!io.gets(buff,5)) { e_printf("Corrupt archive?\n"); return false; }
            break;
          }
          else {
            long skip = strtol(&ar_header[48],NULL,10);
            if (skip < 0) return false;
            if (skip & 1) skip++;
            io.fseek(skip,SEEK_CUR);
          }
       }
    }
    if (strcmp(buff,"FLIF")) { e_printf("Not a FLIF file: %s (header: \"%s\")\n",io.getName(),buff); return false; }
    int c = io.getc();
    if (c < ' ' || c > ' '+32+15+32) { e_printf("Invalid or unknown FLIF format byte\n"); return false;}
    c -= ' ';
    int numFrames=1;
    if (c > 47) {
        c -= 32;
        numFrames = io.getc();
        if (numFrames < 2 || numFrames >= 255) return false;
    }
    const int encoding=c/16;
    if (encoding < 1 || encoding > 2) { e_printf("Invalid or unknown FLIF encoding method\n"); return false;}
    if (scale != 1 && encoding==1) { v_printf(1,"Cannot decode non-interlaced FLIF file at lower scale! Ignoring scale...\n");}
    if (quality < 100 && encoding==1) { v_printf(1,"Cannot decode non-interlaced FLIF file at lower quality! Ignoring quality...\n");}
    int numPlanes=c%16;
    if (numPlanes < 1 || numPlanes > 4) {e_printf("Invalid FLIF header (unsupported color channels)\n"); return false;}
    c = io.getc();
    if (c < '0' || c > '2')  {e_printf("Invalid FLIF header (unsupported color depth)\n"); return false;}

    int width=io.getc() << 8;
    width += io.getc();
    int height=io.getc() << 8;
    height += io.getc();
    if (width < 1 || height < 1) {e_printf("Invalid FLIF header\n"); return false;}

    // TODO: implement downscaled decoding without allocating a fullscale image buffer!

    RacIn<IO> rac(io);
    SimpleSymbolCoder<FLIFBitChanceMeta, RacIn<IO>, 24> metaCoder(rac);

//    image.init(width, height, 0, 0, 0);
    v_printf(3,"Decoding %ux%u image, channels:",width,height);
    int maxmax=0;
    for (int p = 0; p < numPlanes; p++) {
//        int min = 0;
        int max = 255;
        if (c=='2') max=65535;
        else if (c=='0') max=(1 << metaCoder.read_int(1, 16)) - 1;
        if (max>maxmax) maxmax=max;
//        image.add_plane(min, max);
//        v_printf(2," [%i] %i bpp (%i..%i)",p,ilog2(image.max(p)+1),image.min(p), image.max(p));
        if (c=='0') v_printf(3," [%i] %i bpp",p,ilog2(max+1));
    }
    if (c=='1') v_printf(3," %i, depth: 8 bit",numPlanes);
    if (c=='2') v_printf(3," %i, depth: 16 bit",numPlanes);
    if (numFrames>1) v_printf(3,", frames: %i",numFrames);
    v_printf(3,"\n");

    if (numFrames>1) {
        // ignored for now (assuming loop forever)
        metaCoder.read_int(0, 100); // repeats (0=infinite)
    }

    for (int i=0; i<numFrames; i++) {
      images.push_back(Image());
      if (!images[i].init(width,height,0,maxmax,numPlanes)) return false;
      if (numFrames>1) images[i].frame_delay = metaCoder.read_int(0, 60000); // time in ms between frames
      if (callback) partial_images.push_back(Image());
      //if (numFrames>1) partial_images[i].frame_delay = images[i].frame_delay;
    }
    std::vector<const ColorRanges*> rangesList;
    std::vector<Transform<IO>*> transforms;
    rangesList.push_back(getRanges(images[0]));
    v_printf(4,"Transforms: ");
    int tcount=0;
    transform_l=0;
    while (rac.read()) {
        if (transform_l > MAX_TRANSFORM) return false;
        std::string desc = read_name(rac);
        Transform<IO> *trans = create_transform<IO>(desc);
        if (!trans) {
            e_printf("Unknown transformation '%s'\n", desc.c_str());
            return false;
        }
        if (!trans->init(rangesList.back())) {
            e_printf("Transformation '%s' failed\n", desc.c_str());
            return false;
        }
        if (tcount++ > 0) v_printf(4,", ");
        v_printf(4,"%s", desc.c_str());
        if (desc == "FRA" && images.size()<2) return false;
        if (desc == "FRS") {
                if (images.size()<2) return false;
                int unique_frames=images.size()-1; // not considering first frame
                for (Image& i : images) if (i.seen_before >= 0) unique_frames--;
                if (unique_frames < 1) {return false;}
                trans->configure(unique_frames*images[0].rows()); trans->configure(images[0].cols()); }
        if (desc == "DUP") { if (images.size()<2) return false; else trans->configure(images.size()); }
        if (!trans->load(rangesList.back(), rac)) return false;
        rangesList.push_back(trans->meta(images, rangesList.back()));
        transforms.push_back(trans);
    }
    if (tcount==0) v_printf(4,"none\n"); else v_printf(4,"\n");
    const ColorRanges* ranges = rangesList.back();
    grey.clear();
    for (int p = 0; p < ranges->numPlanes(); p++) grey.push_back((ranges->min(p)+ranges->max(p))/2);

    pixels_todo = (int64_t)width*height*ranges->numPlanes()/scale/scale;
    pixels_done = 0;

    for (int p = 0; p < ranges->numPlanes(); p++) {
      v_printf(7,"Plane %i: %i..%i\n",p,ranges->min(p),ranges->max(p));
    }

    for (int p = 0; p < ranges->numPlanes(); p++) {
        if (ranges->min(p) >= ranges->max(p)) {
             v_printf(4,"Constant plane %i at color value %i\n",p,ranges->min(p));
             //for (ColorVal_intern& x : image(p).data) x=ranges->min(p);
            for (int fr = 0; fr < numFrames; fr++)
            for (uint32_t r=0; r<images[fr].rows(); r++) {
              for (uint32_t c=0; c<images[fr].cols(); c++) {
                images[fr].set(p,r,c,ranges->min(p));
              }
            }
        }
    }
    int mbits = 0;
    for (int p = 0; p < ranges->numPlanes(); p++) {
        if (ranges->max(p) > ranges->min(p)) {
          int nBits = ilog2((ranges->max(p) - ranges->min(p))*2-1)+1;
          if (nBits > mbits) mbits = nBits;
        }
    }
    int bits = 10;
#ifdef SUPPORT_HDR
    if (mbits >10) bits=18;
#endif
    if (mbits > bits) { e_printf("This FLIF cannot decode >8 bit per channel files. Please compile with SUPPORT_HDR.\n"); return false;}


    std::vector<Tree> forest(ranges->numPlanes(), Tree());
    int roughZL = 0;
    if (encoding == 2) {
      roughZL = images[0].zooms() - NB_NOLEARN_ZOOMS-1;
      if (roughZL < 0) roughZL = 0;
//      v_printf(2,"Decoding rough data\n");
      if (bits==10) flif_decode_FLIF2_pass<IO, RacIn<IO>, FinalPropertySymbolCoder<FLIFBitChancePass2, RacIn<IO>, 10> >(rac, images, ranges, forest, images[0].zooms(), roughZL+1, 100, scale, transforms, callback, partial_images);
#ifdef SUPPORT_HDR
      else flif_decode_FLIF2_pass<IO, RacIn<IO>, FinalPropertySymbolCoder<FLIFBitChancePass2, RacIn<IO>, 18> >(rac, images, ranges, forest, images[0].zooms(), roughZL+1, 100, scale, transforms, callback, partial_images);
#endif
    }
    if (encoding == 2 && quality <= 0) {
      v_printf(3,"Not decoding MANIAC tree\n");
    } else {
      v_printf(3,"Decoded header + rough data. Decoding MANIAC tree.\n");
      if (!flif_decode_tree<FLIFBitChanceTree, RacIn<IO>>(rac, ranges, forest, encoding)) return false;
    }


    switch(encoding) {
        case 1: v_printf(3,"Decoding data (scanlines)\n");
                if (bits==10) flif_decode_scanlines_pass<IO, RacIn<IO>, FinalPropertySymbolCoder<FLIFBitChancePass2, RacIn<IO>, 10> >(rac, images, ranges, forest, transforms, callback, partial_images);
#ifdef SUPPORT_HDR
                else flif_decode_scanlines_pass<IO, RacIn<IO>, FinalPropertySymbolCoder<FLIFBitChancePass2, RacIn<IO>, 18> >(rac, images, ranges, forest, transforms, callback, partial_images);
#endif
                break;
        case 2: v_printf(3,"Decoding data (interlaced)\n");
                if (bits==10) flif_decode_FLIF2_pass<IO, RacIn<IO>, FinalPropertySymbolCoder<FLIFBitChancePass2, RacIn<IO>, 10> >(rac, images, ranges, forest, roughZL, 0, quality, scale, transforms, callback, partial_images);
#ifdef SUPPORT_HDR
                else flif_decode_FLIF2_pass<IO, RacIn<IO>, FinalPropertySymbolCoder<FLIFBitChancePass2, RacIn<IO>, 18> >(rac, images, ranges, forest, roughZL, 0, quality, scale, transforms, callback, partial_images);
#endif
                break;
    }
 

    if (quality==100 && scale==1) {
      uint32_t checksum = images[0].checksum();
      v_printf(8,"Computed checksum: %X\n", checksum);
      uint32_t checksum2 = metaCoder.read_int(0, 0xFFFF);
      checksum2 *= 0x10000;
      checksum2 += metaCoder.read_int(0, 0xFFFF);
      v_printf(8,"Read checksum: %X\n", checksum2);
      if (checksum != checksum2) v_printf(1,"\nCORRUPTION DETECTED! (partial file?)\n\n");
      else v_printf(2,"Image decoded, checksum verified.\n");
    } else {
      v_printf(2,"Not checking checksum, lossy partial decoding was chosen.\n");
    }

   if (numFrames==1)
      v_printf(2,"\rDecoding done, %li bytes for %ux%u pixels (%.4fbpp)   \n",rac.ftell(), images[0].cols()/scale, images[0].rows()/scale, 8.0*rac.ftell()/images[0].rows()/images[0].cols()/scale/scale);
    else
      v_printf(2,"\rDecoding done, %li bytes for %i frames of %ux%u pixels (%.4fbpp)   \n",rac.ftell(), numFrames, images[0].cols()/scale, images[0].rows()/scale, 8.0*rac.ftell()/numFrames/images[0].rows()/images[0].cols()/scale/scale);


    for (int i=(int)transforms.size()-1; i>=0; i--) {
        transforms[i]->invData(images);
        delete transforms[i];
    }
    transforms.clear();


    for (unsigned int i=0; i<rangesList.size(); i++) {
        delete rangesList[i];
    }
    rangesList.clear();

    return true;
}