static int
diskarenapart(HConnect *c, char *disk, Part *p)
{
	char *arenaname;
	ArenaPart ap;
	ArenaHead head;
	Arena arena;
	char *table;
	char *score;
	char *clump;
	uchar *blk;
	vlong start, end, off;
	char tbuf[60];

	hprint(&c->hout, "<h1>arena partition %s</h1>\n", disk);

	if((table = readap(p, &ap)) == nil){
		hprint(&c->hout, "%r\n");
		goto out;
	}
	
	hprint(&c->hout, "<pre>\n");
	hprint(&c->hout, "version=%d blocksize=%d base=%d\n",
		ap.version, ap.blocksize, ap.arenabase);
	hprint(&c->hout, "</pre>\n");

	arenaname = hargstr(c, "arena", "");
	if(arenaname[0] == 0){
		diskarenatable(c, disk, table);
		goto out;
	}
	
	if(xfindarena(table, arenaname, &start, &end) < 0){
		hprint(&c->hout, "no such arena %s\n", arenaname);
		goto out;
	}
	
	hprint(&c->hout, "<h2>arena %s</h2>\n", arenaname);
	hprint(&c->hout, "<pre>start=%#llx end=%#llx<pre>\n", start, end);
	if(end < start || end - start < HeadSize){
		hprint(&c->hout, "bad size %#llx\n", end - start);
		goto out;
	}

	// read arena header, tail
	blk = vtmalloc(HeadSize);
	if(readpart(p, start, blk, HeadSize) != HeadSize){
		hprint(&c->hout, "reading header: %r\n");
		vtfree(blk);
		goto out;
	}
	if(unpackarenahead(&head, blk) < 0){
		hprint(&c->hout, "corrupt arena header: %r\n");
		// hhex(blk, HeadSize);
		vtfree(blk);
		goto out;
	}
	vtfree(blk);

	hprint(&c->hout, "head:\n<pre>\n");
	hprint(&c->hout, "version=%d name=%s blocksize=%d size=%#llx clumpmagic=%#ux\n",
		head.version, head.name, head.blocksize, head.size, 
		head.clumpmagic);
	hprint(&c->hout, "</pre><br><br>\n");

	if(head.blocksize > MaxIoSize || head.blocksize >= end - start){
		hprint(&c->hout, "corrupt block size %d\n", head.blocksize);
		goto out;
	}

	blk = vtmalloc(head.blocksize);
	if(readpart(p, end - head.blocksize, blk, head.blocksize) < 0){
		hprint(&c->hout, "reading tail: %r\n");
		vtfree(blk);
		goto out;
	}
	memset(&arena, 0, sizeof arena);
	arena.part = p;
	arena.blocksize = head.blocksize;
	arena.clumpmax = head.blocksize / ClumpInfoSize;
	arena.base = start + head.blocksize;
	arena.size = end - start - 2 * head.blocksize;
	if(unpackarena(&arena, blk) < 0){
		vtfree(blk);
		goto out;
	}
	scorecp(arena.score, blk+head.blocksize - VtScoreSize);

	vtfree(blk);
	
	hprint(&c->hout, "tail:\n<pre>\n");
	hprint(&c->hout, "version=%d name=%s\n", arena.version, arena.name);
	hprint(&c->hout, "ctime=%d %s\n", arena.ctime, fmttime(tbuf, arena.ctime));
	hprint(&c->hout, "wtime=%d %s\n", arena.wtime, fmttime(tbuf, arena.wtime));
	hprint(&c->hout, "clumpmagic=%#ux\n", arena.clumpmagic);
	hprint(&c->hout, "score %V\n", arena.score);
	hprint(&c->hout, "diskstats:\n");
	hprint(&c->hout, "\tclumps=%,d cclumps=%,d used=%,lld uncsize=%,lld sealed=%d\n",
		arena.diskstats.clumps, arena.diskstats.cclumps,
		arena.diskstats.used, arena.diskstats.uncsize,
		arena.diskstats.sealed);
	hprint(&c->hout, "memstats:\n");
	hprint(&c->hout, "\tclumps=%,d cclumps=%,d used=%,lld uncsize=%,lld sealed=%d\n",
		arena.memstats.clumps, arena.memstats.cclumps,
		arena.memstats.used, arena.memstats.uncsize,
		arena.memstats.sealed);
	if(arena.clumpmax == 0){
		hprint(&c->hout, "bad clumpmax\n");
		goto out;
	}

	score = hargstr(c, "score", "");
	clump = hargstr(c, "clump", "");

	if(clump[0]){
		off = strtoull(clump, 0, 0);
		diskarenaclump(c, &arena, off, score[0] ? score : nil);
	}else if(score[0]){
		diskarenaclump(c, &arena, -1, score);
	}else{
		diskarenatoc(c, &arena);
	}

out:
	free(table);
	return 0;
}