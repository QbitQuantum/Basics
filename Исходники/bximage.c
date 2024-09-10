int main (int argc, char *argv[])
{
  Bit64s sectors = 0;
  char filename[256];
  char bochsrc_line[256];

  WRITE_IMAGE write_function=NULL;
#ifdef WIN32
  WRITE_IMAGE_WIN32 writefn_win32=NULL;
#endif
 
  if (!parse_cmdline (argc, argv))
    myexit(1);

  print_banner ();
  if (bx_interactive) {
    if (ask_menu (fdhd_menu, fdhd_n_choices, fdhd_choices, bx_hdimage, &bx_hdimage) < 0)
      fatal (EOF_ERR);
  }
  if (bx_hdimage) {
    unsigned int cyl;
    int hdsize, heads=16, spt=63;
    int mode;

    if (bx_interactive) {
      if (ask_menu (hdmode_menu, hdmode_n_choices, hdmode_choices, bx_hdimagemode, &mode) < 0)
        fatal (EOF_ERR);
      if (ask_int ("\nEnter the hard disk size in megabytes, between 1 and 129023\n", 1, 129023, bx_hdsize, &hdsize) < 0)
        fatal (EOF_ERR);
    } else {
      mode = bx_hdimagemode;
      hdsize = bx_hdsize;
    }
    cyl = (unsigned int) (hdsize*1024.0*1024.0/16.0/63.0/512.0);
    assert (cyl < 262144);
    sectors = cyl*heads*spt;
    printf ("\nI will create a '%s' hard disk image with\n", hdmode_choices[mode]);
    printf ("  cyl=%d\n", cyl);
    printf ("  heads=%d\n", heads);
    printf ("  sectors per track=%d\n", spt);
    printf ("  total sectors=" FMT_LL "d\n", sectors);
    printf ("  total size=%.2f megabytes\n", (float)(Bit64s)(sectors/2)/1024.0);
    if (bx_interactive) {
      if (!strlen(bx_filename)) strcpy(bx_filename, "c.img");
      if (ask_string ("\nWhat should I name the image?\n", bx_filename, filename) < 0)
        fatal (EOF_ERR);
    } else {
      strcpy(filename, bx_filename);
    }

    sprintf (bochsrc_line, "ata0-master: type=disk, path=\"%s\", mode=%s, cylinders=%d, heads=%d, spt=%d", filename, hdmode_choices[mode], cyl, heads, spt);

    switch (mode) {
      case 1:
        write_function=make_sparse_image;
        break;
      case 2:
        write_function=make_growing_image;
        break;
      default:
#ifdef WIN32
        writefn_win32=make_flat_image_win32;
#else
        write_function=make_flat_image;
#endif
      }
  } else {
    int fdsize, cyl=0, heads=0, spt=0;
    if (bx_interactive) {
      if (ask_menu (fdsize_menu, fdsize_n_choices, fdsize_choices, bx_fdsize_idx, &fdsize) < 0)
        fatal (EOF_ERR);
    } else {
      fdsize = bx_fdsize_idx;
    }
    switch (fdsize) {
      case 0: cyl=40; heads=1; spt=8; break;  /* 0.16 meg */
      case 1: cyl=40; heads=1; spt=9; break;  /* 0.18 meg */
      case 2: cyl=40; heads=2; spt=8; break;  /* 0.32 meg */
      case 3: cyl=40; heads=2; spt=9; break;  /* 0.36 meg */
      case 4: cyl=80; heads=2; spt=9; break;  /* 0.72 meg */
      case 5: cyl=80; heads=2; spt=15; break; /* 1.2 meg */
      case 6: cyl=80; heads=2; spt=18; break; /* 1.44 meg */
      case 7: cyl=80; heads=2; spt=21; break; /* 1.68 meg */
      case 8: cyl=82; heads=2; spt=21; break; /* 1.72 meg */
      case 9: cyl=80; heads=2; spt=36; break; /* 2.88 meg */
      default:
        fatal ("ERROR: fdsize out of range");
    }
    sectors = cyl*heads*spt;
    printf ("I will create a floppy image with\n");
    printf ("  cyl=%d\n", cyl);
    printf ("  heads=%d\n", heads);
    printf ("  sectors per track=%d\n", spt);
    printf ("  total sectors=" FMT_LL "d\n", sectors);
    printf ("  total bytes=" FMT_LL "d\n", sectors*512);
    if (bx_interactive) {
      if (!strlen(bx_filename)) strcpy(bx_filename, "a.img");
      if (ask_string ("\nWhat should I name the image?\n", bx_filename, filename) < 0)
        fatal (EOF_ERR);
    } else {
      strcpy(filename, bx_filename);
    }
    sprintf (bochsrc_line, "floppya: image=\"%s\", status=inserted", filename);

    write_function=make_flat_image;
  }
  if (sectors < 1)
    fatal ("ERROR: Illegal disk size!");
  if (strlen (filename) < 1)
    fatal ("ERROR: Illegal filename");
#ifdef WIN32
  if (writefn_win32 != NULL) {
    make_image_win32 (sectors, filename, writefn_win32);
  }
  else
#endif
  {
    make_image (sectors, filename, write_function);
  }
  printf ("\nI wrote " FMT_LL "u bytes to ", sectors*512);
  printf ("%s.\n", filename);
  printf ("\nThe following line should appear in your bochsrc:\n");
  printf ("  %s\n", bochsrc_line);
#ifdef WIN32
  if (OpenClipboard(NULL)) {
    HGLOBAL hgClip;
    EmptyClipboard();
    hgClip = GlobalAlloc(GMEM_DDESHARE, (strlen(bochsrc_line) + 1));
    strcpy((char *)GlobalLock(hgClip), bochsrc_line);
    GlobalUnlock(hgClip);
    SetClipboardData(CF_TEXT, hgClip);
    CloseClipboard();
    printf("(The line is stored in your windows clipboard, use CTRL-V to paste)\n");
  }
#endif
  myexit(0);

  // make picky compilers (c++, gcc) happy,
  // even though we leave via 'myexit' just above
  return 0;
}