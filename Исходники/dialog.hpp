	/// OKボタンが押された場合の処理
	///
	/// モーダル：EndDialog(IDOK)を呼び出します @n
	/// モードレス：Destroy()を呼び出します
	virtual bool onOK() {
		if (m_isModal) {
			endDialog(IDOK);
		}
		else {
			destroy();
		}
		return true;
	}