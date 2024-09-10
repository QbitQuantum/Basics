int find_special_key(const char_u **srcp, const size_t src_len, int *const modp,
                     const bool keycode, const bool keep_x_key,
                     const bool in_string)
{
  const char_u *last_dash;
  const char_u *end_of_name;
  const char_u *src;
  const char_u *bp;
  const char_u *const end = *srcp + src_len - 1;
  int modifiers;
  int bit;
  int key;
  uvarnumber_T n;
  int l;

  if (src_len == 0) {
    return 0;
  }

  src = *srcp;
  if (src[0] != '<') {
    return 0;
  }

  // Find end of modifier list
  last_dash = src;
  for (bp = src + 1; bp <= end && (*bp == '-' || ascii_isident(*bp)); bp++) {
    if (*bp == '-') {
      last_dash = bp;
      if (bp + 1 <= end) {
        l = utfc_ptr2len_len(bp + 1, (int)(end - bp) + 1);
        // Anything accepted, like <C-?>.
        // <C-"> or <M-"> are not special in strings as " is
        // the string delimiter. With a backslash it works: <M-\">
        if (end - bp > l && !(in_string && bp[1] == '"') && bp[2] == '>') {
          bp += l;
        } else if (end - bp > 2 && in_string && bp[1] == '\\'
                   && bp[2] == '"' && bp[3] == '>') {
          bp += 2;
        }
      }
    }
    if (end - bp > 3 && bp[0] == 't' && bp[1] == '_') {
      bp += 3;  // skip t_xx, xx may be '-' or '>'
    } else if (end - bp > 4 && STRNICMP(bp, "char-", 5) == 0) {
      vim_str2nr(bp + 5, NULL, &l, STR2NR_ALL, NULL, NULL, 0);
      bp += l + 5;
      break;
    }
  }

  if (bp <= end && *bp == '>') {  // found matching '>'
    end_of_name = bp + 1;

    /* Which modifiers are given? */
    modifiers = 0x0;
    for (bp = src + 1; bp < last_dash; bp++) {
      if (*bp != '-') {
        bit = name_to_mod_mask(*bp);
        if (bit == 0x0) {
          break;                // Illegal modifier name
        }
        modifiers |= bit;
      }
    }

    // Legal modifier name.
    if (bp >= last_dash) {
      if (STRNICMP(last_dash + 1, "char-", 5) == 0
          && ascii_isdigit(last_dash[6])) {
        // <Char-123> or <Char-033> or <Char-0x33>
        vim_str2nr(last_dash + 6, NULL, NULL, STR2NR_ALL, NULL, &n, 0);
        key = (int)n;
      } else {
        int off = 1;

        // Modifier with single letter, or special key name.
        if (in_string && last_dash[1] == '\\' && last_dash[2] == '"') {
          off = 2;
        }
        l = mb_ptr2len(last_dash + 1);
        if (modifiers != 0 && last_dash[l + 1] == '>') {
          key = PTR2CHAR(last_dash + off);
        } else {
          key = get_special_key_code(last_dash + off);
          if (!keep_x_key) {
            key = handle_x_keys(key);
          }
        }
      }

      // get_special_key_code() may return NUL for invalid
      // special key name.
      if (key != NUL) {
        // Only use a modifier when there is no special key code that
        // includes the modifier.
        key = simplify_key(key, &modifiers);

        if (!keycode) {
          // don't want keycode, use single byte code
          if (key == K_BS) {
            key = BS;
          } else if (key == K_DEL || key == K_KDEL) {
            key = DEL;
          }
        }

        // Normal Key with modifier:
        // Try to make a single byte code (except for Alt/Meta modifiers).
        if (!IS_SPECIAL(key)) {
          key = extract_modifiers(key, &modifiers);
        }

        *modp = modifiers;
        *srcp = end_of_name;
        return key;
      }
    }
  }
  return 0;
}