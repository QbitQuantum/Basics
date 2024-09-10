static int
scroller( HWND hwndDlg, WPARAM scroll_command )
{
  libspectrum_word base;
  SCROLLINFO si;

  si.cbSize = sizeof(si); 
  si.fMask = SIF_POS; 
  GetScrollInfo( GetDlgItem( hwndDlg, IDC_MEM_SB ), SB_CTL, &si );

  int value = si.nPos;
  
  /* in Windows we have to read the command and scroll the scrollbar manually */
  switch( LOWORD( scroll_command ) ) {
    case SB_BOTTOM:
      value = memorysb_max;
      break;
    case SB_TOP:
      value = memorysb_min;
      break;
    case SB_LINEDOWN:
      value += memorysb_step;
      break;
    case SB_LINEUP:
      value -= memorysb_step;
      break;
    case SB_PAGEUP:
      value -= memorysb_page_inc;
      break;
    case SB_PAGEDOWN:
      value += memorysb_page_inc;
      break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
      value = HIWORD( scroll_command );
      break;
    default:
      return 1;
  }
  if( value > memorysb_max ) value = memorysb_max;
  if( value < memorysb_min ) value = memorysb_min;

  /* Drop the low bits before displaying anything */
  base = value; base &= 0xfff0;

  /* set the new scrollbar position */
  memset( &si, 0, sizeof(si) );
  si.cbSize = sizeof(si); 
  si.fMask = SIF_POS; 
  si.nPos = base;
  SetScrollInfo( GetDlgItem( hwndDlg, IDC_MEM_SB ), SB_CTL, &si, TRUE );
  
  update_display( hwndDlg, base );
  
  return 0;
}