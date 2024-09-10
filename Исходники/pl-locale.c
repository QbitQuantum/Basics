static wchar_t *
ls_to_wcs(const char *in, const wchar_t *on_error)
{ wchar_t buf[LSTR_MAX];
  mbstate_t state;

  memset(&state, 0, sizeof(state));
  mbsrtowcs(buf, &in, LSTR_MAX, &state);
  if ( in == NULL )
  { return wcsdup(buf);
  } else
  { Sdprintf("Illegal locale string: %s\n", in);
    return wcsdup(on_error);
  }
}