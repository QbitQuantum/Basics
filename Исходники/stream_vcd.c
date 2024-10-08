static int open_s(stream_t *stream,int mode, void* opts, int* file_format) {
  struct stream_priv_s* p = opts;
  int ret,ret2,f,sect,tmp;
  mp_vcd_priv_t* vcd;
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
  int bsize = VCD_SECTOR_SIZE;
#endif
#if defined(__MINGW32__) || defined(__CYGWIN__)
  HANDLE hd;
  char device[] = "\\\\.\\?:";
#endif
#if defined(__OS2__)
  char device[] = "X:";
  HFILE hcd;
  ULONG ulAction;
  ULONG rc;
#endif

  if(mode != STREAM_READ
#if defined(__MINGW32__) || defined(__CYGWIN__)
      || GetVersion() > 0x80000000 // Win9x
#endif
      ) {
    m_struct_free(&stream_opts,opts);
    return STREAM_UNSUPPORTED;
  }

  if (!p->device) {
    if(cdrom_device)
      p->device = strdup(cdrom_device);
    else
      p->device = strdup(DEFAULT_CDROM_DEVICE);
  }

#if defined(__MINGW32__) || defined(__CYGWIN__)
  device[4] = p->device[0];
  /* open() can't be used for devices so do it the complicated way */
  hd = CreateFile(device, GENERIC_READ, FILE_SHARE_READ, NULL,
	  OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
  f = _open_osfhandle((long)hd, _O_RDONLY);
#elif defined(__OS2__)
  device[0] = p->device[0];
  rc = DosOpen(device, &hcd, &ulAction, 0, FILE_NORMAL,
               OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW,
               OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE | OPEN_FLAGS_DASD,
               NULL);
  f = rc ? -1 : hcd;
#else
  f=open(p->device,O_RDONLY);
#endif
  if(f<0){
    mp_tmsg(MSGT_OPEN,MSGL_ERR,"CD-ROM Device '%s' not found.\n",p->device);
    m_struct_free(&stream_opts,opts);
    return STREAM_ERROR;
  }

  vcd = vcd_read_toc(f);
  if(!vcd) {
    mp_msg(MSGT_OPEN,MSGL_ERR,"Failed to get cd toc\n");
    close(f);
    m_struct_free(&stream_opts,opts);
    return STREAM_ERROR;
  }
  ret2=vcd_get_track_end(vcd,p->track);
  if(ret2<0){
      mp_msg(MSGT_OPEN, MSGL_ERR, "%s (get)\n",
             mp_gtext("Error selecting VCD track."));
    close(f);
    free(vcd);
    m_struct_free(&stream_opts,opts);
    return STREAM_ERROR;
  }
  ret=vcd_seek_to_track(vcd,p->track);
  if(ret<0){
      mp_msg(MSGT_OPEN, MSGL_ERR, "%s (seek)\n",
             mp_gtext("Error selecting VCD track."));
    close(f);
    free(vcd);
    m_struct_free(&stream_opts,opts);
    return STREAM_ERROR;
  }
  /* search forward up to at most 3 seconds to skip leading margin */
  sect = ret / VCD_SECTOR_DATA;
  for (tmp = sect; tmp < sect + 3 * 75; tmp++) {
    char mem[VCD_SECTOR_DATA];
    //since MPEG packs are block-aligned we stop discarding sectors if they are non-null
    if (vcd_read(vcd, mem) != VCD_SECTOR_DATA || mem[2] || mem[3])
      break;
  }
  mp_msg(MSGT_OPEN, MSGL_DBG2, "%d leading sectors skipped\n", tmp - sect);
  vcd_set_msf(vcd, tmp);
  ret = tmp * VCD_SECTOR_DATA;

  mp_msg(MSGT_OPEN,MSGL_V,"VCD start byte position: 0x%X  end: 0x%X\n",ret,ret2);

#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
  if (ioctl (f, CDRIOCSETBLOCKSIZE, &bsize) == -1) {
    mp_msg(MSGT_OPEN,MSGL_WARN,"Error in CDRIOCSETBLOCKSIZE");
  }
#endif

  stream->fd = f;
  stream->type = STREAMTYPE_VCD;
  stream->sector_size = VCD_SECTOR_DATA;
  stream->start_pos=ret;
  stream->end_pos=ret2;
  stream->priv = vcd;

  stream->fill_buffer = fill_buffer;
  stream->seek = seek;
  stream->close = close_s;
  *file_format = DEMUXER_TYPE_MPEG_PS;

  m_struct_free(&stream_opts,opts);
  return STREAM_OK;
}