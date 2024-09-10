static ut64 getFunctionSize(Sdb *db) {
#if 1
	ut64 min = sdb_num_get (db, Fmin (addr), NULL);
	ut64 max = sdb_num_get (db, Fmax (addr), NULL);
#else
	ut64 min, max;
	char *c, *bbs = sdb_get (db, "bbs", NULL);
	int first = 1;
	sdb_aforeach (c, bbs) {
		ut64 addr = sdb_atoi (c);
		ut64 addr_end = sdb_num_get (db, Fbb(addr), NULL);
		if (first) {
			min = addr;
			max = addr_end;
			first = 0;
		} else {
			if (addr<min)
				min = addr;
			if (addr_end>max)
				max = addr_end;
		}
		sdb_aforeach_next (c);
	}