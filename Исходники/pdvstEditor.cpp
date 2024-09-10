void pdvstEditor::idle()
{

       // JYG :: masquer la fenêtre GUI créée par hôte VST pour laisser puredata le faire
  //  SetWindowPos((HWND)systemWindow,HWND_TOPMOST,-300,-300,0,0,SWP_NOSIZE);  // déplacer la fenetre
  //  SetWindowPos((HWND)systemWindow,NULL,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_HIDEWINDOW); //masquer la fenêtre
  //  systemWindowHidden=true;
  // JYG
    if (((pdvst *)this->effect)->guiNameUpdated)
        if (editWindow)//&&!pdGuiWindow)
        {
            HWND tref=NULL;
            parms.ref = &tref;
            strcpy(parms.s,(char*)((pdvst *)this->effect)->guiName);
            parms.exact = false;
            EnumWindows(enumwnd,(LPARAM)&parms);
            pdGuiWindow = tref;

           // pdGuiWindow=FindWindow(NULL,"Pd_Gain(gui).pd  - C:/Program Files (x86)/Ableton/Live 8.0.4/Program/pdvst");
           //  pdGuiWindow=FindWindow(NULL,(char*)((pdvst *)this->effect)->guiName);
            if (pdGuiWindow)
            {
                if(SetParent(pdGuiWindow,(HWND)editWindow))//systemWindow))
                {
                    ((pdvst *)this->effect)->guiNameUpdated=0;
                    //Remove WS_POPUP style and add WS_CHILD style
                    DWORD style = GetWindowLong(pdGuiWindow,GWL_STYLE);
                    // style = style & ~(WS_POPUPWINDOW);
                    style = style & ~(WS_POPUP);
                    style = style & ~(WS_CHILD);    // WS_CHILD Crashes tcltk with reaper
                    style = style & ~(WS_SYSMENU);
                    style = style & ~(WS_BORDER);
                    style = style & ~(WS_HSCROLL);
                    style = style & ~(WS_VSCROLL);
                    style = style & ~(WS_SIZEBOX);
                    style = style & ~(WS_CAPTION);
                    SetWindowLong(pdGuiWindow,GWL_STYLE,style);
                    MoveWindow(pdGuiWindow, 0,0,((pdvst *)this->effect)->customGuiWidth,((pdvst *)this->effect)->customGuiHeight,TRUE);
                    systemWindowHidden=true;
                }
            }
        }
    AEffEditor::idle();
}