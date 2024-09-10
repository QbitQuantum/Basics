static int button_msg_proc (skin_item_t* item, int message, WPARAM wparam, LPARAM lparam)
{
	/* assert (item != NULL) */
	switch (message) {
	case SKIN_MSG_LBUTTONDOWN:	/* click-down event */
		//RAISE_EVENT ( SIE_LBUTTONDOWN, NULL ); /*item msg not defined*/
		/* default operation */
		skin_set_check_status ( item->hostskin, item->id, TRUE );	/*button down*/
		break;
	case SKIN_MSG_LBUTTONUP:	/* click-up event */
		//RAISE_EVENT ( SIE_LBUTTONUP, NULL ); /*item msg not defined*/
		/* default operation */
		skin_set_check_status ( item->hostskin, item->id, FALSE );	/*button up*/
		break;
	case SKIN_MSG_CLICK:		/* CLICK event */
		RAISE_EVENT ( SIE_BUTTON_CLICKED, NULL );
		/* default operation */
		skin_set_check_status ( item->hostskin, item->id, FALSE );	/* button up */
		break;
	case SKIN_MSG_MOUSEDRAG:
		//RAISE_EVENT ( SIE_MOUSEDRAG, NULL );
		/* default operation */
		if ( PtInRegion (&item->region, (int)wparam, (int)lparam) ){
        	/* if mouse moves in, click-down item */
            if (!skin_get_check_status(item->hostskin, item->id))
                skin_set_check_status ( item->hostskin, item->id, TRUE);	/*button down*/
		}
		else{
        	/* if mouse moves out, click-up item */
            if (skin_get_check_status(item->hostskin, item->id))
                skin_set_check_status ( item->hostskin, item->id, FALSE);	/*button up*/
		}
		break;
	case SKIN_MSG_SETFOCUS:
		RAISE_EVENT ( SIE_GAIN_FOCUS, NULL );
		break;
	case SKIN_MSG_KILLFOCUS:
		RAISE_EVENT ( SIE_LOST_FOCUS, NULL );
		break;
	}
	return 1;
}