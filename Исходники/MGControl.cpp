//---------------------------------------------------------------------------//
// Constructor
//
//---------------------------------------------------------------------------//
CMGControl::CMGControl(CMGControl *pParent, int iX, int iY, int iW, int iH)
{
  m_Parent  = NULL;
  m_Align   = MGALIGN_NONE;
  m_Enabled = true;
  m_Visible = true;
  m_Focused = false;
  m_AddRectAlign = true;
  m_Transparent  = true;
  m_Color = g_pMGDD->Skin()->Color(COL_BASE_BG);
  SetRect   (m_Border, 0,0,0,0);
  SetPos    (iX, iY);
  SetSize   (iW, iH);
  SetParent (pParent);
  m_FreeRect = m_Rect;
}