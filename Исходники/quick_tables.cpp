void CGame::init_quick_tables(void)
{
	int i;
	int part_size;
	List<CObject> l;
	CObject *o;

	part_size=dy/QUICK_PARTS;

	/* Background: */ 
	l.Instance(background);
	l.Rewind();
	while(l.Iterate(o)) {
		i=o->get_y()/part_size;
		if (i<0) i=0;
		if (i>=QUICK_PARTS-1) i=QUICK_PARTS-1;
		quick_background[i].Add(o);
	} /* while */ 

	/* Middleground: */ 
	l.Instance(middleground);
	l.Rewind();
	while(l.Iterate(o)) {
		i=o->get_y()/part_size;
		if (i<0) i=0;
		if (i>=QUICK_PARTS-1) i=QUICK_PARTS-1;
		quick_middleground[i].Add(o);
	} /* while */ 

	/* Foreground: */ 
	l.Instance(foreground);
	l.Rewind();
	while(l.Iterate(o)) {
		i=o->get_y()/part_size;
		if (i<0) i=0;
		if (i>=QUICK_PARTS-1) i=QUICK_PARTS-1;
		quick_foreground[i].Add(o);
	} /* while */ 

} /* CGame:init_quick_tables */ 