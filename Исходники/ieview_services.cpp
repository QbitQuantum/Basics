INT_PTR HandleIEWindow(WPARAM, LPARAM lParam)
{
	IEVIEWWINDOW *window = (IEVIEWWINDOW *)lParam;
	Options::init();
	if (window->iType == IEW_CREATE) {
		HTMLBuilder *builder = NULL;
		switch (window->dwMode) {
		case IEWM_MUCC:
			builder = new MUCCHTMLBuilder();
			break;
		case IEWM_CHAT:
			builder = new ChatHTMLBuilder();
			break;
		case IEWM_TABSRMM:
			builder = new TabSRMMHTMLBuilder();
			break;
		case IEWM_SCRIVER:
			builder = new ScriverHTMLBuilder();
			break;
		case IEWM_HISTORY:
			builder = new HistoryHTMLBuilder();
			break;
		case IEWM_BROWSER:
			builder = NULL;
			break;
		default:
			builder = new ScriverHTMLBuilder();
			break;
		}
		IEView *view = new IEView(window->parent, builder, window->x, window->y, window->cx, window->cy);
		window->hwnd = view->getHWND();
	}
	else if (window->iType == IEW_SETPOS) {
		IEView *view = IEView::get(window->hwnd);
		if (view != NULL)
			view->setWindowPos(window->x, window->y, window->cx, window->cy);
	}
	else if (window->iType == IEW_SCROLLBOTTOM) {
		IEView *view = IEView::get(window->hwnd);
		if (view != NULL)
			view->scrollToBottom();
	}
	else if (window->iType == IEW_DESTROY) {
		IEView *view = IEView::get(window->hwnd);
		if (view != NULL)
			delete view;
	}
	return 0;
}