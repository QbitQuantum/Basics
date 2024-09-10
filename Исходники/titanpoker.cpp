void TitanPoker::close_login_ads() {

  //try to get root window
  std::vector<HWND> buf_vec = ScreenScraper::get_windows_by_type(WindowType::TitanRoot);
  if (buf_vec.size() != 1) { std::cout << "error, couldn't get titan root window" << std::endl; exit(0); }
  titan_root_window = buf_vec[0];

  //first popup
  HWND buf = GetLastActivePopup(titan_root_window);
  RECT rect = {0};
  GetWindowRect(buf, &rect);
  //press escape as long as we dont recognize titan-root-window through width and height
  while (rect.right - rect.left != 1016 && rect.bottom - rect.top != 738) {

    PostMessage(buf, WM_KEYDOWN, VK_ESCAPE, 0);
    PostMessage(buf, WM_KEYUP, VK_ESCAPE, 0);

    // needs to be in foreground in order to be an active popup
    SetForegroundWindow(titan_root_window);

    //if buf != titan-root-window, its an add
    buf = GetLastActivePopup(titan_root_window);
    GetWindowRect(buf, &rect);
    Sleep(200);
  }

  //imshow("test", ScreenScraper::window_to_mat(titan_root_window));
	//waitKey(0);

  //GetLastActivePopup(ScreenScraper::get_windows_by_type(WindowType::TitanRoot)[0]))
}