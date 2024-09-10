static int text_autocomplete_modal(bContext *C, wmOperator *op, const wmEvent *event)
{
	SpaceText *st = CTX_wm_space_text(C);
	ScrArea *sa = CTX_wm_area(C);
	ARegion *ar = BKE_area_find_region_type(sa, RGN_TYPE_WINDOW);

	int draw = 0, tools = 0, swallow = 0, scroll = 1;
	Text *text = CTX_data_edit_text(C);
	int retval = OPERATOR_RUNNING_MODAL;

	(void)text;

	if (st->doplugins && texttool_text_is_active(st->text)) {
		if (texttool_suggest_first()) tools |= TOOL_SUGG_LIST;
		if (texttool_docs_get()) tools |= TOOL_DOCUMENT;
	}

	switch (event->type) {
		case LEFTMOUSE:
			if (event->val == KM_PRESS) {
				if (text_do_suggest_select(st, ar))
					swallow = 1;
				else {
					if (tools & TOOL_SUGG_LIST) texttool_suggest_clear();
					if (tools & TOOL_DOCUMENT) texttool_docs_clear(), doc_scroll = 0;
					retval = OPERATOR_FINISHED;
				}
				draw = 1;
			}
			break;
		case MIDDLEMOUSE:
			if (event->val == KM_PRESS) {
				if (text_do_suggest_select(st, ar)) {
					confirm_suggestion(st->text);
					text_update_line_edited(st->text->curl);
					swallow = 1;
				}
				else {
					if (tools & TOOL_SUGG_LIST) texttool_suggest_clear();
					if (tools & TOOL_DOCUMENT) texttool_docs_clear(), doc_scroll = 0;
					retval = OPERATOR_FINISHED;
				}
				draw = 1;
			}
			break;
		case ESCKEY:
			if (event->val == KM_PRESS) {
				draw = swallow = 1;
				if (tools & TOOL_SUGG_LIST) texttool_suggest_clear();
				else if (tools & TOOL_DOCUMENT) texttool_docs_clear(), doc_scroll = 0;
				else draw = swallow = 0;
				retval = OPERATOR_CANCELLED;
			}
			break;
		case RETKEY:
		case PADENTER:
			if (event->val == KM_PRESS) {
				if (tools & TOOL_SUGG_LIST) {
					confirm_suggestion(st->text);
					text_update_line_edited(st->text->curl);
					swallow = 1;
					draw = 1;
				}
				if (tools & TOOL_DOCUMENT) texttool_docs_clear(), doc_scroll = 0, draw = 1;
				retval = OPERATOR_FINISHED;
			}
			break;
		case LEFTARROWKEY:
		case BACKSPACEKEY:
			if (event->val == KM_PRESS) {
				if (tools & TOOL_SUGG_LIST) {
					if (event->ctrl) {
						texttool_suggest_clear();
						retval = OPERATOR_CANCELLED;
					}
					else {
						/* Work out which char we are about to delete/pass */
						if (st->text->curl && st->text->curc > 0) {
							char ch = st->text->curl->line[st->text->curc - 1];
							if ((ch == '_' || !ispunct(ch)) && !text_check_whitespace(ch)) {
								get_suggest_prefix(st->text, -1);
								text_pop_suggest_list();
							}
							else {
								texttool_suggest_clear();
								retval = OPERATOR_CANCELLED;
							}
						}
						else {
							texttool_suggest_clear();
							retval = OPERATOR_CANCELLED;
						}
					}
				}
				if (tools & TOOL_DOCUMENT) texttool_docs_clear(), doc_scroll = 0;
			}
			break;
		case RIGHTARROWKEY:
			if (event->val == KM_PRESS) {
				if (tools & TOOL_SUGG_LIST) {
					if (event->ctrl) {
						texttool_suggest_clear();
						retval = OPERATOR_CANCELLED;
					}
					else {
						/* Work out which char we are about to pass */
						if (st->text->curl && st->text->curc < st->text->curl->len) {
							char ch = st->text->curl->line[st->text->curc + 1];
							if ((ch == '_' || !ispunct(ch)) && !text_check_whitespace(ch)) {
								get_suggest_prefix(st->text, 1);
								text_pop_suggest_list();
							}
							else {
								texttool_suggest_clear();
								retval = OPERATOR_CANCELLED;
							}
						}
						else {
							texttool_suggest_clear();
							retval = OPERATOR_CANCELLED;
						}
					}
				}
				if (tools & TOOL_DOCUMENT) texttool_docs_clear(), doc_scroll = 0;
			}
			break;
		case PAGEDOWNKEY:
			scroll = SUGG_LIST_SIZE - 1;
			/* fall-through */
		case WHEELDOWNMOUSE:
		case DOWNARROWKEY:
			if (event->val == KM_PRESS) {
				if (tools & TOOL_DOCUMENT) {
					doc_scroll++;
					swallow = 1;
					draw = 1;
				}
				else if (tools & TOOL_SUGG_LIST) {
					SuggItem *sel = texttool_suggest_selected();
					if (!sel) {
						texttool_suggest_select(texttool_suggest_first());
					}
					else {
						while (sel && scroll--) {
							if (sel != texttool_suggest_last() && sel->next) {
								texttool_suggest_select(sel->next);
								sel = sel->next;
							}
							else {
								texttool_suggest_select(texttool_suggest_first());
								sel = texttool_suggest_first();
							}
						}
					}
					text_pop_suggest_list();
					swallow = 1;
					draw = 1;
				}
			}
			break;
		case PAGEUPKEY:
			scroll = SUGG_LIST_SIZE - 1;
			/* fall-through */
		case WHEELUPMOUSE:
		case UPARROWKEY:
			if (event->val == KM_PRESS) {
				if (tools & TOOL_DOCUMENT) {
					if (doc_scroll > 0) doc_scroll--;
					swallow = 1;
					draw = 1;
				}
				else if (tools & TOOL_SUGG_LIST) {
					SuggItem *sel = texttool_suggest_selected();
					while (sel && scroll--) {
						if (sel != texttool_suggest_first() && sel->prev) {
							texttool_suggest_select(sel->prev);
							sel = sel->prev;
						}
						else {
							texttool_suggest_select(texttool_suggest_last());
							sel = texttool_suggest_last();
						}
					}
					text_pop_suggest_list();
					swallow = 1;
					draw = 1;
				}
			}
			break;
		case RIGHTSHIFTKEY:
		case LEFTSHIFTKEY:
			break;
#if 0
		default:
			if (tools & TOOL_SUGG_LIST) texttool_suggest_clear(), draw = 1;
			if (tools & TOOL_DOCUMENT) texttool_docs_clear(), doc_scroll = 0, draw = 1;
#endif
	}

	if (draw) {
		ED_area_tag_redraw(sa);
	}

//	if (swallow) {
//		retval = OPERATOR_RUNNING_MODAL;
//	}

	if (texttool_suggest_first()) {
		if (retval != OPERATOR_RUNNING_MODAL) {
			text_autocomplete_free(C, op);
		}
		return retval;
	}
	else {
		text_autocomplete_free(C, op);
		return OPERATOR_FINISHED;
	}
}