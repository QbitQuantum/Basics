void SplashDialog::Populate( ShuttleGui & S )
{
   //#if ((AUDACITY_BRANDING == BRAND_JAMLING__EASY) || (AUDACITY_BRANDING == BRAND_JAMLING__FULL))
   //   this->SetBackgroundColour(wxColour(rrr, ggg, bbb)); // same as waveform color
   //#else
   //   this->SetBackgroundColour(theTheme.Colour( clrAboutBoxBackground ));
   //#endif
   this->SetBackgroundColour(theTheme.Colour( clrAboutBoxBackground ));

   bool bShow;
   gPrefs->Read(wxT("/GUI/ShowSplashScreen"), &bShow, true );
   S.StartVerticalLay(1);

   wxImage buttonImageUp;
   wxImage buttonImageOver;
   wxSize buttonSize;
   wxBitmap* pButtonBitmap;
   wxBitmap* pButtonBitmapOver;
   //vvv Change this compile flag when other brands are supported. 
   #if ((AUDACITY_BRANDING == BRAND_JAMLING__EASY) || (AUDACITY_BRANDING == BRAND_JAMLING__FULL)) 
      //vvv Compiles only BRAND_JAMLING__EASY or BRAND_JAMLING__FULL 
      //    because we don't load any other company_logo*_xpm consts yet. 
      pButtonBitmap = new wxBitmap(company_logo_xpm);
      buttonImageUp = pButtonBitmap->ConvertToImage();
      pButtonBitmapOver = new wxBitmap(company_logo_over_xpm);
      buttonImageOver = pButtonBitmapOver->ConvertToImage();
      buttonSize = wxSize(pButtonBitmap->GetWidth(), pButtonBitmap->GetHeight()); 
      mButton_Logo = 
         new AButton(this, ID_BUTTON_LOGO, 
                     wxDefaultPosition, buttonSize, 
                     &buttonImageUp, &buttonImageOver, 
                     &buttonImageUp, &buttonImageUp, //v other images?
                     true); 
   #else
      //vvv For now, change to AudacityLogoWithName via old-fashioned ways, not Theme.
      pButtonBitmap = //vvv theTheme.Bitmap(bmpAudacityLogoWithName)
         new wxBitmap((const char **) AudacityLogoWithName_xpm); 
      buttonImageUp = pButtonBitmap->ConvertToImage();

      // JKC: Resize to 50% of size.  Later we may use a smaller xpm as
      // our source, but this allows us to tweak the size - if we want to.
      // It also makes it easier to revert to full size if we decide to.
      const float fScale=0.5f;// smaller size.
      buttonSize = wxSize(LOGOWITHNAME_WIDTH * fScale, LOGOWITHNAME_HEIGHT * fScale); 
      // wxIMAGE_QUALITY_HIGH not supported by wxWidgets 2.6.x, or we would use it here.
      buttonImageUp.Rescale(buttonSize.GetWidth(), buttonSize.GetHeight());

      buttonImageOver = buttonImageUp.Copy();
      buttonImageOver.RotateHue(-0.01);

      mButton_Logo = 
         new AButton(this, ID_BUTTON_LOGO, 
                     wxDefaultPosition, buttonSize, 
                     &buttonImageUp, &buttonImageOver, 
                     &buttonImageUp, &buttonImageUp, //v other images?
                     true); 
   #endif
   S.Prop(0).AddWindow(mButton_Logo);

   mpHtml = new LinkingHtmlWindow(S.GetParent(), -1,
                                         wxDefaultPosition,
                                         wxSize(kWidth, 280),
                                         wxHW_SCROLLBAR_AUTO | wxSUNKEN_BORDER );
   mpHtml->SetPage(HelpText( wxT("welcome") ));
   S.Prop(1).AddWindow( mpHtml, wxEXPAND );
   S.Prop(0).StartMultiColumn(2, wxEXPAND);
   S.SetStretchyCol( 1 );// Column 1 is stretchy...
   {
      S.SetBorder( 5 );
      S.Id( DontShowID).AddCheckBox( _("Don't show this again at start up"), bShow ? wxT("false") : wxT("true") );
      wxButton *ok = new wxButton(S.GetParent(), wxID_OK);
      ok->SetDefault();
      ok->SetFocus();
      S.SetBorder( 5 );
      S.Prop(0).AddWindow( ok, wxALIGN_RIGHT| wxALL );
   }
   S.EndVerticalLay();
}