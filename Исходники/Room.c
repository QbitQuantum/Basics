int load_RoomData_version0(File *f, Room *r, int flags) {
char buf[MAX_LONGLINE];
StringList *sl;
int i;

/* name */
	if (Fgets(f, buf, MAX_LINE) == NULL)
		goto err_load_room;

	cstrip_line(buf);
	Free(r->name);
	r->name = cstrdup(buf);

	if (flags & LOAD_ROOM_DATA) {
/* generation/creation date */
		if (Fgets(f, buf, MAX_LINE) == NULL)
			goto err_load_room;
		cstrip_line(buf);
		r->generation = cstrtoul(buf, 10);

/* flags */
		if (Fgets(f, buf, MAX_LINE) == NULL)
			goto err_load_room;
		cstrip_line(buf);
		r->flags = (unsigned int)cstrtoul(buf, 16);
		r->flags &= ROOM_ALL;		/* reset non-existant flags */

/* roominfo_changed */
		if (Fgets(f, buf, MAX_LINE) == NULL)
			goto err_load_room;
		cstrip_line(buf);
		r->roominfo_changed = (unsigned int)cstrtoul(buf, 10);
	} else
		LOAD_ROOM_SKIPLINES(3);

/* info */
	destroy_StringIO(r->info);
	r->info = NULL;

	if (PARAM_HAVE_RESIDENT_INFO || (flags & LOAD_ROOM_INFO)) {
		while(Fgets(f, buf, MAX_LINE) != NULL) {
			if (!*buf)
				break;

			if (r->info == NULL && (r->info = new_StringIO()) == NULL)
				continue;

			put_StringIO(r->info, buf);
			write_StringIO(r->info, "\n", 1);
		}
	} else
		LOAD_ROOM_SKIPLIST;

/* room aides */
	listdestroy_StringList(r->room_aides);
	r->room_aides = NULL;

	if (flags & LOAD_ROOM_AIDES) {
		while(Fgets(f, buf, MAX_LINE) != NULL) {
			cstrip_line(buf);
			if (!*buf)
				break;

			if (user_exists(buf) && (sl = new_StringList(buf)) != NULL)
				r->room_aides = add_StringList(&r->room_aides, sl);
		}
		r->room_aides = rewind_StringList(r->room_aides);
	} else
		LOAD_ROOM_SKIPLIST;

/* invited */
	listdestroy_StringList(r->invited);
	r->invited = NULL;

	if (flags & LOAD_ROOM_INVITED) {
		while(Fgets(f, buf, MAX_LINE) != NULL) {
			cstrip_line(buf);
			if (!*buf)
				break;

			if (user_exists(buf) && (sl = new_StringList(buf)) != NULL)
				r->invited = add_StringList(&r->invited, sl);
		}
		r->invited = rewind_StringList(r->invited);
	} else
		LOAD_ROOM_SKIPLIST;

/* kicked */
	listdestroy_StringList(r->kicked);
	r->kicked = NULL;

	if (flags & LOAD_ROOM_KICKED) {
		while(Fgets(f, buf, MAX_LINE) != NULL) {
			cstrip_line(buf);
			if (!*buf)
				break;

			if (user_exists(buf) && (sl = new_StringList(buf)) != NULL)
				r->kicked = add_StringList(&r->kicked, sl);
		}
		r->kicked = rewind_StringList(r->kicked);
	} else
		LOAD_ROOM_SKIPLIST;

/* chat history */
	if ((flags & LOAD_ROOM_CHAT_HISTORY) && (r->flags & ROOM_CHATROOM)) {
		if (r->chat_history == NULL && (r->chat_history = new_StringQueue()) == NULL)
			LOAD_ROOM_SKIPLIST;
		else {
			r->chat_history->tail = (ListType *)Fgetlist(f);
			r->chat_history->head = (ListType *)unwind_StringList((StringList *)r->chat_history->tail);
			r->chat_history->count = count_List(r->chat_history->tail);
		}
	} else
		LOAD_ROOM_SKIPLIST;

	return 0;

err_load_room:
	return -1;
}