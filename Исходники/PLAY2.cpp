void PLAY2::loadvals(FILE * fileptr)
{
	fscanf_s(fileptr,"%d %d %d %d %d %d %d %d %d",\
	&strength,&luck,&canswim,&survival,&dexterity,&agility,&constitution,&intelligence,&skillpoints);
	}