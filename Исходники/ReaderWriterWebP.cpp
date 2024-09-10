  WriteResult writeImage(const osg::Image &img, std::ostream &fout, const Options *options) const
  {
    int internalFormat = osg::Image::computeNumComponents(img.getPixelFormat());

    WebPConfig config;
    config.quality = 75;
    config.method = 2;

    if (options)
    {
      std::istringstream iss(options->getOptionString());
      std::string opt;
      while (iss >> opt)
      {
        if (strcmp(opt.c_str(), "lossless") == 0)
        {
          config.lossless = 1;
          config.quality = 100;
        }
        else if (strcmp(opt.c_str(), "hint") == 0)
        {
          std::string v;
          iss >> v;
          if (strcmp(v.c_str(), "picture") == 0)
          {
            config.image_hint = WEBP_HINT_PICTURE;
          }
          else if (strcmp(v.c_str(), "photo") == 0)
          {
            config.image_hint = WEBP_HINT_PHOTO;
          }
          else if (strcmp(v.c_str(), "graph") == 0)
          {
            config.image_hint = WEBP_HINT_GRAPH;
          }
        }
        else if (strcmp(opt.c_str(), "quality") == 0)
        {
          float v;
          iss >> v;
          if (v >= 0.0 && v <= 100.0)
          {
            config.quality = v;
          }
        }