static void FILE_from_erlangv(ErlDrvData drv_data,  ErlIOVec* ev)
{
    Desc *desc = (Desc*) drv_data;
    SysIOVec  *iov = ev->iov;
    ErlDrvBinary* bin;

    switch ((&iov[1])->iov_base[0]) {

    case XX_OPEN: {
	char buf[BUFSIZ];
	char file[BUFSIZ];  /* should be FILENAME_MAX */
	char flags[4];       /* at most someething like rb+ */
	char* src;
	char* dst;
	char* src_end;
	char* dst_end;
	int n;

	if (desc->fp != NULL) {
	    driver_error(desc->port, XX_EINVAL);
	    return;
	}

	/* play it safe ? */
	n = vec_to_buf(ev, buf, BUFSIZ);
	src = buf + 1;
	src_end = buf + n;

	/* get file name */
	dst = file;
	dst_end = dst + BUFSIZ;  /* make room for a '\0' */
	while((src < src_end) && (dst < dst_end) && (*src != '\0'))
	    *dst++ = *src++;
	if ((src == src_end) || (dst == dst_end)) {
	    driver_error(desc->port, XX_EINVAL);
	}
	*dst = *src++;
	/* get flags */
	dst = flags;
	dst_end = dst + 4;
	while((src < src_end) && (dst < dst_end) && (*src != '\0'))
	    *dst++ = *src++;	
	if (dst == dst_end) {
	    driver_error(desc->port, XX_EINVAL);
	    return;
	}
	*dst = '\0';

	if ((desc->fp = fopen(file, flags))==NULL) {
	    driver_error(desc->port, errno);
	    return;
	}
	driver_ok(desc->port);
	break;
    }

    case XX_WRITE: {
	int i;
	iov[1].iov_base++;
	iov[1].iov_len--;
	for(i=1; i<ev->vsize; i++) {
	    if (fwrite(iov[i].iov_base, 1, iov[i].iov_len, desc->fp) !=
		iov[i].iov_len) {
		driver_error(desc->port, errno);
		return;
	    }
	}
	driver_ok(desc->port);
	break;
    }

    case XX_READ: {
	char ch = XX_VALUE;
	int rval;
	int sz = get_int32((&iov[1])->iov_base+1);

	if ((bin = driver_alloc_binary(sz)) == NULL) {
	    driver_error(desc->port, -1);
	    return;
	}

	if ((rval = fread(bin->orig_bytes, 1, sz, desc->fp)) != sz) {
	    if (feof(desc->fp)) {
		if (rval == 0) {
		    driver_free_binary(bin);
		    driver_eof(desc->port);
		    return;
		}
		driver_output_binary(desc->port, &ch, 1,bin, 0, rval);
		driver_free_binary(bin);
		return;
	    }
	    driver_free_binary(bin);
	    driver_error(desc->port, errno);
	    return;
	}
	driver_output_binary(desc->port, &ch, 1,bin, 0, sz);
	driver_free_binary(bin);
	break;
    }

    case XX_SEEK: {
	int offs = get_int32((&iov[1])->iov_base+1);
	int w = (int) (&iov[1])->iov_base[5];
	int whence;
	switch (w) {
	case 1: whence = SEEK_SET; break;
	case 2: whence = SEEK_CUR; break;
	case 3: whence = SEEK_END; break;
	}
	if ((w = fseek(desc->fp, offs, whence)) != 0) {
	    driver_error(desc->port, errno);
	    return;
	}
	driver_ok(desc->port);
	return;
    }

    case XX_TELL: {
	int offs;
	if ((offs = ftell(desc->fp)) == -1) {
	    driver_error(desc->port, errno);
	    return;
	}
	driver_ret32(desc->port, offs);
	break;
    }

    case XX_TRUNCATE: {
        int fno;
        int offs;
	/* is this really safe? */
        if (fflush(desc->fp) != 0) {
	    driver_error(desc->port, errno);
	    return;
	}
	if ((offs = ftell(desc->fp)) == -1) {
	    driver_error(desc->port, errno);
	    return;
	}
        fno = fileno(desc->fp);
#ifdef WIN32
	if (SetEndOfFile((HANDLE)fno) !=  0) {
	    driver_error(desc->port, GetLastError());
	    return;
	}
#else
        if (ftruncate(fno, offs) == -1) {
	    driver_error(desc->port, errno);
	    return;
	}
#endif
	driver_ok(desc->port);
	return;
    }

    case XX_FLUSH:
	if (fflush(desc->fp) != 0)
	    driver_error(desc->port, errno);
	else
	    driver_ok(desc->port);
	break;

    case XX_OEOF:
	if (feof(desc->fp))
	    driver_ret32(desc->port, 1);
	else
	    driver_ret32(desc->port,0);
	break;

    case XX_ERROR:
	if (ferror(desc->fp))
	    driver_ret32(desc->port, 1);
	else
	    driver_ret32(desc->port,0);
	break;

    case XX_GETC: {
	int ch;
	if ((ch = getc(desc->fp)) == EOF) {
	    if (feof(desc->fp)) {
		driver_eof(desc->port);
		return;
	    }
	    driver_error(desc->port, errno);
	    return;
	}
	driver_ret32(desc->port, ch);
	break;
    }

    case XX_SET_LINEBUF_SIZE: {
	int sz = get_int32((&iov[1])->iov_base+1);
	desc->linebuf_size = sz;
	driver_ok(desc->port);
	break;
    }

    case XX_GETS:
    case XX_GETS2: {
	int rval;
	long cpos1, cpos2;
	char header;
	
	if ((bin = driver_alloc_binary(desc->linebuf_size)) == NULL) {
	    driver_error(desc->port, -1);
	    return;
	}

	if ((cpos1 = ftell(desc->fp)) == -1) {
	    driver_free_binary(bin);
	    driver_error(desc->port, errno);
	    return;
	}

	if ((fgets(bin->orig_bytes, desc->linebuf_size,
		   desc->fp)) == NULL) {
	    driver_free_binary(bin);
	    if (feof(desc->fp)) {
		driver_eof(desc->port);
		return;
	    }
	    driver_error(desc->port, errno);
	    return;
	}
	if ((cpos2 = ftell(desc->fp)) == -1) {
	    driver_free_binary(bin);
	    driver_error(desc->port, errno);
	    return;
	}
	rval = cpos2 - cpos1;

	if (bin->orig_bytes[rval-1] == '\n' &&
	    bin->orig_bytes[rval] == 0) {
	    header = XX_FLINE;
	    /* GETS keep newline, GETS2 remove newline */
	    rval = rval - ((&iov[1])->iov_base[0] == XX_GETS ? 0 : 1);
	}
	else
	    header = XX_NOLINE;
	driver_output_binary(desc->port, &header, 1,bin, 0, rval);
	driver_free_binary(bin);
	break;
    }

    case XX_UNGETC: {
	int ch = (&iov[1])->iov_base[1];
	if (ungetc(ch, desc->fp) == EOF)
	    driver_error(desc->port, errno);
	else
	    driver_ok(desc->port);
	break;
    }
    
    default:
#ifdef DEBUG
	fprintf(stderr, "Unknown opcode %c\n\r", ((&iov[1])->iov_base[0]));
#endif
	driver_error(desc->port, XX_EINVAL);
	break;
    }
	
	
}