LRESULT DisViewBox_OnPaint(disview_struct *win, WPARAM wParam, LPARAM lParam)
{
        HWND         hwnd = GetDlgItem(win->hwnd, IDC_DES_BOX);
        HDC          hdc;
        PAINTSTRUCT  ps;
        SIZE fontsize;
        TCHAR text[100];
        TCHAR txt[100];
        RECT rect;
        int lg;
        int ht;
        HDC mem_dc;
        HBITMAP mem_bmp;
        u32  nbligne;

        GetClientRect(hwnd, &rect);
        lg = rect.right - rect.left;
        ht = rect.bottom - rect.top;
        
        hdc = BeginPaint(hwnd, &ps);
        
        mem_dc = CreateCompatibleDC(hdc);
        mem_bmp = CreateCompatibleBitmap(hdc, lg, ht);
        SelectObject(mem_dc, mem_bmp);
        
        FillRect(mem_dc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
        
        SelectObject(mem_dc, GetStockObject(SYSTEM_FIXED_FONT));
        
        GetTextExtentPoint32(mem_dc, "0", 1, &fontsize);
        
        nbligne = ht/fontsize.cy;
        
        SetTextColor(mem_dc, RGB(0,0,0));
        
        if((win->mode==1) || ((win->mode==0) && (win->cpu->CPSR.bits.T == 0)))
        {
             u32 i;
             u32 adr;

             if (win->autoup)
                  win->curr_ligne = (win->cpu->instruct_adr >> 2) - (win->curr_ligne % nbligne) ;
             adr = win->curr_ligne*4;
        
             for(i = 0; i < nbligne; ++i)
             {
                  u32 ins = MMU_readWord(win->cpu->proc_ID, adr);
                  des_arm_instructions_set[INDEX(ins)](adr, ins, txt);
                  sprintf(text, "%04X:%04X  %08X  %s", (int)(adr>>16), (int)(adr&0xFFFF), (int)ins, txt);
                  DrawText(mem_dc, text, -1, &rect, DT_TOP | DT_LEFT | DT_NOPREFIX);
                  rect.top+=fontsize.cy;
                  adr += 4;
             }
             
             
        
             if(((win->cpu->instruct_adr&0x0FFFFFFF) >= win->curr_ligne<<2)&&((win->cpu->instruct_adr&0x0FFFFFFF) <= (win->curr_ligne+nbligne<<2)))
             {
                  HBRUSH brjaune = CreateSolidBrush(RGB(255, 255, 0));
                  SetBkColor(mem_dc, RGB(255, 255, 0));
                  rect.top = (((win->cpu->instruct_adr&0x0FFFFFFF)>>2) - win->curr_ligne)*fontsize.cy;
                  rect.bottom = rect.top + fontsize.cy;
                  FillRect(mem_dc, &rect, brjaune);
                  des_arm_instructions_set[INDEX(win->cpu->instruction)](win->cpu->instruct_adr, win->cpu->instruction, txt);
                  sprintf(text, "%04X:%04X  %08X  %s", (int)((win->cpu->instruct_adr&0x0FFFFFFF)>>16), (int)(win->cpu->instruct_adr&0xFFFF), (int)win->cpu->instruction, txt);
                  DrawText(mem_dc, text, -1, &rect, DT_TOP | DT_LEFT | DT_NOPREFIX);
                  DeleteObject(brjaune);
             }