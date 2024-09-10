static LRESULT CALLBACK ase_wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch (msg) {

    case WM_DROPFILES:
      {
        ScopedLock lock(*dropped_files_mutex);
        HDROP hdrop = (HDROP)(wparam);
        int index, count, length;

        count = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
        for (index=0; index<count; ++index) {
          length = DragQueryFile(hdrop, index, NULL, 0);
          if (length > 0) {
            TCHAR* lpstr = new TCHAR[length+1];
            DragQueryFile(hdrop, index, lpstr, length+1);
            dropped_files->push_back(lpstr);
            delete[] lpstr;
          }
        }

        DragFinish(hdrop);
      }
      break;

  }
  return ::CallWindowProc(base_wnd_proc, hwnd, msg, wparam, lparam);
}