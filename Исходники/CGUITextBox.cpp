bool CGUITextBox::HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	if(GetFocus() && wParam==m_Hotkey){
		OnHotkey();
		return true;
	}
if(GetFocus() && m_bSelectable)
	switch(uMsg){
		case WM_KEYDOWN:
			switch( wParam ){
				case VK_UP:
					PlaceCaret(m_Caretx, m_Carety-1);
					if( GetKeyState( VK_SHIFT ) >= 0 )
						SyncSelStart();
					break;
				case VK_DOWN:
					PlaceCaret(m_Caretx, m_Carety+1);
					if( GetKeyState( VK_SHIFT ) >= 0 )
						SyncSelStart();
					break;
				case VK_LEFT:
					if(m_Caretx==0 && m_Carety!=0)
						PlaceCaret(m_Text[m_Carety-1].length(), m_Carety-1);
					else
						PlaceCaret(m_Caretx-1, m_Carety);

					if( GetKeyState( VK_SHIFT ) >= 0 )
						SyncSelStart();
					break;
				case VK_RIGHT:
					if(m_Caretx==m_MaxCaretx && m_Carety!=m_MaxCarety)
						PlaceCaret(0, m_Carety+1);
					else
						PlaceCaret(m_Caretx+1, m_Carety);

					if( GetKeyState( VK_SHIFT ) >= 0 )
						SyncSelStart();
					break;
			default:
				break;
			}
			break;
        case WM_CHAR:
			switch( wParam ){
				case VK_BACK:
					if(m_Caretx==m_SelStartx && m_Carety==m_SelStarty)
						DeleteTextAtCaret();
					else
						DeleteSelectionText();
					break;
				case VK_RETURN:
					if(m_bEditable){
						if(m_Caretx==m_SelStartx && m_Carety==m_SelStarty)
						AddChar('\n');
						SyncSelStart();
					}
					break;
				case 24: // Ctrl-X Cut
                case VK_CANCEL: // Ctrl-C Copy
                case 22: // Ctrl-V Paste
                case 26:  // Ctrl Z
                case 2:   // Ctrl B
                case 14:  // Ctrl N
                case 19:  // Ctrl S
                case 4:   // Ctrl D
                case 6:   // Ctrl F
                case 7:   // Ctrl G
                case 10:  // Ctrl J
                case 11:  // Ctrl K
                case 12:  // Ctrl L
                case 17:  // Ctrl Q
                case 23:  // Ctrl W
                case 5:   // Ctrl E
                case 18:  // Ctrl R
                case 20:  // Ctrl T
                case 25:  // Ctrl Y
                case 21:  // Ctrl U
                case 9:   // Ctrl I
                case 15:  // Ctrl O
                case 16:  // Ctrl P
                case 27:  // Ctrl [
                case 29:  // Ctrl ]
                case 28:  // Ctrl \ 
					break;
				default:
					if(m_bEditable){
						AddChar((char)wParam);
						SyncSelStart();
					}
			}
			return true;
		default:
			return false;
	}

	return false;
}