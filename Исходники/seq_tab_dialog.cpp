  void seq_tab_dialog::create_device_independent_resources()
  {
    // Direct2DFactory の生成
    if(!d2d_factory_){
#if defined(DEBUG) || defined(_DEBUG)
      D2D1_FACTORY_OPTIONS options;
      options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION ;
      THROW_IFERR(D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        options,
        d2d_factory_.GetAddressOf()
        ));
#else
      THROW_IFERR(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory_));
#endif

    }

    if(!write_factory_){
      THROW_IFERR(::DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(write_factory_.GetAddressOf())
        ));
    }


    //wic_imaging_factory_.CreateInstance(CLSID_WICImagingFactory);

    //thunk_proc_ = (WNDPROC)thunk_.getCode();
    layout_rect_ = D2D1::RectF(0.0f,100.0f,400.0f,100.0f);
    // Text Formatの作成
    THROW_IFERR(write_factory_->CreateTextFormat(
      L"MS GOTHIC",                // Font family name.
      NULL,                       // Font collection (NULL sets it to use the system font collection).
      DWRITE_FONT_WEIGHT_BOLD,
      DWRITE_FONT_STYLE_NORMAL,
      DWRITE_FONT_STRETCH_NORMAL,
      12.0f,
      L"ja-jp",
      &write_text_format_
      ));

  }