void
done_in_by(struct monst *mtmp)
{
static char buf[BUFSZ];
	pline("You die ...");
	if(mtmp->data->mlet == ' '){
		Sprintf(buf, "the ghost of %s", (char *) mtmp->mextra);
		killer = buf;
	} else if(mtmp->mnamelth) {
		Sprintf(buf, "%s called %s",
			mtmp->data->mname, NAME(mtmp));
		killer = buf;
	} else if(mtmp->minvis) {
		Sprintf(buf, "invisible %s", mtmp->data->mname);
		killer = buf;
	} else killer = mtmp->data->mname;
	done("died");
}