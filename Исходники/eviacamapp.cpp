bool EViacamApp::OnInit()
{     	
	// Call default behaviour
	if (!wxApp::OnInit()) return false;

/* ////@begin EViacamApp initialisation */
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif		
/* ////@end EViacamApp initialisation */

// Set up globals
#ifndef NDEBUG
	// Assume project runs from src/ 
	eviacam::SetDataDir(wxGetCwd() + _T("/../doc/"));
#else
	eviacam::SetDataDir(wxStandardPaths::Get().GetDataDir());
#endif
	
	// Initialize sockets support
	// Note: (Workaround for implementation limitation for wxWidgets up to 2.5.x) 
	// If you want to use sockets or derived classes such as wxFTP in a secondary 
	// thread, call wxSocketBase::Initialize() (undocumented) from the main thread 
	// before creating any sockets - in wxApp::OnInit for example. 
	// See http://wiki.wxwidgets.org/wiki.pl?WxSocket or 
	// http://www.litwindow.com/knowhow/knowhow.html for more details.
	wxSocketBase::Initialize();

	m_pController= new CViacamController();
	assert (m_pController);
	if (!m_pController->Initialize()) 
	{
		OnExit();
		return false;
	}
	else return true;
}