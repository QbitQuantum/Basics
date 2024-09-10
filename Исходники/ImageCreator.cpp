  ExitCodes main_(int, const char **)
  {
    //----------------------------------------------------------------
    // load data
    //----------------------------------------------------------------
    String in = getStringOption_("in");
    String in_featureXML = getStringOption_("in_featureXML");
    String out = getStringOption_("out");
    String format = getStringOption_("out_type");
    if (format.trim() == "") // get from filename
    {
      try
      {
        format = out.suffix('.');
      }
      catch (Exception::ElementNotFound & /*e*/)
      {
        format = "nosuffix";
      }
      StringListUtils::toUpper(out_formats_);
      if (!ListUtils::contains(out_formats_, format.toUpper()))
      {
        LOG_ERROR << "No explicit image output format was provided via 'out_type', and the suffix ('" << format << "') does not resemble a valid type. Please fix one of them." << std::endl;
        return ILLEGAL_PARAMETERS;
      }
    }
    MSExperiment<> exp;
    MzMLFile f;
    f.setLogType(log_type_);
    f.load(in, exp);

    exp.updateRanges(1);

    SignedSize rows = getIntOption_("height");
    if (rows == 0)
    {
      rows = exp.size();
    }
    if (rows <= 0)
    {
      writeLog_("Error: Zero rows is not possible.");
      return ILLEGAL_PARAMETERS;
    }

    SignedSize cols = getIntOption_("width");
    if (cols == 0)
    {
      cols = UInt(ceil(exp.getMaxMZ() - exp.getMinMZ()));
    }
    if (cols <= 0)
    {
      writeLog_("Error: Zero columns is not possible.");
      return ILLEGAL_PARAMETERS;
    }

    //----------------------------------------------------------------
    //Do the actual resampling
    BilinearInterpolation<double, double> bilip;
    bilip.getData().resize(rows, cols);

    if (!getFlag_("transpose"))
    {
      // scans run bottom-up:
      bilip.setMapping_0(0, exp.getMaxRT(), rows - 1, exp.getMinRT());
      // peaks run left-right:
      bilip.setMapping_1(0, exp.getMinMZ(), cols - 1, exp.getMaxMZ());

      for (MSExperiment<>::Iterator spec_iter = exp.begin();
           spec_iter != exp.end(); ++spec_iter)
      {
        if (spec_iter->getMSLevel() != 1) continue;
        for (MSExperiment<>::SpectrumType::ConstIterator peak1_iter =
               spec_iter->begin(); peak1_iter != spec_iter->end();
             ++peak1_iter)
        {
          bilip.addValue(spec_iter->getRT(), peak1_iter->getMZ(),
                         peak1_iter->getIntensity());
        }
      }
    }
    else     // transpose
    {
      // spectra run bottom-up:
      bilip.setMapping_0(0, exp.getMaxMZ(), rows - 1, exp.getMinMZ());
      // scans run left-right:
      bilip.setMapping_1(0, exp.getMinRT(), cols - 1, exp.getMaxRT());

      for (MSExperiment<>::Iterator spec_iter = exp.begin();
           spec_iter != exp.end(); ++spec_iter)
      {
        if (spec_iter->getMSLevel() != 1) continue;
        for (MSExperiment<>::SpectrumType::ConstIterator peak1_iter =
               spec_iter->begin(); peak1_iter != spec_iter->end();
             ++peak1_iter)
        {
          bilip.addValue(peak1_iter->getMZ(), spec_iter->getRT(),
                         peak1_iter->getIntensity());
        }
      }
    }

    //----------------------------------------------------------------
    //create and store image
    int scans = (int) bilip.getData().sizePair().first;
    int peaks = (int) bilip.getData().sizePair().second;

    MultiGradient gradient;
    String gradient_str = getStringOption_("gradient");
    if (gradient_str != "")
    {
      gradient.fromString(String("Linear|") + gradient_str);
    }
    else
    {
      gradient.fromString("Linear|0,#FFFFFF;2,#FFFF00;11,#FFAA00;32,#FF0000;55,#AA00FF;78,#5500FF;100,#000000");
    }

    bool use_log = getFlag_("log_intensity");
    writeDebug_("log_intensity: " + String(use_log), 1);

    QImage image(peaks, scans, QImage::Format_RGB32);
    string s = getStringOption_("background_color");
    QColor background_color(s.c_str());

    string feature_color_string = getStringOption_("feature_color");
    QColor feature_color(feature_color_string.c_str());

    QPainter * painter = new QPainter(&image);
    painter->setPen(background_color);
    painter->fillRect(0, 0, peaks, scans, Qt::SolidPattern);
    delete painter;

    double factor = getDoubleOption_("max_intensity");
    if (factor == 0)
    {
      factor = (*std::max_element(bilip.getData().begin(), bilip.getData().end()));
    }
    // logarithmize max. intensity as well:
    if (use_log) factor = std::log(factor);

    factor /= 100.0;
    for (int i = 0; i < scans; ++i)
    {
      for (int j = 0; j < peaks; ++j)
      {
        double value = bilip.getData().getValue(i, j);
        if (use_log) value = std::log(value);
        if (value > 1e-4)
        {
          image.setPixel(j, i, gradient.interpolatedColorAt(value / factor).rgb());
        }
        else
        {
          image.setPixel(j, i, background_color.rgb());
        }
      }
    }

    if (getFlag_("precursors"))
    {
      markMS2Locations_(exp, image, getFlag_("transpose"),
                        getStringOption_("precursor_color").toQString(),
                        Size(getIntOption_("precursor_size")));
    }

    if (!in_featureXML.empty())
    {
      FeatureMap feature_map;
      FeatureXMLFile ff;
      ff.load(in_featureXML, feature_map);
      markFeatureLocations_(feature_map, exp, image, getFlag_("transpose"), feature_color);
    }

    if (image.save(out.toQString(), format.c_str())) return EXECUTION_OK;
    else return CANNOT_WRITE_OUTPUT_FILE;
  }