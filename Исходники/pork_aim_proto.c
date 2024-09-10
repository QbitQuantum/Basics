void parse_ccom(char *cmd, struct chatroom *room, struct pork_acct *acct, int priv) {
	struct aim_chat *ccon = room->data;
	struct aim_priv *a_priv = acct->data;
	dlist_t *temp;
	char sn[MAXSNLEN+1];
	char msg[MAXSNLEN+1024];
	char *pmsg = msg;

	cmd[strcspn(cmd,"/")] = '\0';
	if(!strncasecmp(cmd, "op ", 3) && (priv >= FULLOPS)) {
		cmd += 3;
		if (!aim_snvalid(cmd))
			return;
		partial_nick(cmd, sn, room);
		if (check_if_op(sn, room))
			return;
		ccon->oparray = dlist_add_tail(ccon->oparray, xstrdup(sn));
		if (ccon->chatsends > 1) {
			sprintf(msg, "%s has been opped.", sn);
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
		}
	} else if(!strncasecmp(cmd, "deop ", 5) && (priv >= FULLOPS)) {
		cmd += 5;
		if (!aim_snvalid(cmd))
			return;
		partial_nick(cmd, sn, room);
		if (!check_if_op(sn, room))
			return;
		if (temp = dlist_find(ccon->oparray, sn, (void*)strcmp)) {
			free(temp->data);
			ccon->oparray = dlist_remove(ccon->oparray, temp);
			if (ccon->chatsends > 1) {
				sprintf(msg, "%s has been deopped.", sn);
				aim_chat_send_im(&a_priv->aim_session, ccon->conn,
					0, pmsg, strlen(msg), "us-ascii", "en");
			}
		}
	} else if(!strncasecmp(cmd, "defullop ", 7) && (priv >= DOWNERS)) {
		cmd += 9;
		if (!aim_snvalid(cmd))
			return;
		partial_nick(cmd, sn, room);
		if (temp = dlist_find(ccon->fullops, sn, (void*)strcmp)) {
			free(temp->data);
			ccon->fullops = dlist_remove(ccon->fullops, temp);
			if (ccon->chatsends > 1) {
				sprintf(msg, "%s has been defullopped.", sn);
				aim_chat_send_im(&a_priv->aim_session, ccon->conn,
					0, pmsg, strlen(msg), "us-ascii", "en");
			}
		}
	} else if(!strncasecmp(cmd, "fullop ", 7) && (priv >= FULLOPS)) {
		cmd += 7;
		if (!aim_snvalid(cmd))
			return;
		partial_nick(cmd, sn, room);
		if (check_if_fullop(sn, room))
			return;
		ccon->fullops = dlist_add_tail(ccon->fullops, xstrdup(sn));
		if (ccon->chatsends > 1) {
			sprintf(msg, "%s has been fullopped.", sn);
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
		}
	} else if(!strncasecmp(cmd, "halfop ", 7) && (priv > HALFOPS)) {
		cmd += 7;
		if (!aim_snvalid(cmd))
			return;
		partial_nick(cmd, sn, room);
		if (check_if_halfop(sn, room))
			return;
		ccon->halfops = dlist_add_tail(ccon->halfops, xstrdup(sn));
		if (ccon->chatsends > 1) {
			sprintf(msg, "%s has been halfopped.", sn);
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
		}
	} else if(!strncasecmp(cmd, "dehalfop ", 9) && (priv > HALFOPS)) {
		cmd += 9;
		if (!aim_snvalid(cmd))
			return;
		partial_nick(cmd, sn, room);
		if (!check_if_halfop(sn, room))
			return;
		if (temp = dlist_find(ccon->halfops, sn, (void*)strcmp)) {
			free(temp->data);
			ccon->halfops = dlist_remove(ccon->halfops, temp);
			if (ccon->chatsends > 1) {
				sprintf(msg, "%s has been dehalfopped.", sn);
				aim_chat_send_im(&a_priv->aim_session, ccon->conn,
					0, pmsg, strlen(msg), "us-ascii", "en");
			}
		}
	} else if(!strncasecmp(cmd, "kick ", 5)) {
		cmd += 5;
		if (!aim_snvalid(cmd))
			return;
		partial_nick(cmd, sn, room);
		if (check_if_imm(sn, room))
			return;
		if (ccon->chatsends > 1) {
			snprintf(msg, MAXSNLEN+127, "kicking %s.", sn);
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
		}
		if ((temp = dlist_find(ccon->banlist, sn, (void*)strcmp)) != NULL) {
			free(temp->data);
			ccon->banlist = dlist_remove(ccon->banlist, temp);
		}
		aim_chat_ban(&a_priv->aim_session, ccon->conn, sn);
		aim_chat_unban(&a_priv->aim_session, ccon->conn, sn);
	} else if(!strncasecmp(cmd, "ban ", 4) && (priv > HALFOPS)) {
		cmd += 4;
		if (!aim_snvalid(cmd))
			return;
		partial_nick(cmd, sn, room);
		if (check_if_imm(sn, room))
			return;
		if (ccon->chatsends > 1) {
			snprintf(msg, MAXSNLEN+127, "banning %s.", sn);
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
		}
		if (!dlist_find(ccon->banlist, sn, (void*)strcmp))
			ccon->banlist = dlist_add_tail(ccon->banlist, xstrdup(sn));
		aim_chat_ban(&a_priv->aim_session, ccon->conn, sn);
	} else if(!strncasecmp(cmd, "unban ", 6) && (priv > HALFOPS)) {
		cmd += 6;
		if (!aim_snvalid(cmd))
			return;
		if (ccon->chatsends > 1) {
			snprintf(msg, MAXSNLEN+127, "unbanning %s.", cmd);
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
		}
		if ((temp = dlist_find(ccon->banlist, cmd, (void*)strcmp)) != NULL) {
			free(temp->data);
			ccon->banlist = dlist_remove(ccon->banlist, temp);
		}
		aim_chat_unban(&a_priv->aim_session, ccon->conn, cmd);
	} else if(!strncasecmp(cmd, "pause ", 6) && (priv >= FULLOPS)) {
		cmd += 6;
		banpause = atoi(cmd);
		if (banpause < 0)
			banpause = 0;
		sprintf(msg, "autoban pause set to %g microseconds.", banpause);
		if (ccon->chatsends > 1)
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
	} else if(!strncasecmp(cmd, "help", 4) && ccon->chatsends) {
		char commands[MAXMSGLEN+1];
		strcpy(commands, "commands are: !status, !kick, !imm");
		if (priv > HALFOPS)
			strcat(commands,", !unimm, !ban, !unban, !ab, !unab, !aw, !unaw, !halfop, !dehalfop, !bj");
		if (priv > OPS)
			strcat(commands,", !ak, !unak, !op, !deop, !fullop, !save, !load");
		if (priv > FULLOPS)
			strcat(commands,", !defullop");
		strcat(commands, ".");
		aim_chat_send_im(&a_priv->aim_session, ccon->conn,
			0, commands, strlen(commands), "us-ascii", "en");
	} else if(!strncasecmp(cmd, "imm ", 4)) {
		cmd += 4;
		if (!aim_snvalid(cmd))
			return;
		partial_nick(cmd, sn, room);
		if (check_if_imm(sn, room))
			return;
		ccon->immlist = dlist_add_tail(ccon->immlist, xstrdup(sn));
		if (ccon->chatsends > 1) {
			sprintf(msg, "%s has been immed.", sn);
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
		}
	} else if(!strncasecmp(cmd, "unimm ", 6) && (priv > HALFOPS)) {
		cmd += 6;
		if (!aim_snvalid(cmd))
			return;
		partial_nick(cmd, sn, room);
		if (!check_if_imm(sn, room))
			return;
		if (temp = dlist_find(ccon->immlist, sn, (void*)strcmp)) {
			free(temp->data);
			ccon->immlist = dlist_remove(ccon->immlist, temp);
			if (ccon->chatsends > 1) {
				sprintf(msg, "%s has been unimmed.", sn);
				aim_chat_send_im(&a_priv->aim_session, ccon->conn,
					0, pmsg, strlen(msg), "us-ascii", "en");
			}
		}
	} else if(!strncasecmp(cmd, "ak ", 3) && (priv > OPS)) {
		cmd += 3;
		if (!aim_snvalid(cmd))
			return;
		if (check_if_ak(cmd, room))
			return;
		normalize(sn, cmd, strlen(cmd) + 1);
		ccon->akarray = dlist_add_tail(ccon->akarray, xstrdup(cmd));
		if (ccon->chatsends > 1) {
			sprintf(msg, "%s has been autokicked.", sn);
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
		}
		check_akusers_in_room(room);
	} else if(!strncasecmp(cmd, "ab ", 3) && (priv > HALFOPS)) {
		cmd += 3;
		if (!aim_snvalid(cmd))
			return;
		if (check_if_ab(cmd, room))
			return;
		normalize(sn, cmd, strlen(cmd) + 1);
		ccon->abarray = dlist_add_tail(ccon->abarray, xstrdup(cmd));
		if (ccon->chatsends > 1) {
			sprintf(msg, "%s has been autobanned.", sn);
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
		}
		check_abusers_in_room(room);
	} else if(!strncasecmp(cmd, "aw ", 3) && (priv > HALFOPS)) {
		cmd += 3;
		if (check_if_aw(cmd, room))
			return;
		ccon->awarray = dlist_add_tail(ccon->awarray, xstrdup(cmd));
		if (ccon->chatsends > 1) {
			sprintf(msg, "%s has been autoworded.", cmd);
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
		}
	} else if(!strncasecmp(cmd, "unak ", 5) && (priv > OPS)) {
		cmd += 5;
		if (!aim_snvalid(cmd))
			return;
		if (!check_if_ak(cmd, room))
			return;
		if (temp = dlist_find(ccon->akarray, cmd, (void*)strcmp)) {
			free(temp->data);
			ccon->akarray = dlist_remove(ccon->akarray, temp);
			if (0) { //ccon->chatsends > 1) {
				sprintf(msg, "%s has been unautokicked.", cmd);
				aim_chat_send_im(&a_priv->aim_session, ccon->conn,
					0, pmsg, strlen(msg), "us-ascii", "en");
			}
		}
	} else if(!strncasecmp(cmd, "unab ", 5) && (priv > HALFOPS)) {
		cmd += 5;
		if (!aim_snvalid(cmd))
			return;
		if (!check_if_ab(cmd, room))
			return;
		if (temp = dlist_find(ccon->abarray, cmd, (void*)strcmp)) {
			free(temp->data);
			ccon->abarray = dlist_remove(ccon->abarray, temp);
			if (0) { //ccon->chatsends > 1) {
				sprintf(msg, "%s has been unautobanned.", cmd);
				aim_chat_send_im(&a_priv->aim_session, ccon->conn,
					0, pmsg, strlen(msg), "us-ascii", "en");
			}
		}
	} else if(!strncasecmp(cmd, "unaw ", 5) && (priv > HALFOPS)) {
		cmd += 5;
		if (!check_if_aw(cmd, room))
			return;
		if (temp = dlist_find(ccon->awarray, cmd, (void*)strcmp)) {
			free(temp->data);
			ccon->awarray = dlist_remove(ccon->awarray, temp);
			if (ccon->chatsends > 1) {
				snprintf(msg, 1024, "%s has been unautoworded.", cmd);
				aim_chat_send_im(&a_priv->aim_session, ccon->conn,
					0, pmsg, strlen(msg), "us-ascii", "en");
			}
		}
	} else if(!strncasecmp(cmd, "status ", 7) && ccon->chatsends) {
		strcpy(msg, "");
		cmd += 7;
		if (!aim_snvalid(cmd))
			return;
		partial_nick(cmd, sn, room);
		if (check_if_fullop(sn, room)) {
			sprintf(msg, "%s is a full op.", sn);
		} else if (check_if_op(sn, room)) {
			sprintf(msg, "%s is an op.", sn);
		} else if (check_if_halfop(sn, room)) {
			sprintf(msg, "%s is a half op", sn);
			if (check_if_imm(sn, room))
				strcat(msg, " and immune");
			strcat(msg, ".");
		} else if (check_if_imm(sn, room)) {
			sprintf(msg, "%s is immune.", sn);
		}
		if (strlen(msg))
			aim_chat_send_im(&a_priv->aim_session, ccon->conn,
				0, pmsg, strlen(msg), "us-ascii", "en");
	} else if(!strncasecmp(cmd, "chatsends ", 10) && (priv >= FULLOPS)) {
		int chatsends;
		cmd += 10;
		chatsends = atoi(cmd);
		if ((chatsends >= 0) && (chatsends <= 2)) {
			ccon->chatsends = chatsends;
			if (ccon->chatsends > 1) {
				sprintf(msg, "chatsends now set to %d.", ccon->chatsends);
				aim_chat_send_im(&a_priv->aim_session, ccon->conn, 0, msg, strlen(msg), "us-ascii", "en");
			}
		}
	} else if(!strncasecmp(cmd, "save", 4) && (priv >= FULLOPS)) {
		if (!write_room(ccon)) {
			screen_err_msg("unable to save config for room %s.\n", ccon->title);
		}
	} else if(!strncasecmp(cmd, "load ", 5) && (priv >= FULLOPS)) {
		if (!read_room(ccon, &cmd[5])) {
			screen_err_msg("unable to load config for room %s.\n", &cmd[5]);
		}
	} else if(!strncasecmp(cmd, "bj", 2) && (priv > HALFOPS)) {
		ccon->banjoin = !ccon->banjoin;
		if (ccon->chatsends > 1) {
			sprintf(msg, "banjoin: %s.", ccon->banjoin?"on":"off");
			aim_chat_send_im(&a_priv->aim_session, ccon->conn, 0, msg, strlen(msg), "us-ascii", "en");
		}
	}
}