/*============================================
 *  BasicWindow::registWC__()
 *  WNDCLASS登録 & WNDCLASS名を返す
 *  同じ内容のWNDCLASSの二重登録を阻止する
 *==========================================*/
std::wstring urania::BasicWindow::registWC__
(const urania::BasicWindow::WC_& wc)
{
  std::vector<WC_>::iterator it = std::find(vwc_S.begin(), vwc_S.end(), wc);
  if (it == vwc_S.end())
  {
    ////////////////////////////////////////////////////////
    // WNDCLASSの登録とvectorへの追加
    ////////////////////////////////////////////////////////

    // クラス名をWC_に設定
    WC_ wc2 = wc;
    //std::wostringstream tmp;
    std::basic_ostringstream<wchar_t> tmp;
    tmp << vwc_S.size();

    wc2.wcname_ = std::wstring(L"GPWNDCLASS") + tmp.str();

    // WNDCLASS Structure
    WNDCLASS wndcls =
    {
      CS_HREDRAW | CS_VREDRAW,
      wc2.proc_,
      0,
      sizeof(Window*),
      getHI__(),
      NULL,
      NULL,
      NULL,
      nullptr,
      wc2.wcname_.c_str()
    };

    // Icon の設定
    if (wc2.icon_id_ != DEFAULT_RC)
      wndcls.hIcon = LoadIcon(getHI__(), MAKEINTRESOURCE(wc2.icon_id_));
    else
      wndcls.hIcon = LoadIcon(0, IDI_APPLICATION);

    // Cursor の設定
    if (wc2.cursor_id_ != DEFAULT_RC)
      wndcls.hCursor = LoadCursor(getHI__(), MAKEINTRESOURCE(wc2.cursor_id_));
    else
      wndcls.hCursor = LoadCursor(0, IDC_ARROW);


    // 背景色の設定
    switch (wc2.bkcolor_)
    {
    case BG_WHITE:
      wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
      break;

    case BG_BLACK:
      wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
      break;

    case BG_GRAY:
      wndcls.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
      break;

    case BG_LTGRAY:
      wndcls.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
      break;

    case BG_DKGRAY:
      wndcls.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
      break;

    case BG_APPWORKSPACE:
      wndcls.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
      break;

    case BG_BKWINDOW:
      wndcls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      break;

    default:
      wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
      break;
    }

    // 実際に登録
    ::RegisterClass(&wndcls);

    vwc_S.push_back(wc2);
    return wc2.wcname_;
  }
  else
    return it->wcname_; // WNDCLASS名を返す
}