static int exec(t_hydra_console *con, t_tokenline_parsed *p, int token_pos)
{
	int dev_func;
	mode_config_proto_t* proto = &con->mode->proto;
	int action, period, continuous, t;

	action = 0;
	period = 1000;
	continuous = FALSE;
	for (t = token_pos; p->tokens[t]; t++) {
		switch (p->tokens[t]) {
		case T_SHOW:
			t += show(con, p);
			break;
		case T_TYPEA:
			proto->dev_function = NFC_TYPEA;
			break;
		case T_VICINITY:
			proto->dev_function = NFC_VICINITY;
			break;
		case T_PERIOD:
			t += 2;
			memcpy(&period, p->buf + p->tokens[t], sizeof(int));
			break;
		case T_CONTINUOUS:
			continuous = TRUE;
			break;
		case T_SCAN:
		case T_SNIFF:
		case T_SNIFF_DBG:
		case T_EMUL_MIFARE:
		case T_EMUL_ISO14443A:
			action = p->tokens[t];
			break;
		}
	}

	if (action == T_SCAN) {
		dev_func = proto->dev_function;
		if( (dev_func == NFC_TYPEA) || (dev_func == NFC_VICINITY) ) {
			if (continuous) {
				cprintf(con, "Scanning %s ",
					proto->dev_function == NFC_TYPEA ? "MIFARE" : "Vicinity");
				cprintf(con, "with %dms period. Press user button to stop.\r\n", period);
				while (!USER_BUTTON) {
					scan(con);
					chThdSleepMilliseconds(period);
				}
			} else {
				scan(con);
			}

		} else {
			cprintf(con, "Please select MIFARE or Vicinity mode first.\r\n");
			return 0;
		}
	} else if (action == T_SNIFF) {
		hydranfc_sniff_14443A(con);
	} else if (action == T_SNIFF_DBG) {
		hydranfc_sniff_14443A_dbg(con);
	} else if (action == T_EMUL_MIFARE) {
		hydranfc_emul_mifare(con);
	} else if (action == T_EMUL_ISO14443A)
		hydranfc_emul_iso14443a(con);

	return t - token_pos;
}