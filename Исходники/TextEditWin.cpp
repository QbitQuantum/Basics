   void CorrectText(bool detect){

      dword len = win::SendMessage(hwnd_ctrl, WM_GETTEXTLENGTH, 0, 0);
      if(mask_password && !len)
         return;
#ifdef USE_RICHINK
      if(detect && len==dword(text.size()-1)){
         C_buffer<wchar> tmp;
         tmp.Resize(len+1);
         SendMessageW(hwnd_ctrl, WM_GETTEXT, len, (win::LPARAM)tmp.Begin());
         if(!MemCmp(tmp.Begin(), text.begin(), len*sizeof(wchar)))
            return;
         MemCpy(text.begin(), tmp.Begin(), len*sizeof(wchar));
      }else{
         text.resize(len+1);
         win::SendMessage(hwnd_ctrl, WM_GETTEXT, len, (win::LPARAM)text.begin());
      }
      text[len] = 0;
#else
      if(detect && len==dword(text.size()-1)){
         C_buffer<wchar> tmp;
         tmp.Resize(len+1);
         SendMessageW(hwnd_ctrl, WM_GETTEXT, len+1, (win::LPARAM)tmp.Begin());
         if(!MemCmp(tmp.Begin(), text.begin(), (len+1)*sizeof(wchar)))
            return;
         MemCpy(text.begin(), tmp.Begin(), (len+1)*sizeof(wchar));
      }else{
         text.resize(len+1);
         win::SendMessage(hwnd_ctrl, WM_GETTEXT, len+1, (win::LPARAM)text.begin());
         text.begin()[len] = 0;
      }
#endif
      mask_password = false;
      text_dirty = true;
      SetSelFromWin();
      ResetCursor();
   }