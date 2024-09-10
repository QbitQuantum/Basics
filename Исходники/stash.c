static struct stash *stash_lookup_next(pr_stash_type_t sym_type,
    const char *name, size_t namelen, int idx, unsigned int hash, void *prev) {
  struct stash *sym = NULL;
  int last_hit = 0;
  xaset_t **symbol_table = NULL;

  switch (sym_type) {
    case PR_SYM_CONF:
      symbol_table = conf_symbol_table;
      break;

    case PR_SYM_CMD:
      symbol_table = cmd_symbol_table;
      break;

    case PR_SYM_AUTH:
      symbol_table = auth_symbol_table;
      break;

    case PR_SYM_HOOK:
      symbol_table = hook_symbol_table;
      break;

    default:
      errno = EINVAL;
      return NULL;
  }

  if (symbol_table[idx]) {
    for (sym = (struct stash *) symbol_table[idx]->xas_list; sym;
        sym = sym->next) {
      if (last_hit) {
        int res;

        if (name == NULL) {
          break;
        }

        if (sym->sym_hash != hash) {
          continue;
        }

        if (sym->sym_namelen != namelen) {
          continue;
        }

        /* Try to avoid strncmp(3) if we can. */
        if (namelen >= 1) {
          char c1, c2;

          c1 = tolower((int) sym->sym_name[0]);
          c2 = tolower((int) name[0]);

          if (c1 != c2) {
            continue;
          }

          /* Special case (unlikely, but possible) */
          if (namelen == 1 &&
              c1 == '\0') {
            break;
          }
        }

        if (namelen >= 2) {
          char c1, c2;

          c1 = tolower((int) sym->sym_name[1]);
          c2 = tolower((int) name[1]);

          if (c1 != c2) {
            continue;
          }

          /* Special case */
          if (namelen == 2 &&
              c1 == '\0') {
            break;
          }
        }

        res = strncasecmp(sym->sym_name + 2, name + 2, namelen - 2);
        if (res == 0) {
          break;
        }
      }

      if (sym->ptr.sym_generic == prev) {
        last_hit++;
      }
    }
  }

  return sym;
}