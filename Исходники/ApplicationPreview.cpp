void ApplicationPreview::SetupViews()
{
  dash::ApplicationPreview* app_preview_model = dynamic_cast<dash::ApplicationPreview*>(preview_model_.get());
  if (!app_preview_model)
  {
    LOG_ERROR(logger) << "Could not derive application preview model from given parameter.";
    return;
  }

  previews::Style& style = dash::previews::Style::Instance();

  auto on_mouse_down = [this](int x, int y, unsigned long button_flags, unsigned long key_flags) { this->preview_container_->OnMouseDown(x, y, button_flags, key_flags); };

  nux::HLayout* image_data_layout = new nux::HLayout();
  image_data_layout->SetSpaceBetweenChildren(style.GetPanelSplitWidth());

  /////////////////////
  // Image
  image_ = new CoverArt();
  AddChild(image_.GetPointer());
  UpdateCoverArtImage(image_.GetPointer());
  /////////////////////

    /////////////////////
    // App Data Panel
    full_data_layout_ = new nux::VLayout();
    full_data_layout_->SetPadding(style.GetDetailsTopMargin(), 0, style.GetDetailsBottomMargin(), style.GetDetailsLeftMargin());
    full_data_layout_->SetSpaceBetweenChildren(16);

      /////////////////////
      // Main App Info
      nux::HLayout* main_app_info = new nux::HLayout();
      main_app_info->SetSpaceBetweenChildren(style.GetSpaceBetweenIconAndDetails());

        /////////////////////
        // Icon Layout
        nux::VLayout* icon_layout = new nux::VLayout();
        icon_layout->SetSpaceBetweenChildren(3);
        app_icon_ = new IconTexture(app_preview_model->app_icon.Get().RawPtr() ? g_icon_to_string(app_preview_model->app_icon.Get().RawPtr()) : "", 72);
        AddChild(app_icon_.GetPointer());
        app_icon_->SetMinimumSize(style.GetAppIconAreaWidth(), style.GetAppIconAreaWidth());
        app_icon_->SetMaximumSize(style.GetAppIconAreaWidth(), style.GetAppIconAreaWidth());
        app_icon_->mouse_click.connect(on_mouse_down);
        icon_layout->AddView(app_icon_.GetPointer(), 0);

        if (app_preview_model->rating >= 0) {
          app_rating_ = new PreviewRatingsWidget();
          AddChild(app_rating_.GetPointer());
          app_rating_->SetMaximumHeight(style.GetRatingWidgetHeight());
          app_rating_->SetMinimumHeight(style.GetRatingWidgetHeight());
          app_rating_->SetRating(app_preview_model->rating);
          app_rating_->SetReviews(app_preview_model->num_ratings);
          app_rating_->request_close().connect([this]() { preview_container_->request_close.emit(); });
          icon_layout->AddView(app_rating_.GetPointer(), 0);
        }

        /////////////////////

        /////////////////////
        // Data

        nux::VLayout* app_data_layout = new nux::VLayout();
        app_data_layout->SetSpaceBetweenChildren(16);

        title_subtitle_layout_ = new nux::VLayout();
        title_subtitle_layout_->SetSpaceBetweenChildren(style.GetSpaceBetweenTitleAndSubtitle());

        title_ = new StaticCairoText(preview_model_->title, true, NUX_TRACKER_LOCATION);
        AddChild(title_.GetPointer());
        title_->SetLines(-1);
        title_->SetFont(style.title_font().c_str());
        title_->mouse_click.connect(on_mouse_down);
        title_subtitle_layout_->AddView(title_.GetPointer(), 1);

        if (!preview_model_->subtitle.Get().empty())
        {
          subtitle_ = new StaticCairoText(preview_model_->subtitle, true, NUX_TRACKER_LOCATION);
          AddChild(subtitle_.GetPointer());
          subtitle_->SetFont(style.subtitle_size_font().c_str());
          subtitle_->SetLines(-1);
          subtitle_->mouse_click.connect(on_mouse_down);
          title_subtitle_layout_->AddView(subtitle_.GetPointer(), 1);
        }

        nux::VLayout* app_updated_copywrite_layout = new nux::VLayout();
        app_updated_copywrite_layout->SetSpaceBetweenChildren(8);

        if (!app_preview_model->license.Get().empty())
        {
          license_ = new StaticCairoText(app_preview_model->license, true, NUX_TRACKER_LOCATION);
          AddChild(license_.GetPointer());
          license_->SetFont(style.app_license_font().c_str());
          license_->SetLines(-1);
          license_->mouse_click.connect(on_mouse_down);
          app_updated_copywrite_layout->AddView(license_.GetPointer(), 1);
        }

        if (!app_preview_model->last_update.Get().empty())
        {
          std::stringstream last_update;
          last_update << _("Last Updated") << " " << app_preview_model->last_update.Get();

          last_update_ = new StaticCairoText(last_update.str(), true, NUX_TRACKER_LOCATION);
          AddChild(last_update_.GetPointer());
          last_update_->SetFont(style.app_last_update_font().c_str());
          last_update_->mouse_click.connect(on_mouse_down);
          app_updated_copywrite_layout->AddView(last_update_.GetPointer(), 1);
        }

        if (!app_preview_model->copyright.Get().empty())
        {
          copywrite_ = new StaticCairoText(app_preview_model->copyright, true, NUX_TRACKER_LOCATION);
          AddChild(copywrite_.GetPointer());
          copywrite_->SetFont(style.app_copywrite_font().c_str());
          copywrite_->SetLines(-1);
          copywrite_->mouse_click.connect(on_mouse_down);
          app_updated_copywrite_layout->AddView(copywrite_.GetPointer(), 1);
        }

        app_data_layout->AddLayout(title_subtitle_layout_);
        app_data_layout->AddLayout(app_updated_copywrite_layout);

        // buffer space
        /////////////////////

      main_app_info->AddLayout(icon_layout, 0);
      main_app_info->AddLayout(app_data_layout, 1);
      /////////////////////

      /////////////////////
      // Description
      nux::ScrollView* app_info = new DetailsScrollView(NUX_TRACKER_LOCATION);
      app_info->EnableHorizontalScrollBar(false);
      app_info->mouse_click.connect(on_mouse_down);

      nux::VLayout* app_info_layout = new nux::VLayout();
      app_info_layout->SetSpaceBetweenChildren(12);
      app_info->SetLayout(app_info_layout);

      if (!preview_model_->description.Get().empty())
      {
        description_ = new StaticCairoText(preview_model_->description, false, NUX_TRACKER_LOCATION); // not escaped!
        AddChild(description_.GetPointer());
        description_->SetFont(style.description_font().c_str());
        description_->SetTextAlignment(StaticCairoText::NUX_ALIGN_TOP);
        description_->SetLines(-style.GetDescriptionLineCount());
        description_->SetLineSpacing(style.GetDescriptionLineSpacing());
        description_->mouse_click.connect(on_mouse_down);
        app_info_layout->AddView(description_.GetPointer());
      }

      if (!preview_model_->GetInfoHints().empty())
      {
        preview_info_hints_ = new PreviewInfoHintWidget(preview_model_, style.GetInfoHintIconSizeWidth());
        AddChild(preview_info_hints_.GetPointer());
        preview_info_hints_->request_close().connect([this]() { preview_container_->request_close.emit(); });
        app_info_layout->AddView(preview_info_hints_.GetPointer());
      }
      /////////////////////

      /////////////////////
      // Actions
      action_buttons_.clear();
      nux::Layout* actions_layout = BuildGridActionsLayout(preview_model_->GetActions(), action_buttons_);
      actions_layout->SetLeftAndRightPadding(0, style.GetDetailsRightMargin());
      ///////////////////

    full_data_layout_->AddLayout(main_app_info, 0);
    full_data_layout_->AddView(app_info, 1);
    full_data_layout_->AddLayout(actions_layout, 0);
    /////////////////////
  
  image_data_layout->AddView(image_.GetPointer(), 0);
  image_data_layout->AddLayout(full_data_layout_, 1);

  mouse_click.connect(on_mouse_down);

  SetLayout(image_data_layout);
}