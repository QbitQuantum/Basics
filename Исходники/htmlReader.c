int
getText (struct doc_descriptor *desc, UChar * buf, int size)
{
  struct meta *meta = NULL;
  char buf2[BUFSIZE];
  UErrorCode err;
  char *src;
  UChar *dest, esc[3];
  UChar name[1024], value[1024];
  int len, i, isMarkup, isJavascript, isMeta, l, j;
  int dangerousCut, fini, r, offset, endOfFile, space_added;

  space_added = 0;
  l = 0;
  fini = 0;
  endOfFile = 0;
  isJavascript = 0;
  dangerousCut = 0;
  isMarkup = 0;
  isMeta = 0;
  len = read (desc->fd, buf2, BUFSIZE);
  while (!fini && len > 0 && 2*l < size - 2)
    {

      /* consuming buffer */
      for (i = 0; 2*l < size - 2 && i < len && !dangerousCut && !fini; i++)
        {

          /* end of buffer are possible points of failure
             if a markup or a token is cut, it will not be
             parsed. */
          if (!endOfFile && i > len - 9 && (!strncmp (buf2 + i, "\x3c", 1) ||
                                            !strncmp (buf2 + i, "\x26", 1)))
            {
              dangerousCut = 1;
              break;
            }

          /* detecting end of javascript */
          if (isJavascript
              && !strncasecmp (buf2 + i, "</script>", 9))
            {
              isJavascript = 0;
              i += 9;
            }

          /* detecting new paragraph */
          if (l > 0 && !isJavascript
              && (!strncasecmp (buf2 + i, "<p", 2)
                  || !strncasecmp (buf2 + i, "<br", 3)
                  || !strncasecmp (buf2 + i, "<div", 4)))
            {
              fini = 1;
              i += 2;
              while (strncmp (buf2 + i, ">", 1))
                {
                  i++;
                }
              lseek (desc->fd, i - len, SEEK_CUR);
              break;
            }

          /* detecting begining of markup */
          if (!isJavascript && !isMarkup && !strncmp (buf2 + i, "\x3c", 1))
            {

              /* detecting begining of javascript */
              if (!strncasecmp (buf2 + i, "<script", 7))
                {
                  isJavascript = 1;

                }
              else if (!strncasecmp (buf2 + i, "<title", 6))
                {
                  err = U_ZERO_ERROR;
                  /* finding last metadata of desc */
                  if (desc->meta == NULL)
                    {
                      meta = (struct meta *) malloc (sizeof (struct meta));
                      desc->meta = meta;
                    }
                  else
                    {
                      meta = desc->meta;
                      while (meta->next != NULL)
                        {
                          meta = meta->next;
                        }
                      meta->next =
                        (struct meta *) malloc (sizeof (struct meta));
                      meta = meta->next;
                    }
                  meta->next = NULL;
                  meta->name = (UChar *) malloc (12);

                  /* filling name field */
                  meta->name_length =
                    2 * ucnv_toUChars (desc->conv, meta->name, 12, "title", 5,
                                       &err);
                  meta->name_length = u_strlen (meta->name);
                  if (U_FAILURE (err))
                    {
                      printf ("error icu\n");
                      return ERR_ICU;
                    }
                  isMeta = 1;

                }
              else if (!strncasecmp (buf2 + i, "<meta", 5))
                {
                  i += 5;
                  if (i >= size - 9)
                    {
                      strncpy (buf2, buf2 + i, len - i);
                      len =
                        read (desc->fd, buf2 + i,
                              BUFSIZE - len + i) + len - i;
                      i = 0;
                    }
                  for (; strncasecmp (buf2 + i, "name=\"", 6)  &&
                       strncmp (buf2 + i, "\x3E", 1); i++)
                    {
                      if (i >= size - 9)
                        {
                          strncpy (buf2, buf2 + i, len - i);
                          len =
                            read (desc->fd, buf2 + i,
                                  BUFSIZE - len + i) + len - i;
                          i = 0;
                        }
                    }
                  if (!strncmp (buf2 + i, "\x3E", 1))
                    {
                      continue;

                    }
                  else
                    {
                      i += 6;
                      /* get metadata name */
                      memset (name, '\x00', 2048);
                      for (j = 0; len != 0 && strncmp (buf2 + i, "\"", 1);
                           i++)
                        {
                          if (i >= size - 9)
                            {
                              strncpy (buf2, buf2 + i, len - i);
                              len =
                                read (desc->fd, buf2 + i,
                                      BUFSIZE - len + i) + len - i;
                              i = 0;
                            }
                          if (!strncmp (buf2 + i, "\x26", 1))
                            {
                              memset (esc, '\x00', 6);
                              offset = escapeChar (desc, buf2 + i, esc);
                              memcpy (name + j, esc, 2 * u_strlen (esc));
                              j += u_strlen (esc);
                              i += (offset - 1);
                            }
                          else
                            {

                              /* filling name buffer */
                              dest = name + j;
                              src = buf2 + i;
                              err = U_ZERO_ERROR;
                              ucnv_toUnicode (desc->conv, &dest, name + 1024,
                                              &src, buf2 + i + 1, NULL, FALSE,
                                              &err);
                              if (U_FAILURE (err))
                                {
                                  fprintf (stderr,
                                           "Unable to convert buffer\n");
                                  return ERR_ICU;
                                }
                              j += (dest - name - j);
                            }
                        }

                      /* get metadata value */
                      for (; strncasecmp (buf2 + i, "content=\"", 9) && strncmp (buf2 + i, "\x3E", 1); i++)
                        {
                          if (i >= size - 9)
                            {
                              strncpy (buf2, buf2 + i, len - i);
                              len =
                                read (desc->fd, buf2 + i,
                                      BUFSIZE - len + i) + len - i;
                              i = 0;
                            }
                        }
                      i += 9;
                      if (i >= size - 9)
                        {
                          strncpy (buf2, buf2 + i, len - i);
                          len =
                            read (desc->fd, buf2 + i,
                                  BUFSIZE - len + i) + len - i;
                          i = 0;
                        }
                      memset (value, '\x00', 2048);
                      for (j = 0; len != 0 && strncmp (buf2 + i, "\"", 1);
                           i++)
                        {
                          if (i >= size - 9)
                            {
                              strncpy (buf2, buf2 + i, len - i);
                              len =
                                read (desc->fd, buf2 + i,
                                      BUFSIZE - len + i) + len - i;
                              i = 0;
                            }
                          if (!strncmp (buf2 + i, "\x26", 1))
                            {
                              memset (esc, '\x00', 6);
                              offset = escapeChar (desc, buf2 + i, esc);
                              memcpy (value + j, esc, 2 * u_strlen (esc));
                              j += u_strlen (esc);
                              i += (offset - 1);
                            }
                          else
                            {

                              /* filling value buffer */
                              dest = value + j;
                              src = buf2 + i;
                              err = U_ZERO_ERROR;
                              ucnv_toUnicode (desc->conv, &dest, value + 1024,
                                              &src, buf2 + i + 1, NULL, FALSE,
                                              &err);
                              if (U_FAILURE (err))
                                {
                                  fprintf (stderr,
                                           "Unable to convert buffer\n");
                                  return ERR_ICU;
                                }
                              j += (dest - value - j);
                            }
                        }

                      /* insert metadata in list */
                      if (desc->meta == NULL)
                        {
                          meta =
                            (struct meta *) malloc (sizeof (struct meta));
                          desc->meta = meta;
                        }
                      else
                        {
                          meta = desc->meta;
                          while (meta->next != NULL)
                            {
                              meta = meta->next;
                            }
                          meta->next =
                            (struct meta *) malloc (sizeof (struct meta));
                          meta = meta->next;
                        }
                      meta->next = NULL;
                      meta->name = (UChar *) malloc (2 * u_strlen (name) + 2);
                      meta->value =
                        (UChar *) malloc (2 * u_strlen (value) + 2);
                      memset (meta->name, '\x00', 2 * u_strlen (name) + 2);
                      memset (meta->value, '\x00', 2 * u_strlen (value) + 2);
                      memcpy (meta->name, name, 2 * u_strlen (name));
                      memcpy (meta->value, value, 2 * u_strlen (value));
                      meta->name_length = u_strlen (name);
                      meta->value_length = u_strlen (value);

                      for (; strncmp (buf2 + i, "\x3E", 1); i++)
                        {
                          if (i >= size - 9)
                            {
                              strncpy (buf2, buf2 + i, len - i);
                              len =
                                read (desc->fd, buf2 + i,
                                      BUFSIZE - len + i) + len - i;
                              i = 0;
                            }
                        }
                      continue;
                    }

                }
              else
                {

                  isMarkup = 1;
                }
            }

          /* get metadata value */
          if (!isJavascript && isMeta)
            {
              for (; len != 0 && strncmp (buf2 + i, "\x3E", 1); i++)
                {
                  if (i >= size - 9)
                    {
                      strncpy (buf2, buf2 + i, len - i);
                      len =
                        read (desc->fd, buf2 + i,
                              BUFSIZE - len + i) + len - i;
                      i = 0;
                    }
                }
              i++;
              memset (value, '\x00', 2048);
              for (j = 0; len != 0 && strncmp (buf2 + i, "\x3C", 1); i++)
                {
                  if (i >= size - 9)
                    {
                      strncpy (buf2, buf2 + i, len - i);
                      len =
                        read (desc->fd, buf2 + i,
                              BUFSIZE - len + i) + len - i;
                      i = 0;
                    }
                  if (!strncmp (buf2 + i, "\x26", 1))
                    {
                      memset (esc, '\x00', 6);
                      offset = escapeChar (desc, buf2 + i, esc);
                      memcpy (value + j, esc, 2 * u_strlen (esc));
                      j += u_strlen (esc);
                      i += (offset - 1);
                    }
                  else
                    {

                      /* filling value buffer */
                      dest = value + j;
                      src = buf2 + i;
                      err = U_ZERO_ERROR;
                      ucnv_toUnicode (desc->conv, &dest, value + 1024,
                                      &src, buf2 + i + 1, NULL, FALSE, &err);
                      if (U_FAILURE (err))
                        {
                          fprintf (stderr, "Unable to convert buffer\n");
                          return ERR_ICU;
                        }
                      j += (dest - value - j);
                    }
                }
              meta->value = (UChar *) malloc (2 * (j + 1));
              memcpy (meta->value, value, 2 * u_strlen (value));
              meta->value_length = u_strlen (value);
              isMeta = 0;
              i += 7;
              continue;
            }

          /* detecting end of markup */
          if (!isJavascript && isMarkup && !strncmp (buf2 + i, "\x3e", 1))
            {
              if (!space_added && l > 0)
                {
                  buf[l] = 0x20;
                  l ++;
                  space_added = 1;
                }
              isMarkup = 0;
            }

          /* handling text */
          if (!isJavascript && !isMarkup && strncmp (buf2 + i, "\x3e", 1))
            {

              if (strncmp (buf2 + i, "\n", 1) && strncmp (buf2 + i, "\t", 1) && strncmp (buf2 + i, "\r", 1))
                {

                  /* converting tokens */
                  if (!isJavascript && !isMarkup
                      && !strncmp (buf2 + i, "\x26", 1))
                    {
                      memset (esc, '\x00', 6);
                      offset = escapeChar (desc, buf2 + i, esc);
                      if (memcmp (esc, "\x20\x00", u_strlen (esc)))
                        {
                          memcpy (buf + l, esc, 2 * u_strlen (esc));
                          l += u_strlen (esc);
                          space_added = 0;
                        }
                      else {
                        if (!space_added){
                            buf[l] = 0x20;
                            space_added = 1;
                            l++;
                        }
                      }
                      i += (offset - 1);
                    }
                  else
                    {
                      if (buf2[i] != 0x20 || !space_added){
                        /* filling output buffer */
                        dest = buf + l;
                        src = buf2 + i;
                        err = U_ZERO_ERROR;
                        ucnv_toUnicode (desc->conv, &dest, buf + size / 2,
                                        &src, buf2 + i + 1, NULL, FALSE, &err);
                        if (U_FAILURE (err))
                            {
                            fprintf (stderr, "Unable to convert buffer\n");
                            return ERR_ICU;
                            }
                        l += (dest - buf - l);
                        if (buf2[i] == 0x20) {space_added = 1;} else {space_added=0;}
                      }
                    }
                }
              else
                {
                  /* replace tabs and eol by spaces */
                  if (!space_added){
                    buf[l] = 0x20;
                    space_added = 1;
                    l++;
                  }
                }
            }
        }

      /* filling new buffer correctly */
      if (!fini)
        {
          if (dangerousCut)
            {
              r = len - i;
              strncpy (buf2, buf2 + i, r);
              len = read (desc->fd, buf2 + r, BUFSIZE - r) + r;
              if (len < 9)
                {
                  endOfFile = 1;
                }
              dangerousCut = 0;
            }
          else
            {
              len = read (desc->fd, buf2, BUFSIZE);
            }
        }

    }

  /* ending buffer properly */
  if (l > 0)
    {
      buf[l] = 0x20;
      return 2*l;
    }

  if (len == 0)
    {
      return NO_MORE_DATA;
    }

  return 2*l;
}