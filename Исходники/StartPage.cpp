// -----------------------------------------------------------------------------
// Initialises the start page
// -----------------------------------------------------------------------------
void SStartPage::init()
{
	// wxWebView
#ifdef USE_WEBVIEW_STARTPAGE
	html_startpage_ = wxWebView::New(
		this, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxWebViewBackendDefault, wxBORDER_NONE);
	html_startpage_->SetZoomType(App::platform() == App::MacOS ? wxWEBVIEW_ZOOM_TYPE_TEXT : wxWEBVIEW_ZOOM_TYPE_LAYOUT);

	// wxHtmlWindow
#else
	html_startpage_ = new wxHtmlWindow(this, -1, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_NEVER, "startpage");
#endif

	// Add to sizer
	GetSizer()->Add(html_startpage_, 1, wxEXPAND);

	// Bind events
#ifdef USE_WEBVIEW_STARTPAGE
	html_startpage_->Bind(wxEVT_WEBVIEW_NAVIGATING, &SStartPage::onHTMLLinkClicked, this);

	html_startpage_->Bind(
		wxEVT_WEBVIEW_ERROR, [&](wxWebViewEvent& e) { Log::error(S_FMT("wxWebView Error: %s", CHR(e.GetString()))); });

	if (App::platform() == App::Platform::Windows)
	{
		html_startpage_->Bind(wxEVT_WEBVIEW_LOADED, [&](wxWebViewEvent& e) { html_startpage_->Reload(); });
	}

	Bind(wxEVT_THREAD_WEBGET_COMPLETED, [&](wxThreadEvent& e) {
		latest_news_ = e.GetString();
		latest_news_.Trim();

		if (latest_news_ == "connect_failed" || latest_news_.empty())
			latest_news_ = "<center>Unable to load latest SLADE news</center>";

		load(false);
	});

#else
	html_startpage_->Bind(wxEVT_COMMAND_HTML_LINK_CLICKED, &SStartPage::onHTMLLinkClicked, this);
#endif

	// Get data used to build the page
	auto res_archive = App::archiveManager().programResourceArchive();
	if (res_archive)
	{
		entry_base_html_ =
			res_archive->entryAtPath(App::useWebView() ? "html/startpage.htm" : "html/startpage_basic.htm");

		entry_css_ = res_archive->entryAtPath(web_dark_theme ? "html/theme-dark.css" : "html/theme-light.css");

		entry_export_.push_back(res_archive->entryAtPath("html/base.css"));
		entry_export_.push_back(res_archive->entryAtPath("fonts/FiraSans-Regular.woff"));
		entry_export_.push_back(res_archive->entryAtPath("fonts/FiraSans-Italic.woff"));
		entry_export_.push_back(res_archive->entryAtPath("fonts/FiraSans-Medium.woff"));
		entry_export_.push_back(res_archive->entryAtPath("fonts/FiraSans-Bold.woff"));
		entry_export_.push_back(res_archive->entryAtPath("fonts/FiraSans-Heavy.woff"));
		entry_export_.push_back(res_archive->entryAtPath("logo_icon.png"));
		entry_export_.push_back(res_archive->entryAtPath("icons/entry_list/Rounded/archive.png"));
		entry_export_.push_back(res_archive->entryAtPath("icons/entry_list/Rounded/wad.png"));
		entry_export_.push_back(res_archive->entryAtPath("icons/entry_list/Rounded/zip.png"));
		entry_export_.push_back(res_archive->entryAtPath("icons/entry_list/Rounded/folder.png"));
		entry_export_.push_back(res_archive->entryAtPath("icons/general/open.png"));
		entry_export_.push_back(res_archive->entryAtPath("icons/general/newarchive.png"));
		entry_export_.push_back(res_archive->entryAtPath("icons/general/newzip.png"));
		entry_export_.push_back(res_archive->entryAtPath("icons/general/mapeditor.png"));
		entry_export_.push_back(res_archive->entryAtPath("icons/general/wiki.png"));

		// Load tips
		auto entry_tips = res_archive->entryAtPath("tips.txt");
		if (entry_tips)
		{
			Tokenizer tz;
			tz.openMem((const char*)entry_tips->getData(), entry_tips->getSize(), entry_tips->getName());
			while (!tz.atEnd() && tz.peekToken() != "")
				tips_.push_back(tz.getToken());
		}
	}
}