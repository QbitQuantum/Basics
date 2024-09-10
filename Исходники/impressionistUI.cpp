//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
    ImpressionistDoc *pDoc=whoami(o)->getDocument();
    /*pDoc->m_pUI->m_chooser = new Fl_File_Chooser(".", "*.png\t*.jpg", Fl_File_Chooser::CREATE, "Save");
    pDoc->m_pUI->m_chooser->show();
    while(pDoc->m_pUI->m_chooser->shown())
        { Fl::wait(); }*/
    
    const char* filename = pDoc->m_pUI->fileDialog( Fl_Native_File_Chooser::BROWSE_SAVE_FILE,
                                                    "PNG Image File (*.png)\t*.png\nJPEG Image File (*.jpg)\t*.jpg");
    if(filename) {
        std::string strFileName = (std::string)filename;
        std::string ext;
        int quality = 95;
        switch(pDoc->m_pUI->m_nativeChooser->filter_value()) {
            case 0:	ext = ".png"; break;
            case 1:	ext = ".jpg"; break;
        }
#ifdef WIN32
        char szExt[_MAX_EXT];
        _splitpath_s(strFileName.c_str(), NULL,0, NULL,0, NULL, 0, szExt,_MAX_EXT);
        if (_stricmp(szExt,".jpg") && _stricmp(szExt,".png")) {
            strFileName += ext;
        }
        else
            ext = szExt;
#endif

#ifdef __APPLE__
        if(!strcasecmp(ext.c_str(),".jpg")) {
#else
        if(!_strcmpi(ext.c_str(),".jpg")) {
#endif		
            Dialog2 x(0,0,0,0,"ok");
            quality = x.getValue();
        }
        pDoc->saveImage(strFileName.c_str(), ext.c_str(), quality);
    }
    /*const char *szFileName = pDoc->m_pUI->m_chooser->value();
    if (szFileName) {
        std::string strFileName = szFileName;
        std::string ext = (std::string)pDoc->m_pUI->m_chooser->filter();
        ext = ext.substr(1, ext.length() - 1);
        #ifdef WIN32
            char szExt[_MAX_EXT];
            _splitpath_s(strFileName.c_str(), NULL,0, NULL,0, NULL, 0, szExt,_MAX_EXT);
            // If user didn't type supported ext, add default one.
            if (_stricmp(szExt,".jpg") && _stricmp(szExt,".png")) {
                strFileName += ext;
            }
            else
                ext = szExt;
        #endif
        int quality = 95;
        if (!strcmp(ext.c_str(),".jpg")){
            Dialog2 x(0,0,0,0,"ok");
            quality = x.getValue();
        }
        pDoc->saveImage(strFileName.c_str(), ext.c_str(), quality);
    }*/
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
    whoami(o)->m_brushDialog->show();
}