void Dialog_Config::ViewObjExec( int nViewType, Position* pPos, KeyInfo& tKeyInfo )
{
	int nKey = 0;

	if ( nViewType == INPUTBOX ) // Input
	{
		Input*	pInput = static_cast<Input*>(pPos);

		if ( pInput )
    		nKey = pInput->DataInput( tKeyInfo );
	}
	else
		nKey = (int)tKeyInfo;

    switch( nKey )
    {
        case KEY_MOUSE:
            MouseProc();
            break;
		case ' ':
        case KEY_ENTER:
        case 13:
		{
			if ( nViewType == CHECKBOX && _nCurNum < _vConfigOBJS.size() )
			{
				CheckRadioButton* pBox = static_cast<CheckRadioButton*>(_vConfigOBJS[_nCurNum]._pBox);
				pBox->SetCheck( !pBox->GetCheck() );
			}
		}
        case KEY_DOWN:
        case KEY_TAB:
            _nCurNum++;
            if ( _nCurNum > _vConfigOBJS.size() + 1 ) _nCurNum = 0;
            break;
        case KEY_UP:
            _nCurNum--;
            if ( _nCurNum < 0 ) _nCurNum = _vConfigOBJS.size() + 1;
            break;
        case KEY_ESC:
            _nCurNum = _vConfigOBJS.size() + 1; // Cancel Button
            break;
    }
}