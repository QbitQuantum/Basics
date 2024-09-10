void *PackDialogU(
    DWORD style,
    DWORD exstyle,
    int x, int y,
    int cx, int cy,
    WCHAR const *titlestr,
    int titleid,
    LOGFONTW *fnt,
    int itemcount,
    struct DLG_Item *items
    )
    {
    size_t dmenu_size;
    size_t dclass_size;
    size_t dtitle_size;
    size_t dfont_size;
    int title_id_len;
    size_t title_str_len;
    size_t title_space_len;
    WCHAR *titlespace=L" - ";
    WCHAR *dmenu;
    WCHAR *dclass;
    WCHAR *dtitle;
    WCHAR *dfont;
    size_t dlg_size;
    size_t items_size;
    DLGTEMPLATEEX *dlg;
    DLGTEMPLATEEXFONT *dfparam;
    size_t item_offset;
    char *buf;
    int i;

    /* Get size of strings */
    dmenu_size=sizeof(WCHAR);
    dclass_size=sizeof(WCHAR);
    /* Calculate size of title */
    dtitle_size=1;
    title_id_len=LoadStringU(NULL, titleid, NULL, 0, 0);
    dtitle_size+=title_id_len;
    title_str_len= titlestr ? lstrlenW(titlestr) : 0;
    dtitle_size+=title_str_len;
    title_space_len=lstrlenW(titlespace);
    if(title_id_len>0 && title_str_len>0)
        dtitle_size+=title_space_len;
    dtitle_size*=sizeof(WCHAR);
    /* Get size of face name string, if font present */
    if(fnt!=NULL)
        dfont_size=StringBytesU(fnt->lfFaceName);
    else
        dfont_size=0;

    /* Calculate size of template */
    dlg_size=sizeof(*dlg)+dmenu_size+dclass_size+dtitle_size;
    /* Add font parameters size, if present */
    if(dfont_size!=0)
        dlg_size+=sizeof(DLGTEMPLATEEXFONT)+dfont_size;

    /* Adjust to DWORD boundary */
    dlg_size=AdjustToDWORD(dlg_size);

    /* Calculate dialog items size */
    items_size=0;
    for(i=0; i<itemcount; i++)
        items_size+=DlgMeasureItemU(items+i);

    /* Allocate buffer for template */
    buf=malloc(dlg_size+items_size+sizeof(DWORD));
    if(buf==NULL)
        return NULL;

    /* Set pointers in buffer */
    dlg=(DLGTEMPLATEEX *)AdjustToDWORD((size_t)buf);
    dmenu=(WCHAR *)((char *)(dlg)+sizeof(DLGTEMPLATEEX));
    dclass=(WCHAR *)((char *)(dmenu)+dmenu_size);
    dtitle=(WCHAR *)((char *)(dclass)+dclass_size);

    /* Fill template with data */
    dlg->dlgVer=1; 
    dlg->signature=0xFFFF; 
    dlg->helpID=0; 
    dlg->exStyle=exstyle; 
    dlg->style=style; 
    dlg->cDlgItems=itemcount; 
    dlg->x=x;
    dlg->y=y; 
    dlg->cx=cx; 
    dlg->cy=cy;
    
    *dmenu=0;
    *dclass=0;
    if(title_str_len>0)
        {
        strcpyU(dtitle, titlestr);
        if(title_str_len>0 && title_id_len>0)
            {
            strcpyU(dtitle+title_str_len, titlespace);
            title_str_len+=title_space_len;
            }
        }
    ResLoadStringU(titleid, dtitle+title_str_len, title_id_len+1);

    /* Set font parameters */
    if(fnt!=NULL)
        {
        HDC dc;
        int pointsize;

        dc=GetDC(NULL);
        pointsize=-MulDiv(fnt->lfHeight, 72, GetDeviceCaps(dc, LOGPIXELSY));
        ReleaseDC(NULL, dc);

        dlg->style|=DS_SETFONT;

        dfparam=(DLGTEMPLATEEXFONT *)((char *)(dtitle)+dtitle_size);
        dfont=(WCHAR *)((char *)(dfparam)+sizeof(*dfparam));

        dfparam->pointsize=pointsize;
        dfparam->weight=(WORD)fnt->lfWeight;
        dfparam->bItalic=fnt->lfItalic;
        dfparam->charset=fnt->lfCharSet;
        StringCopyU(dfont, fnt->lfFaceName);
        }
    else
        dlg->style&=~DS_SETFONT;

    /* Fill items data */
    item_offset=dlg_size;
    for(i=0; i<itemcount; i++)
        {
        item_offset+=DlgPackItemU((char *)(dlg)+item_offset, items+i);
        if(items[i].Control->PreInit!=NULL)
            items[i].Control->PreInit();
        }

    return buf;
    }