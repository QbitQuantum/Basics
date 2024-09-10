void
Tk_AddOption(
    Tk_Window tkwin,		/* Window token; option will be associated
				 * with main window for this window. */
    const char *name,		/* Multi-element name of option. */
    const char *value,		/* String value for option. */
    int priority)		/* Overall priority level to use for this
				 * option, such as TK_USER_DEFAULT_PRIO or
				 * TK_INTERACTIVE_PRIO. Must be between 0 and
				 * TK_MAX_PRIO. */
{
    TkWindow *winPtr = ((TkWindow *) tkwin)->mainPtr->winPtr;
    register ElArray **arrayPtrPtr;
    register Element *elPtr;
    Element newEl;
    register const char *p;
    const char *field;
    int count, firstField;
    ptrdiff_t length;
#define TMP_SIZE 100
    char tmp[TMP_SIZE+1];
    ThreadSpecificData *tsdPtr =
	    Tcl_GetThreadData(&dataKey, sizeof(ThreadSpecificData));

    if (winPtr->mainPtr->optionRootPtr == NULL) {
	OptionInit(winPtr->mainPtr);
    }
    tsdPtr->cachedWindow = NULL;/* Invalidate the cache. */

    /*
     * Compute the priority for the new element, including both the overall
     * level and the serial number (to disambiguate with the level).
     */

    if (priority < 0) {
	priority = 0;
    } else if (priority > TK_MAX_PRIO) {
	priority = TK_MAX_PRIO;
    }
    newEl.priority = (priority << 24) + tsdPtr->serial;
    tsdPtr->serial++;

    /*
     * Parse the option one field at a time.
     */

    arrayPtrPtr = &(((TkWindow *) tkwin)->mainPtr->optionRootPtr);
    p = name;
    for (firstField = 1; ; firstField = 0) {
	/*
	 * Scan the next field from the name and convert it to a Tk_Uid. Must
	 * copy the field before calling Tk_Uid, so that a terminating NULL
	 * may be added without modifying the source string.
	 */

	if (*p == '*') {
	    newEl.flags = WILDCARD;
	    p++;
	} else {
	    newEl.flags = 0;
	}
	field = p;
	while ((*p != 0) && (*p != '.') && (*p != '*')) {
	    p++;
	}
	length = p - field;
	if (length > TMP_SIZE) {
	    length = TMP_SIZE;
	}
	strncpy(tmp, field, (size_t) length);
	tmp[length] = 0;
	newEl.nameUid = Tk_GetUid(tmp);
	if (isupper(UCHAR(*field))) {
	    newEl.flags |= CLASS;
	}

	if (*p != 0) {
	    /*
	     * New element will be a node. If this option can't possibly apply
	     * to this main window, then just skip it. Otherwise, add it to
	     * the parent, if it isn't already there, and descend into it.
	     */

	    newEl.flags |= NODE;
	    if (firstField && !(newEl.flags & WILDCARD)
		    && (newEl.nameUid != winPtr->nameUid)
		    && (newEl.nameUid != winPtr->classUid)) {
		return;
	    }
	    for (elPtr = (*arrayPtrPtr)->els, count = (*arrayPtrPtr)->numUsed;
		    ; elPtr++, count--) {
		if (count == 0) {
		    newEl.child.arrayPtr = NewArray(5);
		    *arrayPtrPtr = ExtendArray(*arrayPtrPtr, &newEl);
		    arrayPtrPtr = &((*arrayPtrPtr)
			    ->nextToUse[-1].child.arrayPtr);
		    break;
		}
		if ((elPtr->nameUid == newEl.nameUid)
			&& (elPtr->flags == newEl.flags)) {
		    arrayPtrPtr = &(elPtr->child.arrayPtr);
		    break;
		}
	    }
	    if (*p == '.') {
		p++;
	    }
	} else {
	    /*
	     * New element is a leaf. Add it to the parent, if it isn't
	     * already there. If it exists already, keep whichever value has
	     * highest priority.
	     */

	    newEl.child.valueUid = Tk_GetUid(value);
	    for (elPtr = (*arrayPtrPtr)->els, count = (*arrayPtrPtr)->numUsed;
		    ; elPtr++, count--) {
		if (count == 0) {
		    *arrayPtrPtr = ExtendArray(*arrayPtrPtr, &newEl);
		    return;
		}
		if ((elPtr->nameUid == newEl.nameUid)
			&& (elPtr->flags == newEl.flags)) {
		    if (elPtr->priority < newEl.priority) {
			elPtr->priority = newEl.priority;
			elPtr->child.valueUid = newEl.child.valueUid;
		    }
		    return;
		}
	    }
	}
    }
}