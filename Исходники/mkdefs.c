int main(int argc, char *argv[])
{
    char *filename;
    char *buf;
    char *tk;
    record vals;
    record *recp = &vals;
    FILE *fp;
    char guard[100];
    int idx = MINNAME;
    int lastval = 0;
    int lastmem = 0;

    if (argc != 2) {
	fprintf(stderr, "mkdefs: 1 argument necessary\n");
	exit(1);
    }
    filename = argv[1];

    vals.next = 0;
    buf = malloc(BSIZE);
    while (fgets(buf, BSIZE, stdin)) {
	lineno++;
	tokno = 0;
	tk = strTok(buf);
	if ((!tk) || (*tk == '#'))
	    continue;		/* comment */
	recp = newRec(recp);
	if (*tk == 'V')
	    recp->kind = K_val;
	else if (*tk == 'M')
	    recp->kind = K_member;
	else
	    recp->kind = 0;
	recp->data = buf;
	recp->symbol = tk;
	recp->name = strTok(0);
	recp->lex = strTok(0);
	recp->type = strTok(0);
	if (recp->kind) {
	    recp->domain = strTok(0);
	    recp->range = strTok(0);
	}
	buf = malloc(BSIZE);
    }

    fp = fopen(filename, "w");
    if (!fp) {
	fprintf(stderr, "mkdefs: Could not open %s for writing\n",
		filename);
	exit(1);
    }

    genGuard(filename, guard);
    fprintf(fp, header, guard, guard);
    fputs(prefix, fp);

    for (recp = vals.next; recp; recp = recp->next) {
	if (recp->kind == K_val)
	    lastval = idx;
	else if (recp->kind == K_member)
	    lastmem = idx;
	fprintf(fp, "#define\t%s\t% 5d\n", recp->symbol, idx++);
    }
    idx--;
    fprintf(fp, "\n#define LAST_V %d\n", lastval);
    fprintf(fp, "#define LAST_M %d\n", lastmem);
    fprintf(fp, "#define MINNAME %d\n#define MAXNAME %d\n\n", MINNAME,
	    idx);

    fprintf(fp, "static Exid_t symbols[] = {\n");
    for (recp = vals.next; recp; recp = recp->next) {
	fprintf(fp, "\tEXID ( %s, %s, %s, %s, 0),\n",
		recp->name, recp->lex, recp->symbol, recp->type);
    }
    fprintf(fp, "\tEXID ( {0}, 0, 0, 0, 0)\n};\n");

    fprintf(fp, "\nstatic char* typenames[] = {\n");
    for (recp = vals.next; recp; recp = recp->next) {
	if (*(recp->symbol) == 'T')
	    fprintf(fp, "\t%s,\n", recp->name);
    }
    fprintf(fp, "};\n");

#ifdef DEBUG
    fprintf(fp, "\nstatic char* gprnames[] = {\n\t\"\",\n");
    for (recp = vals.next; recp; recp = recp->next) {
	fprintf(fp, "\t\"%s\",\n", recp->symbol);
    }
    fprintf(fp, "};\n");
#endif

    fprintf(fp, "\ntypedef unsigned short tctype;\n");
    fprintf(fp, "\nstatic tctype tchk[][2] = {\n\t{ 0, 0 },\n");
    for (recp = vals.next; recp; recp = recp->next) {
	if (recp->kind)
	    fprintf(fp, "\t{ %s, %s },\n", recp->domain, recp->range);
    }
    fprintf(fp, "};\n");

    fprintf(fp, "\n#endif\n");
    fclose(fp);
    exit(0);
}