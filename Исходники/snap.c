static void
init_ram_segments(void)
{
	int i, errflag;
        FILE *iomem; 
	char buf[BUFSIZE], *p1, *p2;
	physaddr_t start, end;

	if ((iomem = fopen("/proc/iomem", "r")) == NULL)
		goto fail_iomem;

	while (fgets(buf, BUFSIZE, iomem)) {
		if (strstr(buf, "System RAM")) {
			console(buf);
			nr_segments++;
		}
	}
	if (!nr_segments)
		goto fail_iomem;

	ram_segments = (struct ram_segments *)
		GETBUF(sizeof(struct ram_segments) * nr_segments);

	rewind(iomem);
	i = 0;
	while (fgets(buf, BUFSIZE, iomem)) {
		if (strstr(buf, "System RAM")) {
			if (!(p1 = strstr(buf, ":")))
				goto fail_iomem;
			*p1 = NULLCHAR;
			clean_line(buf);
			if (strstr(buf, " "))
				goto fail_iomem;
			p1 = buf;
			if (!(p2 = strstr(buf, "-")))
				goto fail_iomem;
			*p2 = NULLCHAR;
			p2++;
			errflag = 0;
			start = htoll(p1, RETURN_ON_ERROR|QUIET, &errflag);
			end = htoll(p2, RETURN_ON_ERROR|QUIET, &errflag);
			if (errflag)
				goto fail_iomem;
			ram_segments[i].start = PHYSPAGEBASE(start);
			if (PAGEOFFSET(start))
				ram_segments[i].start += PAGESIZE();
			ram_segments[i].end = PHYSPAGEBASE(end);
			if (PAGEOFFSET(end) == (PAGESIZE()-1))
				ram_segments[i].end += PAGESIZE();
			console("ram_segments[%d]: %016llx %016llx [%s-%s]\n", i,
				(ulonglong)ram_segments[i].start, 
				(ulonglong)ram_segments[i].end, p1, p2);
			i++;
		}
	}

	fclose(iomem);
	return;

fail_iomem:
	fclose(iomem);
	nr_segments = 0;
	if (ram_segments)
		FREEBUF(ram_segments);

	return; 
}