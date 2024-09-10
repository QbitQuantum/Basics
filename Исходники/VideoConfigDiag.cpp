VideoConfigDiag::VideoConfigDiag(wxWindow* parent, const std::string& title)
    : wxDialog(parent, wxID_ANY, wxString::Format(_("Dolphin %s Graphics Configuration"),
                                                  wxGetTranslation(StrToWxStr(title)))),
      vconfig(g_Config)
{
  vconfig.Load(File::GetUserPath(D_CONFIG_IDX) + "GFX.ini");

  Bind(wxEVT_UPDATE_UI, &VideoConfigDiag::OnUpdateUI, this);

  wxNotebook* const notebook = new wxNotebook(this, wxID_ANY);

  // -- GENERAL --
  {
    wxPanel* const page_general = new wxPanel(notebook);
    notebook->AddPage(page_general, _("General"));
    wxBoxSizer* const szr_general = new wxBoxSizer(wxVERTICAL);

    // - basic
    {
      wxFlexGridSizer* const szr_basic = new wxFlexGridSizer(2, 5, 5);

      // backend
      {
        label_backend = new wxStaticText(page_general, wxID_ANY, _("Backend:"));
        choice_backend = new wxChoice(page_general, wxID_ANY);
        RegisterControl(choice_backend, wxGetTranslation(backend_desc));

        for (const auto& backend : g_available_video_backends)
        {
          choice_backend->AppendString(wxGetTranslation(StrToWxStr(backend->GetDisplayName())));
        }

        choice_backend->SetStringSelection(
            wxGetTranslation(StrToWxStr(g_video_backend->GetDisplayName())));
        choice_backend->Bind(wxEVT_CHOICE, &VideoConfigDiag::Event_Backend, this);

        szr_basic->Add(label_backend, 1, wxALIGN_CENTER_VERTICAL, 5);
        szr_basic->Add(choice_backend, 1, 0, 0);
      }

      // adapter (D3D only)
      if (vconfig.backend_info.Adapters.size())
      {
        choice_adapter =
            CreateChoice(page_general, vconfig.iAdapter, wxGetTranslation(adapter_desc));

        for (const std::string& adapter : vconfig.backend_info.Adapters)
        {
          choice_adapter->AppendString(StrToWxStr(adapter));
        }

        choice_adapter->Select(vconfig.iAdapter);

        label_adapter = new wxStaticText(page_general, wxID_ANY, _("Adapter:"));
        szr_basic->Add(label_adapter, 1, wxALIGN_CENTER_VERTICAL, 5);
        szr_basic->Add(choice_adapter, 1, 0, 0);
      }

      // - display
      wxFlexGridSizer* const szr_display = new wxFlexGridSizer(2, 5, 5);

      {
#if !defined(__APPLE__)
        // display resolution
        {
          wxArrayString res_list = GetListOfResolutions();
          if (res_list.empty())
            res_list.Add(_("<No resolutions found>"));
          label_display_resolution =
              new wxStaticText(page_general, wxID_ANY, _("Fullscreen Resolution:"));
          choice_display_resolution =
              new wxChoice(page_general, wxID_ANY, wxDefaultPosition, wxDefaultSize, res_list);
          RegisterControl(choice_display_resolution, wxGetTranslation(display_res_desc));
          choice_display_resolution->Bind(wxEVT_CHOICE, &VideoConfigDiag::Event_DisplayResolution,
                                          this);

          choice_display_resolution->SetStringSelection(
              StrToWxStr(SConfig::GetInstance().strFullscreenResolution));

          szr_display->Add(label_display_resolution, 1, wxALIGN_CENTER_VERTICAL, 0);
          szr_display->Add(choice_display_resolution);
        }
#endif

        // aspect-ratio
        {
          const wxString ar_choices[] = {_("Auto"), _("Force 16:9"), _("Force 4:3"),
                                         _("Stretch to Window")};

          szr_display->Add(new wxStaticText(page_general, wxID_ANY, _("Aspect Ratio:")), 1,
                           wxALIGN_CENTER_VERTICAL, 0);
          wxChoice* const choice_aspect =
              CreateChoice(page_general, vconfig.iAspectRatio, wxGetTranslation(ar_desc),
                           sizeof(ar_choices) / sizeof(*ar_choices), ar_choices);
          szr_display->Add(choice_aspect, 1, 0, 0);
        }

        // various other display options
        {
          szr_display->Add(CreateCheckBox(page_general, _("V-Sync"), wxGetTranslation(vsync_desc),
                                          vconfig.bVSync));
          szr_display->Add(CreateCheckBox(page_general, _("Use Fullscreen"),
                                          wxGetTranslation(use_fullscreen_desc),
                                          SConfig::GetInstance().bFullscreen));
        }
      }

      // - other
      wxFlexGridSizer* const szr_other = new wxFlexGridSizer(2, 5, 5);

      {
        szr_other->Add(CreateCheckBox(page_general, _("Show FPS"), wxGetTranslation(show_fps_desc),
                                      vconfig.bShowFPS));
        szr_other->Add(CreateCheckBox(page_general, _("Show NetPlay Ping"),
                                      wxGetTranslation(show_netplay_ping_desc),
                                      vconfig.bShowNetPlayPing));
        szr_other->Add(CreateCheckBox(page_general, _("Log Render Time to File"),
                                      wxGetTranslation(log_render_time_to_file_desc),
                                      vconfig.bLogRenderTimeToFile));
        szr_other->Add(CreateCheckBox(page_general, _("Auto adjust Window Size"),
                                      wxGetTranslation(auto_window_size_desc),
                                      SConfig::GetInstance().bRenderWindowAutoSize));
        szr_other->Add(CreateCheckBox(page_general, _("Show NetPlay Messages"),
                                      wxGetTranslation(show_netplay_messages_desc),
                                      vconfig.bShowNetPlayMessages));
        szr_other->Add(CreateCheckBox(page_general, _("Keep Window on Top"),
                                      wxGetTranslation(keep_window_on_top_desc),
                                      SConfig::GetInstance().bKeepWindowOnTop));
        szr_other->Add(CreateCheckBox(page_general, _("Hide Mouse Cursor"),
                                      wxGetTranslation(hide_mouse_cursor_desc),
                                      SConfig::GetInstance().bHideCursor));
        szr_other->Add(render_to_main_checkbox =
                           CreateCheckBox(page_general, _("Render to Main Window"),
                                          wxGetTranslation(render_to_main_win_desc),
                                          SConfig::GetInstance().bRenderToMain));
      }

      wxStaticBoxSizer* const group_basic =
          new wxStaticBoxSizer(wxVERTICAL, page_general, _("Basic"));
      group_basic->Add(szr_basic, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
      szr_general->Add(group_basic, 0, wxEXPAND | wxALL, 5);

      wxStaticBoxSizer* const group_display =
          new wxStaticBoxSizer(wxVERTICAL, page_general, _("Display"));
      group_display->Add(szr_display, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
      szr_general->Add(group_display, 0, wxEXPAND | wxALL, 5);

      wxStaticBoxSizer* const group_other =
          new wxStaticBoxSizer(wxVERTICAL, page_general, _("Other"));
      group_other->Add(szr_other, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
      szr_general->Add(group_other, 0, wxEXPAND | wxALL, 5);
    }

    szr_general->AddStretchSpacer();
    CreateDescriptionArea(page_general, szr_general);
    page_general->SetSizerAndFit(szr_general);
  }

  // -- ENHANCEMENTS --
  {
    wxPanel* const page_enh = new wxPanel(notebook);
    notebook->AddPage(page_enh, _("Enhancements"));
    wxBoxSizer* const szr_enh_main = new wxBoxSizer(wxVERTICAL);

    // - enhancements
    wxFlexGridSizer* const szr_enh = new wxFlexGridSizer(2, 5, 5);

    // Internal resolution
    {
      const wxString efbscale_choices[] = {_("Auto (Window Size)"),
                                           _("Auto (Multiple of 640x528)"),
                                           _("Native (640x528)"),
                                           _("1.5x Native (960x792)"),
                                           _("2x Native (1280x1056) for 720p"),
                                           _("2.5x Native (1600x1320)"),
                                           _("3x Native (1920x1584) for 1080p"),
                                           _("4x Native (2560x2112) for 1440p"),
                                           _("5x Native (3200x2640)"),
                                           _("6x Native (3840x3168) for 4K"),
                                           _("7x Native (4480x3696)"),
                                           _("8x Native (5120x4224) for 5K"),
                                           _("Custom")};

      wxChoice* const choice_efbscale = CreateChoice(
          page_enh, vconfig.iEFBScale, wxGetTranslation(internal_res_desc),
          (vconfig.iEFBScale > 11) ? ArraySize(efbscale_choices) : ArraySize(efbscale_choices) - 1,
          efbscale_choices);

      if (vconfig.iEFBScale > 11)
        choice_efbscale->SetSelection(12);

      szr_enh->Add(new wxStaticText(page_enh, wxID_ANY, _("Internal Resolution:")), 1,
                   wxALIGN_CENTER_VERTICAL, 0);
      szr_enh->Add(choice_efbscale);
    }

    // AA
    {
      text_aamode = new wxStaticText(page_enh, wxID_ANY, _("Anti-Aliasing:"));
      choice_aamode = new wxChoice(page_enh, wxID_ANY);
      RegisterControl(choice_aamode, wxGetTranslation(aa_desc));
      PopulateAAList();
      choice_aamode->Bind(wxEVT_CHOICE, &VideoConfigDiag::OnAAChanged, this);

      szr_enh->Add(text_aamode, 1, wxALIGN_CENTER_VERTICAL, 0);
      szr_enh->Add(choice_aamode);
    }

    // AF
    {
      const wxString af_choices[] = {"1x", "2x", "4x", "8x", "16x"};
      szr_enh->Add(new wxStaticText(page_enh, wxID_ANY, _("Anisotropic Filtering:")), 1,
                   wxALIGN_CENTER_VERTICAL, 0);
      szr_enh->Add(
          CreateChoice(page_enh, vconfig.iMaxAnisotropy, wxGetTranslation(af_desc), 5, af_choices));
    }

    // postproc shader
    if (vconfig.backend_info.bSupportsPostProcessing)
    {
      wxFlexGridSizer* const szr_pp = new wxFlexGridSizer(3, 5, 5);
      choice_ppshader = new wxChoice(page_enh, wxID_ANY);
      RegisterControl(choice_ppshader, wxGetTranslation(ppshader_desc));
      button_config_pp = new wxButton(page_enh, wxID_ANY, _("Config"));

      PopulatePostProcessingShaders();

      choice_ppshader->Bind(wxEVT_CHOICE, &VideoConfigDiag::Event_PPShader, this);
      button_config_pp->Bind(wxEVT_BUTTON, &VideoConfigDiag::Event_ConfigurePPShader, this);

      szr_enh->Add(new wxStaticText(page_enh, wxID_ANY, _("Post-Processing Effect:")), 1,
                   wxALIGN_CENTER_VERTICAL, 0);
      szr_pp->Add(choice_ppshader);
      szr_pp->Add(button_config_pp);
      szr_enh->Add(szr_pp);
    }
    else
    {
      choice_ppshader = nullptr;
      button_config_pp = nullptr;
    }

    // Scaled copy, PL, Bilinear filter
    szr_enh->Add(CreateCheckBox(page_enh, _("Scaled EFB Copy"),
                                wxGetTranslation(scaled_efb_copy_desc), vconfig.bCopyEFBScaled));
    szr_enh->Add(CreateCheckBox(page_enh, _("Per-Pixel Lighting"),
                                wxGetTranslation(pixel_lighting_desc),
                                vconfig.bEnablePixelLighting));
    szr_enh->Add(CreateCheckBox(page_enh, _("Force Texture Filtering"),
                                wxGetTranslation(force_filtering_desc), vconfig.bForceFiltering));
    szr_enh->Add(CreateCheckBox(page_enh, _("Widescreen Hack"), wxGetTranslation(ws_hack_desc),
                                vconfig.bWidescreenHack));
    szr_enh->Add(CreateCheckBox(page_enh, _("Disable Fog"), wxGetTranslation(disable_fog_desc),
                                vconfig.bDisableFog));

    wxStaticBoxSizer* const group_enh =
        new wxStaticBoxSizer(wxVERTICAL, page_enh, _("Enhancements"));
    group_enh->Add(szr_enh, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    szr_enh_main->Add(group_enh, 0, wxEXPAND | wxALL, 5);

    // - stereoscopy

    if (vconfig.backend_info.bSupportsGeometryShaders)
    {
      wxFlexGridSizer* const szr_stereo = new wxFlexGridSizer(2, 5, 5);

      szr_stereo->Add(new wxStaticText(page_enh, wxID_ANY, _("Stereoscopic 3D Mode:")), 1,
                      wxALIGN_CENTER_VERTICAL, 0);

      const wxString stereo_choices[] = {_("Off"), _("Side-by-Side"), _("Top-and-Bottom"),
                                         _("Anaglyph"), _("Nvidia 3D Vision")};
      wxChoice* stereo_choice =
          CreateChoice(page_enh, vconfig.iStereoMode, wxGetTranslation(stereo_3d_desc),
                       vconfig.backend_info.bSupports3DVision ? ArraySize(stereo_choices) :
                                                                ArraySize(stereo_choices) - 1,
                       stereo_choices);
      stereo_choice->Bind(wxEVT_CHOICE, &VideoConfigDiag::Event_StereoMode, this);
      szr_stereo->Add(stereo_choice);

      wxSlider* const sep_slider = new wxSlider(page_enh, wxID_ANY, vconfig.iStereoDepth, 0, 100,
                                                wxDefaultPosition, wxDefaultSize);
      sep_slider->Bind(wxEVT_SLIDER, &VideoConfigDiag::Event_StereoDepth, this);
      RegisterControl(sep_slider, wxGetTranslation(stereo_depth_desc));

      szr_stereo->Add(new wxStaticText(page_enh, wxID_ANY, _("Depth:")), 1, wxALIGN_CENTER_VERTICAL,
                      0);
      szr_stereo->Add(sep_slider, 0, wxEXPAND | wxRIGHT);

      conv_slider = new wxSlider(page_enh, wxID_ANY, vconfig.iStereoConvergencePercentage, 0, 200,
                                 wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS);
      conv_slider->ClearTicks();
      conv_slider->SetTick(100);
      conv_slider->Bind(wxEVT_SLIDER, &VideoConfigDiag::Event_StereoConvergence, this);
      RegisterControl(conv_slider, wxGetTranslation(stereo_convergence_desc));

      szr_stereo->Add(new wxStaticText(page_enh, wxID_ANY, _("Convergence:")), 1,
                      wxALIGN_CENTER_VERTICAL, 0);
      szr_stereo->Add(conv_slider, 0, wxEXPAND | wxRIGHT);

      szr_stereo->Add(CreateCheckBox(page_enh, _("Swap Eyes"), wxGetTranslation(stereo_swap_desc),
                                     vconfig.bStereoSwapEyes));

      wxStaticBoxSizer* const group_stereo =
          new wxStaticBoxSizer(wxVERTICAL, page_enh, _("Stereoscopy"));
      group_stereo->Add(szr_stereo, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
      szr_enh_main->Add(group_stereo, 0, wxEXPAND | wxALL, 5);
    }

    szr_enh_main->AddStretchSpacer();
    CreateDescriptionArea(page_enh, szr_enh_main);
    page_enh->SetSizerAndFit(szr_enh_main);
  }

  // -- SPEED HACKS --
  {
    wxPanel* const page_hacks = new wxPanel(notebook);
    notebook->AddPage(page_hacks, _("Hacks"));
    wxBoxSizer* const szr_hacks = new wxBoxSizer(wxVERTICAL);

    // - EFB hacks
    wxStaticBoxSizer* const szr_efb =
        new wxStaticBoxSizer(wxVERTICAL, page_hacks, _("Embedded Frame Buffer (EFB)"));

    szr_efb->Add(CreateCheckBox(page_hacks, _("Skip EFB Access from CPU"),
                                wxGetTranslation(efb_access_desc), vconfig.bEFBAccessEnable, true),
                 0, wxBOTTOM | wxLEFT, 5);
    szr_efb->Add(CreateCheckBox(page_hacks, _("Ignore Format Changes"),
                                wxGetTranslation(efb_emulate_format_changes_desc),
                                vconfig.bEFBEmulateFormatChanges, true),
                 0, wxBOTTOM | wxLEFT, 5);
    szr_efb->Add(CreateCheckBox(page_hacks, _("Store EFB Copies to Texture Only"),
                                wxGetTranslation(skip_efb_copy_to_ram_desc),
                                vconfig.bSkipEFBCopyToRam),
                 0, wxBOTTOM | wxLEFT, 5);

    szr_hacks->Add(szr_efb, 0, wxEXPAND | wxALL, 5);

    // Texture cache
    {
      wxStaticBoxSizer* const szr_safetex =
          new wxStaticBoxSizer(wxHORIZONTAL, page_hacks, _("Texture Cache"));

      // TODO: Use wxSL_MIN_MAX_LABELS or wxSL_VALUE_LABEL with wx 2.9.1
      wxSlider* const stc_slider = new wxSlider(page_hacks, wxID_ANY, 0, 0, 2, wxDefaultPosition,
                                                wxDefaultSize, wxSL_HORIZONTAL | wxSL_BOTTOM);
      stc_slider->Bind(wxEVT_SLIDER, &VideoConfigDiag::Event_Stc, this);
      RegisterControl(stc_slider, wxGetTranslation(stc_desc));

      if (vconfig.iSafeTextureCache_ColorSamples == 0)
        stc_slider->SetValue(0);
      else if (vconfig.iSafeTextureCache_ColorSamples == 512)
        stc_slider->SetValue(1);
      else if (vconfig.iSafeTextureCache_ColorSamples == 128)
        stc_slider->SetValue(2);
      else
        stc_slider->Disable();  // Using custom number of samples; TODO: Inform the user why this is
                                // disabled..

      szr_safetex->Add(new wxStaticText(page_hacks, wxID_ANY, _("Accuracy:")), 0, wxALL, 5);
      szr_safetex->AddStretchSpacer(1);
      szr_safetex->Add(new wxStaticText(page_hacks, wxID_ANY, _("Safe")), 0,
                       wxLEFT | wxTOP | wxBOTTOM, 5);
      szr_safetex->Add(stc_slider, 2, wxRIGHT, 0);
      szr_safetex->Add(new wxStaticText(page_hacks, wxID_ANY, _("Fast")), 0,
                       wxRIGHT | wxTOP | wxBOTTOM, 5);
      szr_hacks->Add(szr_safetex, 0, wxEXPAND | wxALL, 5);
    }

    // - XFB
    {
      wxStaticBoxSizer* const group_xfb =
          new wxStaticBoxSizer(wxHORIZONTAL, page_hacks, _("External Frame Buffer (XFB)"));

      SettingCheckBox* disable_xfb = CreateCheckBox(
          page_hacks, _("Disable"), wxGetTranslation(xfb_desc), vconfig.bUseXFB, true);
      virtual_xfb = CreateRadioButton(page_hacks, _("Virtual"), wxGetTranslation(xfb_virtual_desc),
                                      vconfig.bUseRealXFB, true, wxRB_GROUP);
      real_xfb = CreateRadioButton(page_hacks, _("Real"), wxGetTranslation(xfb_real_desc),
                                   vconfig.bUseRealXFB);

      group_xfb->Add(disable_xfb, 0, wxLEFT | wxRIGHT | wxBOTTOM, 5);
      group_xfb->AddStretchSpacer(1);
      group_xfb->Add(virtual_xfb, 0, wxRIGHT, 5);
      group_xfb->Add(real_xfb, 0, wxRIGHT, 5);
      szr_hacks->Add(group_xfb, 0, wxEXPAND | wxALL, 5);
    }  // xfb

    // - other hacks
    {
      wxGridSizer* const szr_other = new wxGridSizer(2, 5, 5);
      szr_other->Add(CreateCheckBox(page_hacks, _("Fast Depth Calculation"),
                                    wxGetTranslation(fast_depth_calc_desc),
                                    vconfig.bFastDepthCalc));
      szr_other->Add(CreateCheckBox(page_hacks, _("Disable Bounding Box"),
                                    wxGetTranslation(disable_bbox_desc), vconfig.bBBoxEnable,
                                    true));

      wxStaticBoxSizer* const group_other =
          new wxStaticBoxSizer(wxVERTICAL, page_hacks, _("Other"));
      group_other->Add(szr_other, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
      szr_hacks->Add(group_other, 0, wxEXPAND | wxALL, 5);
    }

    szr_hacks->AddStretchSpacer();
    CreateDescriptionArea(page_hacks, szr_hacks);
    page_hacks->SetSizerAndFit(szr_hacks);
  }

  // -- ADVANCED --
  {
    wxPanel* const page_advanced = new wxPanel(notebook);
    notebook->AddPage(page_advanced, _("Advanced"));
    wxBoxSizer* const szr_advanced = new wxBoxSizer(wxVERTICAL);

    // - debug
    {
      wxGridSizer* const szr_debug = new wxGridSizer(2, 5, 5);

      szr_debug->Add(CreateCheckBox(page_advanced, _("Enable Wireframe"),
                                    wxGetTranslation(wireframe_desc), vconfig.bWireFrame));
      szr_debug->Add(CreateCheckBox(page_advanced, _("Show Statistics"),
                                    wxGetTranslation(show_stats_desc), vconfig.bOverlayStats));
      szr_debug->Add(CreateCheckBox(page_advanced, _("Texture Format Overlay"),
                                    wxGetTranslation(texfmt_desc), vconfig.bTexFmtOverlayEnable));

      wxStaticBoxSizer* const group_debug =
          new wxStaticBoxSizer(wxVERTICAL, page_advanced, _("Debugging"));
      szr_advanced->Add(group_debug, 0, wxEXPAND | wxALL, 5);
      group_debug->Add(szr_debug, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    }

    // - utility
    {
      wxGridSizer* const szr_utility = new wxGridSizer(2, 5, 5);

      szr_utility->Add(CreateCheckBox(page_advanced, _("Dump Textures"),
                                      wxGetTranslation(dump_textures_desc), vconfig.bDumpTextures));
      szr_utility->Add(CreateCheckBox(page_advanced, _("Load Custom Textures"),
                                      wxGetTranslation(load_hires_textures_desc),
                                      vconfig.bHiresTextures));
      cache_hires_textures =
          CreateCheckBox(page_advanced, _("Prefetch Custom Textures"),
                         wxGetTranslation(cache_hires_textures_desc), vconfig.bCacheHiresTextures);
      szr_utility->Add(cache_hires_textures);
      szr_utility->Add(CreateCheckBox(page_advanced, _("Dump EFB Target"),
                                      wxGetTranslation(dump_efb_desc), vconfig.bDumpEFBTarget));
      szr_utility->Add(CreateCheckBox(page_advanced, _("Free Look"),
                                      wxGetTranslation(free_look_desc), vconfig.bFreeLook));
#if defined(HAVE_LIBAV) || defined(_WIN32)
      szr_utility->Add(CreateCheckBox(page_advanced, _("Frame Dumps use FFV1"),
                                      wxGetTranslation(use_ffv1_desc), vconfig.bUseFFV1));
#endif

      wxStaticBoxSizer* const group_utility =
          new wxStaticBoxSizer(wxVERTICAL, page_advanced, _("Utility"));
      szr_advanced->Add(group_utility, 0, wxEXPAND | wxALL, 5);
      group_utility->Add(szr_utility, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    }

    // - misc
    {
      wxGridSizer* const szr_misc = new wxGridSizer(2, 5, 5);

      szr_misc->Add(
          CreateCheckBox(page_advanced, _("Crop"), wxGetTranslation(crop_desc), vconfig.bCrop));

      // Progressive Scan
      {
        progressive_scan_checkbox =
            new wxCheckBox(page_advanced, wxID_ANY, _("Enable Progressive Scan"));
        RegisterControl(progressive_scan_checkbox, wxGetTranslation(prog_scan_desc));
        progressive_scan_checkbox->Bind(wxEVT_CHECKBOX, &VideoConfigDiag::Event_ProgressiveScan,
                                        this);

        progressive_scan_checkbox->SetValue(SConfig::GetInstance().bProgressive);
        // A bit strange behavior, but this needs to stay in sync with the main progressive boolean;
        // TODO: Is this still necessary?
        SConfig::GetInstance().m_SYSCONF->SetData("IPL.PGS", SConfig::GetInstance().bProgressive);

        szr_misc->Add(progressive_scan_checkbox);
      }

#if defined WIN32
      // Borderless Fullscreen
      borderless_fullscreen = CreateCheckBox(page_advanced, _("Borderless Fullscreen"),
                                             wxGetTranslation(borderless_fullscreen_desc),
                                             vconfig.bBorderlessFullscreen);
      szr_misc->Add(borderless_fullscreen);
#endif

      wxStaticBoxSizer* const group_misc =
          new wxStaticBoxSizer(wxVERTICAL, page_advanced, _("Misc"));
      szr_advanced->Add(group_misc, 0, wxEXPAND | wxALL, 5);
      group_misc->Add(szr_misc, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    }

    szr_advanced->AddStretchSpacer();
    CreateDescriptionArea(page_advanced, szr_advanced);
    page_advanced->SetSizerAndFit(szr_advanced);
  }

  wxButton* const btn_close = new wxButton(this, wxID_OK, _("Close"));
  btn_close->Bind(wxEVT_BUTTON, &VideoConfigDiag::Event_ClickClose, this);

  Bind(wxEVT_CLOSE_WINDOW, &VideoConfigDiag::Event_Close, this);

  wxBoxSizer* const szr_main = new wxBoxSizer(wxVERTICAL);
  szr_main->Add(notebook, 1, wxEXPAND | wxALL, 5);
  szr_main->Add(btn_close, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 5);

  SetSizerAndFit(szr_main);
  Center();
  SetFocus();

  UpdateWindowUI();
}