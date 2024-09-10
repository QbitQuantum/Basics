void IMsgs_Reset(HWND dialog)
{
	char string[32], version[5] = "0.00";
	char game[32] = "";
	char *version1 = scen.header.version;

	//these aren't gonna change, so load them here
	if (version1[0] == '\0')
		version1 = version;
	sprintf(string, "%s - %.2f", version1, scen.version2);

	switch (scen.game) {
	case AOE:
	    sprintf(game, "Age of Empires");
	    break;
	case ROR:
	    sprintf(game, "Rise of Rome");
	    break;
	case AOK:
	    sprintf(game, "Age of Kings");
	    break;
	case AOC:
	    sprintf(game, "The Conquerors");
	    break;
	case AOHD:
	    sprintf(game, "Age of Empires II: HD Edition");
	    break;
	case AOF:
	    sprintf(game, "The Forgotten");
	    break;
	case SWGB:
	    sprintf(game, "Star Wars Galactic Battlegrounds");
	    break;
	case SWGBCC:
	    sprintf(game, "Clone Campaigns");
	    break;
	default:
	    sprintf(game, "Unknown");
	    break;
	}

	SetDlgItemText(dialog, IDC_G_VER, string);
	SetDlgItemText(dialog, IDC_G_GAME, game);
	SetDlgItemText(dialog, IDC_G_TIMESTAMP, _ctime32(&scen.header.timestamp));
	SetDlgItemText(dialog, IDC_G_ONAME, scen.origname);
	SetDlgItemFloat(dialog, IDC_G_X, scen.editor_pos[0]);
	SetDlgItemFloat(dialog, IDC_G_Y, scen.editor_pos[1]);

	IM_msel = 0;
	SendDlgItemMessage(dialog, IDC_M_SEL, CB_SETCURSEL, 0, 0);
	IM_csel = 3;	//Bitmap = default
	SendDlgItemMessage(dialog, IDC_M_SELC, CB_SETCURSEL, 3, 0);
	LoadIM(dialog);
}