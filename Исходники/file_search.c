/*
 * Initialization routine for vim_findfile().
 *
 * Returns the newly allocated search context or NULL if an error occurred.
 *
 * Don't forget to clean up by calling vim_findfile_cleanup() if you are done
 * with the search context.
 *
 * Find the file 'filename' in the directory 'path'.
 * The parameter 'path' may contain wildcards. If so only search 'level'
 * directories deep. The parameter 'level' is the absolute maximum and is
 * not related to restricts given to the '**' wildcard. If 'level' is 100
 * and you use '**200' vim_findfile() will stop after 100 levels.
 *
 * 'filename' cannot contain wildcards!  It is used as-is, no backslashes to
 * escape special characters.
 *
 * If 'stopdirs' is not NULL and nothing is found downward, the search is
 * restarted on the next higher directory level. This is repeated until the
 * start-directory of a search is contained in 'stopdirs'. 'stopdirs' has the
 * format ";*<dirname>*\(;<dirname>\)*;\=$".
 *
 * If the 'path' is relative, the starting dir for the search is either VIM's
 * current dir or if the path starts with "./" the current files dir.
 * If the 'path' is absolute, the starting dir is that part of the path before
 * the first wildcard.
 *
 * Upward search is only done on the starting dir.
 *
 * If 'free_visited' is TRUE the list of already visited files/directories is
 * cleared. Set this to FALSE if you just want to search from another
 * directory, but want to be sure that no directory from a previous search is
 * searched again. This is useful if you search for a file at different places.
 * The list of visited files/dirs can also be cleared with the function
 * vim_findfile_free_visited().
 *
 * Set the parameter 'find_what' to FINDFILE_DIR if you want to search for
 * directories only, FINDFILE_FILE for files only, FINDFILE_BOTH for both.
 *
 * A search context returned by a previous call to vim_findfile_init() can be
 * passed in the parameter "search_ctx_arg".  This context is reused and
 * reinitialized with the new parameters.  The list of already visited
 * directories from this context is only deleted if the parameter
 * "free_visited" is true.  Be aware that the passed "search_ctx_arg" is freed
 * if the reinitialization fails.
 *
 * If you don't have a search context from a previous call "search_ctx_arg"
 * must be NULL.
 *
 * This function silently ignores a few errors, vim_findfile() will have
 * limited functionality then.
 */
void *
vim_findfile_init (
    char_u *path,
    char_u *filename,
    char_u *stopdirs,
    int level,
    int free_visited,
    int find_what,
    void *search_ctx_arg,
    int tagfile,                    /* expanding names of tags files */
    char_u *rel_fname         /* file name to use for "." */
)
{
  char_u              *wc_part;
  ff_stack_T          *sptr;
  ff_search_ctx_T     *search_ctx;

  /* If a search context is given by the caller, reuse it, else allocate a
   * new one.
   */
  if (search_ctx_arg != NULL)
    search_ctx = search_ctx_arg;
  else {
    search_ctx = xcalloc(1, sizeof(ff_search_ctx_T));
  }
  search_ctx->ffsc_find_what = find_what;
  search_ctx->ffsc_tagfile = tagfile;

  /* clear the search context, but NOT the visited lists */
  ff_clear(search_ctx);

  /* clear visited list if wanted */
  if (free_visited == TRUE)
    vim_findfile_free_visited(search_ctx);
  else {
    /* Reuse old visited lists. Get the visited list for the given
     * filename. If no list for the current filename exists, creates a new
     * one. */
    search_ctx->ffsc_visited_list = ff_get_visited_list(filename,
        &search_ctx->ffsc_visited_lists_list);
    if (search_ctx->ffsc_visited_list == NULL)
      goto error_return;
    search_ctx->ffsc_dir_visited_list = ff_get_visited_list(filename,
        &search_ctx->ffsc_dir_visited_lists_list);
    if (search_ctx->ffsc_dir_visited_list == NULL)
      goto error_return;
  }

  if (ff_expand_buffer == NULL) {
    ff_expand_buffer = xmalloc(MAXPATHL);
  }

  /* Store information on starting dir now if path is relative.
   * If path is absolute, we do that later.  */
  if (path[0] == '.'
      && (vim_ispathsep(path[1]) || path[1] == NUL)
      && (!tagfile || vim_strchr(p_cpo, CPO_DOTTAG) == NULL)
      && rel_fname != NULL) {
    int len = (int)(path_tail(rel_fname) - rel_fname);

    if (!vim_isAbsName(rel_fname) && len + 1 < MAXPATHL) {
      /* Make the start dir an absolute path name. */
      STRLCPY(ff_expand_buffer, rel_fname, len + 1);
      search_ctx->ffsc_start_dir = FullName_save(ff_expand_buffer, FALSE);
    } else
      search_ctx->ffsc_start_dir = vim_strnsave(rel_fname, len);
    if (*++path != NUL)
      ++path;
  } else if (*path == NUL || !vim_isAbsName(path)) {
#ifdef BACKSLASH_IN_FILENAME
    /* "c:dir" needs "c:" to be expanded, otherwise use current dir */
    if (*path != NUL && path[1] == ':') {
      char_u drive[3];

      drive[0] = path[0];
      drive[1] = ':';
      drive[2] = NUL;
      if (vim_FullName(drive, ff_expand_buffer, MAXPATHL, TRUE) == FAIL)
        goto error_return;
      path += 2;
    } else
#endif
    if (os_dirname(ff_expand_buffer, MAXPATHL) == FAIL)
      goto error_return;

    search_ctx->ffsc_start_dir = vim_strsave(ff_expand_buffer);

#ifdef BACKSLASH_IN_FILENAME
    /* A path that starts with "/dir" is relative to the drive, not to the
     * directory (but not for "//machine/dir").  Only use the drive name. */
    if ((*path == '/' || *path == '\\')
        && path[1] != path[0]
        && search_ctx->ffsc_start_dir[1] == ':')
      search_ctx->ffsc_start_dir[2] = NUL;
#endif
  }

  /*
   * If stopdirs are given, split them into an array of pointers.
   * If this fails (mem allocation), there is no upward search at all or a
   * stop directory is not recognized -> continue silently.
   * If stopdirs just contains a ";" or is empty,
   * search_ctx->ffsc_stopdirs_v will only contain a  NULL pointer. This
   * is handled as unlimited upward search.  See function
   * ff_path_in_stoplist() for details.
   */
  if (stopdirs != NULL) {
    char_u  *walker = stopdirs;
    int dircount;

    while (*walker == ';')
      walker++;

    dircount = 1;
    search_ctx->ffsc_stopdirs_v = xmalloc(sizeof(char_u *));

    do {
      char_u  *helper;
      void    *ptr;

      helper = walker;
      ptr = xrealloc(search_ctx->ffsc_stopdirs_v,
          (dircount + 1) * sizeof(char_u *));
      search_ctx->ffsc_stopdirs_v = ptr;
      walker = vim_strchr(walker, ';');
      if (walker) {
        search_ctx->ffsc_stopdirs_v[dircount-1] =
          vim_strnsave(helper, (int)(walker - helper));
        walker++;
      } else
        /* this might be "", which means ascent till top
         * of directory tree.
         */
        search_ctx->ffsc_stopdirs_v[dircount-1] =
          vim_strsave(helper);

      dircount++;

    } while (walker != NULL);
    search_ctx->ffsc_stopdirs_v[dircount-1] = NULL;
  }

  search_ctx->ffsc_level = level;

  /* split into:
   *  -fix path
   *  -wildcard_stuff (might be NULL)
   */
  wc_part = vim_strchr(path, '*');
  if (wc_part != NULL) {
    int llevel;
    int len;
    char    *errpt;

    /* save the fix part of the path */
    search_ctx->ffsc_fix_path = vim_strnsave(path, (int)(wc_part - path));

    /*
     * copy wc_path and add restricts to the '**' wildcard.
     * The octet after a '**' is used as a (binary) counter.
     * So '**3' is transposed to '**^C' ('^C' is ASCII value 3)
     * or '**76' is transposed to '**N'( 'N' is ASCII value 76).
     * For EBCDIC you get different character values.
     * If no restrict is given after '**' the default is used.
     * Due to this technique the path looks awful if you print it as a
     * string.
     */
    len = 0;
    while (*wc_part != NUL) {
      if (len + 5 >= MAXPATHL) {
        EMSG(_(e_pathtoolong));
        break;
      }
      if (STRNCMP(wc_part, "**", 2) == 0) {
        ff_expand_buffer[len++] = *wc_part++;
        ff_expand_buffer[len++] = *wc_part++;

        llevel = strtol((char *)wc_part, &errpt, 10);
        if ((char_u *)errpt != wc_part && llevel > 0 && llevel < 255)
          ff_expand_buffer[len++] = llevel;
        else if ((char_u *)errpt != wc_part && llevel == 0)
          /* restrict is 0 -> remove already added '**' */
          len -= 2;
        else
          ff_expand_buffer[len++] = FF_MAX_STAR_STAR_EXPAND;
        wc_part = (char_u *)errpt;
        if (*wc_part != NUL && !vim_ispathsep(*wc_part)) {
          EMSG2(_(
                  "E343: Invalid path: '**[number]' must be at the end of the path or be followed by '%s'."),
              PATHSEPSTR);
          goto error_return;
        }
      } else
        ff_expand_buffer[len++] = *wc_part++;
    }
    ff_expand_buffer[len] = NUL;
    search_ctx->ffsc_wc_path = vim_strsave(ff_expand_buffer);
  } else
    search_ctx->ffsc_fix_path = vim_strsave(path);

  if (search_ctx->ffsc_start_dir == NULL) {
    /* store the fix part as startdir.
     * This is needed if the parameter path is fully qualified.
     */
    search_ctx->ffsc_start_dir = vim_strsave(search_ctx->ffsc_fix_path);
    search_ctx->ffsc_fix_path[0] = NUL;
  }

  /* create an absolute path */
  if (STRLEN(search_ctx->ffsc_start_dir)
      + STRLEN(search_ctx->ffsc_fix_path) + 3 >= MAXPATHL) {
    EMSG(_(e_pathtoolong));
    goto error_return;
  }
  STRCPY(ff_expand_buffer, search_ctx->ffsc_start_dir);
  add_pathsep(ff_expand_buffer);
  {
    size_t eb_len = STRLEN(ff_expand_buffer);
    char_u *buf = xmalloc(eb_len + STRLEN(search_ctx->ffsc_fix_path) + 1);

    STRCPY(buf, ff_expand_buffer);
    STRCPY(buf + eb_len, search_ctx->ffsc_fix_path);
    if (os_isdir(buf)) {
      STRCAT(ff_expand_buffer, search_ctx->ffsc_fix_path);
      add_pathsep(ff_expand_buffer);
    } else {
      char_u *p =  path_tail(search_ctx->ffsc_fix_path);
      char_u *wc_path = NULL;
      char_u *temp = NULL;
      int len = 0;

      if (p > search_ctx->ffsc_fix_path) {
        len = (int)(p - search_ctx->ffsc_fix_path) - 1;
        STRNCAT(ff_expand_buffer, search_ctx->ffsc_fix_path, len);
        add_pathsep(ff_expand_buffer);
      } else
        len = (int)STRLEN(search_ctx->ffsc_fix_path);

      if (search_ctx->ffsc_wc_path != NULL) {
        wc_path = vim_strsave(search_ctx->ffsc_wc_path);
        temp = xmalloc(STRLEN(search_ctx->ffsc_wc_path)
                       + STRLEN(search_ctx->ffsc_fix_path + len)
                       + 1);
      }

      if (temp == NULL || wc_path == NULL) {
        free(buf);
        free(temp);
        free(wc_path);
        goto error_return;
      }

      STRCPY(temp, search_ctx->ffsc_fix_path + len);
      STRCAT(temp, search_ctx->ffsc_wc_path);
      free(search_ctx->ffsc_wc_path);
      free(wc_path);
      search_ctx->ffsc_wc_path = temp;
    }
    free(buf);
  }

  sptr = ff_create_stack_element(ff_expand_buffer,
      search_ctx->ffsc_wc_path,
      level, 0);

  ff_push(search_ctx, sptr);
  search_ctx->ffsc_file_to_search = vim_strsave(filename);
  return search_ctx;

error_return:
  /*
   * We clear the search context now!
   * Even when the caller gave us a (perhaps valid) context we free it here,
   * as we might have already destroyed it.
   */
  vim_findfile_cleanup(search_ctx);
  return NULL;
}