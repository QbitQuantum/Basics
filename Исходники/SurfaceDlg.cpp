void CSurfaceDlg::SetTexMods()
{
	char	sz[128];
	texdef_t *pt;
	brushprimit_texdef_t	*bpt;
	// local copy if a width=2 height=2 qtetxture_t is needed
	brushprimit_texdef_t	local_bp;
	int		i;

	if (!g_surfwin)
		return;

	m_bPatchMode = false;

	if (OnlyPatchesSelected())
	{
		pt = &g_qeglobals.d_texturewin.texdef;
		if (QE_SingleBrush())
    {
			//strcpy(g_patch_texdef.name, Patch_GetTextureName());
			g_patch_texdef.SetName(Patch_GetTextureName());
    }
		else
    {
			//strcpy(g_patch_texdef.name, pt->name);
			g_patch_texdef.SetName(pt->name);
    }
		g_patch_texdef.contents = pt->contents;
		g_patch_texdef.flags = pt->flags;
		g_patch_texdef.value = pt->value;
		pt = &g_patch_texdef;
		m_bPatchMode = true;
	}
	else
	{
		if (g_bNewFace && g_ptrSelectedFaces.GetSize() > 0)
		{
      face_t *selFace = reinterpret_cast<face_t*>(g_ptrSelectedFaces.GetAt(0));
			pt = &selFace->texdef;
			if (g_qeglobals.m_bBrushPrimitMode)
			{
				// compute a texture matrix related to the default matrix width=2 height=2
				ConvertTexMatWithQTexture( &selFace->brushprimit_texdef, selFace->d_texture, &local_bp, NULL );
				bpt = &local_bp;
			}
		}
		else
		{
			pt = &g_qeglobals.d_texturewin.texdef;
			if (g_qeglobals.m_bBrushPrimitMode)
			{
				bpt = &g_qeglobals.d_texturewin.brushprimit_texdef;
			}
		}
		// brush primitive mode : compute fake shift scale rot representation
		if (g_qeglobals.m_bBrushPrimitMode)
			TexMatToFakeTexCoords( bpt->coords, m_shift, &m_rotate, m_scale );
	}

	SendMessage (WM_SETREDRAW, 0, 0);

	::SetWindowText(GetDlgItem(IDC_TEXTURE)->GetSafeHwnd(), pt->name);

	if (m_bPatchMode)
		sprintf(sz, "%4.6f", pt->shift[0]);
	else
		if (g_qeglobals.m_bBrushPrimitMode)
			sprintf(sz, "%d", (int)m_shift[0]);
		else
			sprintf(sz, "%d", (int)pt->shift[0]);
	::SetWindowText(GetDlgItem(IDC_HSHIFT)->GetSafeHwnd(), sz);

	if (m_bPatchMode)
		sprintf(sz, "%4.6f", pt->shift[1]);
	else
		if (g_qeglobals.m_bBrushPrimitMode)
			sprintf(sz, "%d", (int)m_shift[1]);
		else
			sprintf(sz, "%d", (int)pt->shift[1]);
	::SetWindowText(GetDlgItem(IDC_VSHIFT)->GetSafeHwnd(), sz);

	sprintf(sz, m_bPatchMode ? "%4.6f" : "%4.6f", g_qeglobals.m_bBrushPrimitMode ? m_scale[0] : pt->scale[0]);
	::SetWindowText(GetDlgItem(IDC_HSCALE)->GetSafeHwnd(), sz);

	sprintf(sz, m_bPatchMode ? "%4.6f" : "%4.6f", g_qeglobals.m_bBrushPrimitMode ? m_scale[1] : pt->scale[1]);
	::SetWindowText(GetDlgItem(IDC_VSCALE)->GetSafeHwnd(), sz);

	//++timo compute BProtate as int ..
	sprintf(sz, "%d", g_qeglobals.m_bBrushPrimitMode ? (int)m_rotate : (int)pt->rotate);
	::SetWindowText(GetDlgItem(IDC_ROTATE)->GetSafeHwnd(), sz);

	sprintf(sz, "%d", (int)pt->value);
	::SetWindowText(GetDlgItem(IDC_VALUE)->GetSafeHwnd(), sz);

	for (i=0 ; i<32 ; i++)
		::SendMessage(GetDlgItem(g_checkboxes[i])->GetSafeHwnd(), BM_SETCHECK, !!(pt->flags&(1<<i)), 0 );
	for (i=0 ; i<32 ; i++)
		::SendMessage(GetDlgItem(g_checkboxes[32+i])->GetSafeHwnd(), BM_SETCHECK, !!(pt->contents&(1<<i)), 0 );

	SendMessage (WM_SETREDRAW, 1, 0);
	InvalidateRect (NULL, true);
}