	LRESULT hookMouseLl(int nCode, WPARAM wParam, LPARAM lParam) {
		bool callNext = true;

		if(nCode >= 0) {
			MSLLHOOKSTRUCT* msll = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);

			// --------------------------------------------------------------------------
			/**
				押下時のチャタリング

					--u---	d-----------------
					--u---	dud---------------
					--u---	dudud-------------

				離し時のチャタリング

					--d--	u-----------------
					--d--	udu---------------
					--d--	ududu-------------

				ドラッグ時のチャタリング (用語間違い？　接触や通信不良のこと)

					d-------dud-------
			 */
			//---------------------------------------------------------------------------
			switch(wParam) {
			case WM_LBUTTONDOWN:
				{
					Time currentTime = getCurrentTime();
					//	チャタリングが発生しているか？
					if(isChattering(prevLeftUpTime, currentTime) || isChattering(prevLeftDownTime, currentTime)) {
						//	してるっぽいので何もしない
						callNext = false;
					}
					prevLeftDownTime = currentTime;
					break;
				}
			case WM_LBUTTONUP:
				{
					Time currentTime = getCurrentTime();
					//	チャタリングが発生しているか？
					if(isChattering(prevLeftDownTime, currentTime) || isChattering(prevLeftUpTime, currentTime)) {
						//	してるっぽいので何もしない
						callNext = false;
					}
					prevLeftUpTime = currentTime;
					break;
				}

			case WM_RBUTTONDOWN:
				{
					Time currentTime = getCurrentTime();
					//	チャタリングが発生しているか？
					if(isChattering(prevRightUpTime, currentTime)) {
						//	してるっぽいので何もしない
						callNext = false;
					}
					prevRightDownTime = currentTime;
					break;
				}
				break;
			case WM_RBUTTONUP:
				{
					Time currentTime = getCurrentTime();
					//	チャタリングが発生しているか？
					if(isChattering(prevRightDownTime, currentTime)) {
						//	してるっぽいので何もしない
						callNext = false;
					}
					prevRightUpTime = currentTime;
					break;
				}
				break;

			case WM_MOUSEMOVE:
			case WM_MOUSEWHEEL:
			default:
				break;
			}
		}

		if(callNext) {
			return CallNextHookEx(hook, nCode, wParam, lParam);
		} else {
			return 1;
		}
	}