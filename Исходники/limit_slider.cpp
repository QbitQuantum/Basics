void LimitSliderDlg::internalShow( float minLimit, float maxLimit, float min, float max,
	unsigned int digits, LimitSlider* limitSlider )
{
	mDigits = digits;
	mLimitSlider = limitSlider;

	// If digits == 0, assume integer type
	if (digits == 0)
	{
		mMin.SetNumericType( controls::EditNumeric::ENT_INTEGER );
		mMax.SetNumericType( controls::EditNumeric::ENT_INTEGER );
	}
	else
	{
		mMin.SetNumericType( controls::EditNumeric::ENT_FLOAT );
		mMax.SetNumericType( controls::EditNumeric::ENT_FLOAT );
	}

	mMin.SetNumDecimals( digits );
	mMax.SetNumDecimals( digits );
	mMin.SetValue( min );
	mMax.SetValue( max );

	UpdateData( FALSE );

//	mMinLimit.SetWindowText( formatValue( minLimit ) );
//	mMaxLimit.SetWindowText( formatValue( maxLimit ) );

	mSlider.setRange( minLimit, maxLimit, (int)mDigits );
	mSlider.setThumbValues( min, max );

	CPoint cursor;
	GetCursorPos( &cursor );

	CRect client;
	GetWindowRect( &client );

	MoveWindow( &getBestRect( client.Size(), cursor ) );
	ShowWindow( SW_SHOW );
	SetActiveWindow();
	UpdateWindow();
}