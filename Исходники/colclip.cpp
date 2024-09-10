void ColorClip::Init(HWND hWnd)
   {
   for (int i=0; i<NUM_COLORS; i++) {
      TSTR name;
      name.printf(GetString(IDS_RB_COLORNUM),i);
      cs[i] = GetIColorSwatch(GetDlgItem(hWnd,csIDs[i]),colors[i],name);
      cs[i]->SetUseAlpha(TRUE);
      cs[i]->SetAColor(colors[i]);
      }
   }