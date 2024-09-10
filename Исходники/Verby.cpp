int VerbyPlugin::msg(int msgId, void* wParam, void* lParam)
{
	bool handled = false;
	switch (msgId)
	{		
	case MSG_INIT:
		init();
		handled = true;
		break;
	case MSG_GET_ID:
		getID((uint*) wParam);
		handled = true;
		break;
	case MSG_GET_NAME:
		getName((QString*) wParam);
		handled = true;
		break;
	case MSG_GET_LABELS:
		getLabels((QList<InputData>*) wParam);
		handled = true;
		break;
	case MSG_GET_RESULTS:
		getResults((QList<InputData>*) wParam, (QList<CatItem>*) lParam);
		handled = true;
		break;
	case MSG_LAUNCH_ITEM:
		launchItem((QList<InputData>*) wParam, (CatItem*) lParam);
		handled = true;
		break;
	case MSG_HAS_DIALOG:
		handled = true;
		break;
	case MSG_DO_DIALOG:
		doDialog((QWidget*) wParam, (QWidget**) lParam);
		break;
	case MSG_END_DIALOG:
		endDialog(wParam != 0);
		break;

	default:
		break;
	}

	return handled;
}