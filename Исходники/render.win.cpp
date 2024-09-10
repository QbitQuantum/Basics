// печатать текст
// NOTE: пока сделаю через GDI - это, канечно, заплатка, но
// городить менеджер ресурсов, текстуры, шрифт - много работы и я не успею
void RenderWindow::draw(char* text, int x, int y) {
  static HFONT Font = 0;

  if(Font == 0) {
    HDC hdc;
    long lfHeight;
    hdc = GetDC(NULL);
    lfHeight = -MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 72);
    ReleaseDC(NULL, hdc);
    Font = CreateFont(lfHeight, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, L"Times New Roman");
    SelectObject(reinterpret_cast<HDC>(_dc), g_hfFont);
    SetTextColor(reinterpret_cast<HDC>(_dc), RGB(255, 255, 255));
		SetBkMode(reinterpret_cast<HDC>(_dc), TRANSPARENT);
  }

  TextOutA(reinterpret_cast<HDC>(_dc), x, y, text, strlen(text));
}