	PlatformWinAPI::PlatformWinAPI (const WinAPI::FakeQWidgetWinAPI_ptr& widget, const ICoreProxy_ptr& proxy, QObject* parent)
	: PlatformLayer (proxy, parent)
	, HPowerSchemeNotify_ (new HPOWERNOTIFY, aHPowerNotifyDeleter)
	, HPowerSourceNotify_ (new HPOWERNOTIFY, aHPowerNotifyDeleter)
	, HBatteryPowerNotify_ (new HPOWERNOTIFY, aHPowerNotifyDeleter)
	, FakeWidget_ (widget)
	{
		HWND h_wnd = reinterpret_cast<HWND> (FakeWidget_->winId ());

		*HPowerSchemeNotify_ = RegisterPowerSettingNotification (h_wnd,
			&GUID_POWERSCHEME_PERSONALITY, DEVICE_NOTIFY_WINDOW_HANDLE);

		Q_ASSERT (*HPowerSchemeNotify_);

		*HPowerSourceNotify_ = RegisterPowerSettingNotification (h_wnd,
			&GUID_ACDC_POWER_SOURCE, DEVICE_NOTIFY_WINDOW_HANDLE);

		Q_ASSERT (*HPowerSourceNotify_);

		*HBatteryPowerNotify_ = RegisterPowerSettingNotification (h_wnd,
			&GUID_BATTERY_PERCENTAGE_REMAINING,	DEVICE_NOTIFY_WINDOW_HANDLE);

		Q_ASSERT (*HBatteryPowerNotify_);

		connect (FakeWidget_.get (),
				SIGNAL (schemeChanged (QString)),
				this,
				SLOT (handleSchemeChanged (QString)));
		connect (FakeWidget_.get (),
				SIGNAL (powerSourceChanged (QString)),
				this,
				SLOT (handlePowerSourceChanged (QString)));
	}