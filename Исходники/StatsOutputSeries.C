  void printStatsRGB(const Image<PixRGB<byte> >& img,
                     const std::string& imgname, const std::string& imgtype)
  {
    this->openFile();

    Image<byte> r, g, b;
    getComponents(img, r, g, b);

    const double mean_r = mean(r);
    const double stdev_r = stdev(r);
    const Range<byte> range_r = getRange(r);

    const double mean_g = mean(g);
    const double stdev_g = stdev(g);
    const Range<byte> range_g = getRange(g);

    const double mean_b = mean(b);
    const double stdev_b = stdev(b);
    const Range<byte> range_b = getRange(b);

    fprintf(this->file,
            "%06d "
            "R=[%d .. %f +/- %f .. %d] "
            "G=[%d .. %f +/- %f .. %d] "
            "B=[%d .. %f +/- %f .. %d] %% %s (%dx%d %s)\n",
            this->frameNumber,
            int(range_r.min()), mean_r, stdev_r, int(range_r.max()),
            int(range_g.min()), mean_g, stdev_g, int(range_g.max()),
            int(range_b.min()), mean_b, stdev_b, int(range_b.max()),
            imgname.c_str(), img.getWidth(), img.getHeight(),
            imgtype.c_str());
    fflush(this->file);

    this->rangeR.merge(range_r);
    this->rangeG.merge(range_g);
    this->rangeB.merge(range_b);

    this->meanR += mean_r;
    this->meanG += mean_g;
    this->meanB += mean_b;
    ++(this->count);
  }