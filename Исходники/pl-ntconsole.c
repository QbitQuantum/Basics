static int
flush_ansi(ansi_stream *as)
{ size_t written = 0;

  while ( written < as->buffered )
  { BOOL rc;
    DWORD done;

    rc = WriteConsoleW(as->hConsole,
		       &as->buffer[written],
		       (DWORD)(as->buffered-written),
		       &done,
		       NULL);

    if ( rc )
    { written += done;
    } else
    { as->buffered = 0;
      return -1;
    }
  }

  as->buffered = 0;
  return 0;
}