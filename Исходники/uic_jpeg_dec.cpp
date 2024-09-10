  ExcStatus ReadHeader(
    ImageColorSpec&        colorSpec,
    ImageSamplingGeometry& geometry)
  {
    int        i;
    Point      origin;
    RectSize   size;
    Rect       refgrid;
    JERRCODE   jerr;

    jerr = CJPEGDecoder::ReadHeader(&m_size.width, &m_size.height, &m_nchannels, &m_color, &m_sampling, &m_precision);
    if(JPEG_OK != jerr)
      return ExcStatusFail;

    origin.SetX(0);
    origin.SetY(0);

    size.SetWidth(m_size.width);
    size.SetHeight(m_size.height);

    refgrid.SetOrigin(origin);
    refgrid.SetSize(size);

    geometry.SetRefGridRect(refgrid);

    geometry.ReAlloc(m_nchannels);
    geometry.SetEnumSampling(j2u_smap[m_sampling]);

    colorSpec.ReAlloc(m_nchannels);
    colorSpec.SetColorSpecMethod(UIC::Enumerated);
    colorSpec.SetComponentToColorMap(UIC::Direct);
    colorSpec.SetEnumColorSpace(j2u_cmap[m_color]);

    if(m_precision <= 8)
    {
      for(i = 0; i < m_nchannels; i++)
        colorSpec.DataRange()[i].SetAsRange8u((1 << m_precision) - 1);
    }
    else
    {
      for(i = 0; i < m_nchannels; i++)
        colorSpec.DataRange()[i].SetAsRange16u((1 << m_precision) - 1);
    }

    return ExcStatusOk;
  }