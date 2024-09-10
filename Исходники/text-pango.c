PangoLayout*
gdip_pango_setup_layout (GpGraphics *graphics, GDIPCONST WCHAR *stringUnicode, int length, GDIPCONST GpFont *font,
	GDIPCONST RectF *rc, RectF *box, GDIPCONST GpStringFormat *format, int **charsRemoved)
{
	GpStringFormat *fmt;
	PangoLayout *layout;
	PangoContext *context;
	PangoRectangle logical;   /* logical size of text (used for alignment) */
	PangoRectangle ink;       /* ink size of text (to pixel boundaries) */
	PangoAttrList *list = NULL;
	GString *ftext;
	PangoTabArray *tabs;
	PangoLayoutIter *iter;
	int i;
	int FrameWidth;     /* rc->Width (or rc->Height if vertical) */
	int FrameHeight;    /* rc->Height (or rc->Width if vertical) */
	int FrameX;         /* rc->X (or rc->Y if vertical) */
	int FrameY;         /* rc->Y (or rc->X if vertical) */
	int y0;             /* y0,y1,clipNN used for checking line positions vs. clip rectangle */
	int y1;
	double clipx1;
	double clipx2;
	double clipy1;
	double clipy2;
	int trimSpace;      /* whether or not to trim the space */

	gchar *text = ucs2_to_utf8 (stringUnicode, length);
	if (!text)
		return NULL;
	length = strlen(text);

	if (charsRemoved) {
		(*charsRemoved) = GdipAlloc (sizeof (int) * length);
		if (!*charsRemoved) {
			GdipFree (text);
		return NULL;
		}
		memset (*charsRemoved, 0, sizeof (int) * length);
	}

	/* TODO - Digit substitution */

// g_warning ("layout >%s< (%d) [x %g, y %g, w %g, h %g] [font %s, %g points]", text, length, rc->X, rc->Y, rc->Width, FrameHeight, font->face, font->emSize);

	/* a NULL format is valid, it means get the generic default values (and free them later) */
	if (!format) {
		GpStatus status = GdipStringFormatGetGenericDefault ((GpStringFormat **)&fmt);
		if (status != Ok) {
			GdipFree (text);
			return NULL;
		}
	} else {
		fmt = (GpStringFormat *)format;
	}

	layout = pango_cairo_create_layout (graphics->ct);

	/* context is owned by Pango (i.e. not referenced counted) do not free */
	context = pango_layout_get_context (layout);

	pango_layout_set_font_description (layout, gdip_get_pango_font_description ((GpFont*) font));

	if (fmt->formatFlags & StringFormatFlagsDirectionVertical) {
		FrameWidth = MAKE_SAFE_FOR_PANGO (SAFE_FLOAT_TO_UINT32 (rc->Height));
		FrameHeight = MAKE_SAFE_FOR_PANGO (SAFE_FLOAT_TO_UINT32 (rc->Width));
		FrameX = SAFE_FLOAT_TO_UINT32 (rc->Y);
		FrameY = SAFE_FLOAT_TO_UINT32 (rc->X);
	} else {
		FrameWidth = MAKE_SAFE_FOR_PANGO (SAFE_FLOAT_TO_UINT32 (rc->Width));
		FrameHeight = MAKE_SAFE_FOR_PANGO (SAFE_FLOAT_TO_UINT32 (rc->Height));
		FrameX = SAFE_FLOAT_TO_UINT32 (rc->X);
		FrameY = SAFE_FLOAT_TO_UINT32 (rc->Y);
	}
	//g_warning("FW: %d\tFH: %d", FrameWidth, FrameHeight);

	if ((FrameWidth <= 0) || (fmt->formatFlags & StringFormatFlagsNoWrap)) {
		pango_layout_set_width (layout, -1);
		//g_warning ("Setting width: %d", -1);
	} else {
		pango_layout_set_width (layout, FrameWidth * PANGO_SCALE);
		//g_warning ("Setting width: %d", FrameWidth * PANGO_SCALE);
	}

	if ((rc->Width != 0) && (rc->Height != 0) && ((fmt->formatFlags & StringFormatFlagsNoClip) == 0)) {
// g_warning ("\tclip [%g %g %g %g]", rc->X, rc->Y, rc->Width, rc->Height);
		/* We do not call cairo_reset_clip because we want to take previous clipping into account */
		/* Use rc instead of frame variables because this is pre-transform */
		gdip_cairo_rectangle (graphics, rc->X, rc->Y, rc->Width, rc->Height, TRUE);
		cairo_clip (graphics->ct);
	}

		/* with GDI+ the API not the renderer makes the direction decision */
		pango_layout_set_auto_dir (layout, FALSE);
	if (!(fmt->formatFlags & StringFormatFlagsDirectionRightToLeft) != !(fmt->formatFlags & StringFormatFlagsDirectionVertical)) {
		pango_context_set_base_dir (context, PANGO_DIRECTION_WEAK_RTL);
		pango_layout_context_changed (layout);

		/* horizontal alignment */
		switch (fmt->alignment) {
		case StringAlignmentNear:
			pango_layout_set_alignment (layout, PANGO_ALIGN_RIGHT);
			break;
		case StringAlignmentCenter:
			pango_layout_set_alignment (layout, PANGO_ALIGN_CENTER);
			break;
		case StringAlignmentFar:
			pango_layout_set_alignment (layout, PANGO_ALIGN_LEFT);
			break;
		}
	} else {
		/* pango default base dir is WEAK_LTR, which is what we want */

		/* horizontal alignment */
		switch (fmt->alignment) {
		case StringAlignmentNear:
			pango_layout_set_alignment (layout, PANGO_ALIGN_LEFT);
			break;
		case StringAlignmentCenter:
			pango_layout_set_alignment (layout, PANGO_ALIGN_CENTER);
			break;
		case StringAlignmentFar:
			pango_layout_set_alignment (layout, PANGO_ALIGN_RIGHT);
			break;
		}
	}

#ifdef PANGO_VERSION_CHECK
#if PANGO_VERSION_CHECK(1,16,0)
	if (fmt->formatFlags & StringFormatFlagsDirectionVertical) {
		if (fmt->formatFlags & StringFormatFlagsDirectionRightToLeft) {
			cairo_rotate (graphics->ct, M_PI/2.0);
			cairo_translate (graphics->ct, 0, -FrameHeight);
			pango_cairo_update_context (graphics->ct, context);
		} else {
			cairo_rotate (graphics->ct, 3.0*M_PI/2.0);
			cairo_translate (graphics->ct, -FrameWidth, 0);
			pango_cairo_update_context (graphics->ct, context);
		}
		/* only since Pango 1.16 */
		pango_context_set_base_gravity (context, PANGO_GRAVITY_AUTO);
		pango_context_set_gravity_hint (context, PANGO_GRAVITY_HINT_LINE);
		pango_layout_context_changed (layout);
	}
#endif
#endif

	/* TODO - StringFormatFlagsDisplayFormatControl
		scan and replace them ??? */

	/* Trimming options seem to apply only to the end of the string - gdi+ will still wrap
	 * with preference to word first, then character.  Unfortunately, pango doesn't have
	 * any way to differentiate wrapping behavior from trimming behavior that I could find */
	pango_layout_set_wrap (layout, PANGO_WRAP_WORD_CHAR);
	switch (fmt->trimming) {
	case StringTrimmingNone:
		pango_layout_set_ellipsize (layout, PANGO_ELLIPSIZE_NONE);
		break;
	case StringTrimmingCharacter:
		pango_layout_set_ellipsize (layout, PANGO_ELLIPSIZE_NONE);
		break;
	case StringTrimmingWord:
		pango_layout_set_ellipsize (layout, PANGO_ELLIPSIZE_NONE);
		break;
	case StringTrimmingEllipsisCharacter:
		pango_layout_set_ellipsize (layout, PANGO_ELLIPSIZE_END);
		if (!(fmt->formatFlags & StringFormatFlagsNoWrap))
			pango_layout_set_height (layout, FrameHeight == 0 ? G_MAXINT32 : FrameHeight * PANGO_SCALE);
		break;
	case StringTrimmingEllipsisWord:
		pango_layout_set_ellipsize (layout, PANGO_ELLIPSIZE_END);
		if (!(fmt->formatFlags & StringFormatFlagsNoWrap))
			pango_layout_set_height (layout, FrameHeight == 0 ? G_MAXINT32 : FrameHeight * PANGO_SCALE);
		break;
	case StringTrimmingEllipsisPath:
		pango_layout_set_ellipsize (layout, PANGO_ELLIPSIZE_MIDDLE);
		if (!(fmt->formatFlags & StringFormatFlagsNoWrap))
			pango_layout_set_height (layout, FrameHeight == 0 ? G_MAXINT32 : FrameHeight * PANGO_SCALE);
		break;
	}

	/* some stuff can only be done by manipulating the attributes (but we can avoid this most of the time) */
	if ((fmt->formatFlags & StringFormatFlagsNoFontFallback) || (font->style & (FontStyleUnderline | FontStyleStrikeout))) {

		list = gdip_get_layout_attributes (layout);

		/* StringFormatFlagsNoFontFallback */
		if (fmt->formatFlags & StringFormatFlagsNoFontFallback) {
			PangoAttribute *attr = pango_attr_fallback_new (FALSE);
			attr->start_index = 0;
			attr->end_index = length;
			pango_attr_list_insert (list, attr);
		}

		if (font->style & FontStyleUnderline) {
			PangoAttribute *attr = pango_attr_underline_new (PANGO_UNDERLINE_SINGLE);
			attr->start_index = 0;
			attr->end_index = length;
			pango_attr_list_insert (list, attr);
		}

		if (font->style & FontStyleStrikeout) {
			PangoAttribute *attr = pango_attr_strikethrough_new (TRUE);
			attr->start_index = 0;
			attr->end_index = length;
			pango_attr_list_insert (list, attr);
		}
	}

	if (fmt->numtabStops > 0) {
		float tabPosition;
		tabs = pango_tab_array_new (fmt->numtabStops, FALSE);
		tabPosition = fmt->firstTabOffset;
		for (i = 0; i < fmt->numtabStops; i++) {
			tabPosition += fmt->tabStops[i];
			pango_tab_array_set_tab (tabs, i, PANGO_TAB_LEFT, (gint)min (tabPosition, PANGO_MAX) * PANGO_SCALE);
		}
		pango_layout_set_tabs (layout, tabs);
		pango_tab_array_free (tabs);
	}

	//g_warning ("length before ws removal: %d", length);
	trimSpace = (fmt->formatFlags & StringFormatFlagsMeasureTrailingSpaces) == 0;
	switch (fmt->hotkeyPrefix) {
	case HotkeyPrefixHide:
		/* we need to remove any accelerator from the string */
		ftext = gdip_process_string (text, length, 1, trimSpace, NULL, charsRemoved);
		break;
	case HotkeyPrefixShow:
		/* optimization: is seems that we never see the hotkey when using an underline font */
		if (font->style & FontStyleUnderline) {
			/* so don't bother drawing it (and simply add the '&' character) */
			ftext = gdip_process_string (text, length, 1, trimSpace, NULL, charsRemoved);
		} else {
			/* find accelerator and add attribute to the next character (unless it's the prefix too) */
			if (!list)
				list = gdip_get_layout_attributes (layout);
			ftext = gdip_process_string (text, length, 1, trimSpace, list, charsRemoved);
		}
		break;
	default:
		ftext = gdip_process_string (text, length, 0, trimSpace, NULL, charsRemoved);
		break;
	}
	length = ftext->len;
	//g_warning ("length after ws removal: %d", length);

	if (list) {
		pango_layout_set_attributes (layout, list);
		pango_attr_list_unref (list);
	}

// g_warning("\tftext>%s< (%d)", ftext->str, -1);
	pango_layout_set_text (layout, ftext->str, ftext->len);
	GdipFree (text);
	g_string_free(ftext, TRUE);

	/* Trim the text after the last line for ease of counting lines/characters */
	/* Also prevents drawing whole lines outside the boundaries if NoClip was specified */
	/* In case of pre-existing clipping, use smaller of clip rectangle or our specified height */
	if (FrameHeight > 0) {
		cairo_clip_extents (graphics->ct, &clipx1, &clipy1, &clipx2, &clipy2);
		if (clipy2 > 0 && !(fmt->formatFlags & StringFormatFlagsNoClip))
			clipy2 = min (clipy2, FrameHeight + FrameY);
		else
			clipy2 = FrameHeight + FrameY;
		iter = pango_layout_get_iter (layout);
		do {
			if (iter == NULL)
				break;
			pango_layout_iter_get_line_yrange (iter, &y0, &y1);
			//g_warning("yrange: %d  %d  clipy2: %f", y0 / PANGO_SCALE, y1 / PANGO_SCALE, clipy2);
			/* StringFormatFlagsLineLimit */
			if (((fmt->formatFlags & StringFormatFlagsLineLimit) && y1 / PANGO_SCALE > clipy2) || (y0 / PANGO_SCALE > clipy2)) {
				PangoLayoutLine *line = pango_layout_iter_get_line_readonly (iter);
				pango_layout_set_text (layout, pango_layout_get_text (layout), line->start_index);
				break;
			}
		} while (pango_layout_iter_next_line (iter));
		pango_layout_iter_free (iter);
	}

	pango_layout_get_pixel_extents (layout, &ink, &logical);
// g_warning ("\tlogical\t[x %d, y %d, w %d, h %d][x %d, y %d, w %d, h %d]", logical.x, logical.y, logical.width, logical.height, ink.x, ink.y, ink.width, ink.height);

	if ((fmt->formatFlags & StringFormatFlagsNoFitBlackBox) == 0) {
		/* By default don't allow overhang - ink space may be larger than logical space */
		if (fmt->formatFlags & StringFormatFlagsDirectionVertical) {
			box->X = min (ink.y, logical.y);
			box->Y = min (ink.x, logical.x);
			box->Height = max (ink.width, logical.width);
			box->Width = max (ink.height, logical.height);
		} else {
			box->X = min (ink.x, logical.x);
			box->Y = min (ink.y, logical.y);
			box->Height = max (ink.height, logical.height);
			box->Width = max (ink.width, logical.width);
		}
	} else {
		/* Allow overhang */
		if (fmt->formatFlags & StringFormatFlagsDirectionVertical) {
			box->X = logical.y;
			box->Y = logical.x;
			box->Height = logical.width;
			box->Width = logical.height;
		} else {
			box->X = logical.x;
			box->Y = logical.y;
	box->Height = logical.height;
			box->Width = logical.width;
		}
	}
// g_warning ("\tbox\t[x %g, y %g, w %g, h %g]", box->X, box->Y, box->Width, box->Height);

	/* vertical alignment*/
	if (fmt->formatFlags & StringFormatFlagsDirectionVertical) {
		switch (fmt->lineAlignment) {
		case StringAlignmentNear:
			break;
		case StringAlignmentCenter:
			box->X += (rc->Width - box->Width) / 2;
			break;
		case StringAlignmentFar:
			box->X += (rc->Width - box->Width);
			break;
		}
	} else {
	switch (fmt->lineAlignment) {
	case StringAlignmentNear:
		break;
	case StringAlignmentCenter:
			box->Y += (rc->Height - box->Height) / 2;
		break;
	case StringAlignmentFar:
			box->Y += (rc->Height - box->Height);
		break;
	}
	}
// g_warning ("va-box\t[x %g, y %g, w %g, h %g]", box->X, box->Y, box->Width, box->Height);

	pango_cairo_update_layout (graphics->ct, layout);

	return layout;
}