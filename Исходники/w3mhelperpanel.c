void
editMailcap(char *mailcap, struct parsed_tagarg *args)
{
    TextList *t = newTextList();
    TextListItem *ti;
    FILE *f;
    Str tmp;
    char *type, *viewer;
    struct parsed_tagarg *a;
    bool delete_it;

    if ((f = fopen(mailcap, "rt")) == NULL)
	bye("Can't open", mailcap);

    while (tmp = Strfgets(f), tmp->length > 0) {
	if (tmp->ptr[0] == '#')
	    continue;
	Strchop(tmp);
	extractMailcapEntry(tmp->ptr, &type, &viewer);
	delete_it = false;
	for (a = args; a != NULL; a = a->next) {
	    if (!strcmp(a->arg, "delete") && !strcmp(a->value, type)) {
		delete_it = true;
		break;
	    }
	}
	if (!delete_it)
	    pushText(t, Sprintf("%s;\t%s\n", type, viewer)->ptr);
    }
    type = tag_get_value(args, "newtype");
    viewer = tag_get_value(args, "newcmd");
    if (type != NULL && *type != '\0' && viewer != NULL && *viewer != '\0')
	pushText(t, Sprintf("%s;\t%s\n", type, viewer)->ptr);
    fclose(f);
    if ((f = fopen(mailcap, "w")) == NULL)
	bye("Can't write to", mailcap);

    for (ti = t->first; ti != NULL; ti = ti->next)
	fputs(ti->ptr, f);
    fclose(f);
    printf("Content-Type: text/plain\n");
    printf("w3m-control: BACK\nw3m-control: BACK\n");
    printf("w3m-control: REINIT MAILCAP\n");
}