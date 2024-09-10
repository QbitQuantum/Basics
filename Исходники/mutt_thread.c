/**
 * mutt_draw_tree - Draw a tree of threaded emails
 * @param ctx Mailbox
 *
 * Since the graphics characters have a value >255, I have to resort to using
 * escape sequences to pass the information to print_enriched_string().  These
 * are the macros MUTT_TREE_* defined in mutt.h.
 *
 * ncurses should automatically use the default ASCII characters instead of
 * graphics chars on terminals which don't support them (see the man page for
 * curs_addch).
 */
void mutt_draw_tree(struct Context *ctx)
{
  char *pfx = NULL, *mypfx = NULL, *arrow = NULL, *myarrow = NULL, *new_tree = NULL;
  enum TreeChar corner = (C_Sort & SORT_REVERSE) ? MUTT_TREE_ULCORNER : MUTT_TREE_LLCORNER;
  enum TreeChar vtee = (C_Sort & SORT_REVERSE) ? MUTT_TREE_BTEE : MUTT_TREE_TTEE;
  int depth = 0, start_depth = 0, max_depth = 0, width = C_NarrowTree ? 1 : 2;
  struct MuttThread *nextdisp = NULL, *pseudo = NULL, *parent = NULL, *tree = ctx->tree;

  /* Do the visibility calculations and free the old thread chars.
   * From now on we can simply ignore invisible subtrees */
  calculate_visibility(ctx, &max_depth);
  pfx = mutt_mem_malloc(width * max_depth + 2);
  arrow = mutt_mem_malloc(width * max_depth + 2);
  while (tree)
  {
    if (depth)
    {
      myarrow = arrow + (depth - start_depth - (start_depth ? 0 : 1)) * width;
      if (depth && (start_depth == depth))
        myarrow[0] = nextdisp ? MUTT_TREE_LTEE : corner;
      else if (parent->message && !C_HideLimited)
        myarrow[0] = MUTT_TREE_HIDDEN;
      else if (!parent->message && !C_HideMissing)
        myarrow[0] = MUTT_TREE_MISSING;
      else
        myarrow[0] = vtee;
      if (width == 2)
      {
        myarrow[1] = pseudo ? MUTT_TREE_STAR :
                              (tree->duplicate_thread ? MUTT_TREE_EQUALS : MUTT_TREE_HLINE);
      }
      if (tree->visible)
      {
        myarrow[width] = MUTT_TREE_RARROW;
        myarrow[width + 1] = 0;
        new_tree = mutt_mem_malloc((2 + depth * width));
        if (start_depth > 1)
        {
          strncpy(new_tree, pfx, (start_depth - 1) * width);
          mutt_str_strfcpy(new_tree + (start_depth - 1) * width, arrow,
                           (1 + depth - start_depth) * width + 2);
        }
        else
          mutt_str_strfcpy(new_tree, arrow, 2 + depth * width);
        tree->message->tree = new_tree;
      }
    }
    if (tree->child && depth)
    {
      mypfx = pfx + (depth - 1) * width;
      mypfx[0] = nextdisp ? MUTT_TREE_VLINE : MUTT_TREE_SPACE;
      if (width == 2)
        mypfx[1] = MUTT_TREE_SPACE;
    }
    parent = tree;
    nextdisp = NULL;
    pseudo = NULL;
    do
    {
      if (tree->child && tree->subtree_visible)
      {
        if (tree->deep)
          depth++;
        if (tree->visible)
          start_depth = depth;
        tree = tree->child;

        /* we do this here because we need to make sure that the first child thread
         * of the old tree that we deal with is actually displayed if any are,
         * or we might set the parent variable wrong while going through it. */
        while (!tree->subtree_visible && tree->next)
          tree = tree->next;
      }
      else
      {
        while (!tree->next && tree->parent)
        {
          if (tree == pseudo)
            pseudo = NULL;
          if (tree == nextdisp)
            nextdisp = NULL;
          if (tree->visible)
            start_depth = depth;
          tree = tree->parent;
          if (tree->deep)
          {
            if (start_depth == depth)
              start_depth--;
            depth--;
          }
        }
        if (tree == pseudo)
          pseudo = NULL;
        if (tree == nextdisp)
          nextdisp = NULL;
        if (tree->visible)
          start_depth = depth;
        tree = tree->next;
        if (!tree)
          break;
      }
      if (!pseudo && tree->fake_thread)
        pseudo = tree;
      if (!nextdisp && tree->next_subtree_visible)
        nextdisp = tree;
    } while (!tree->deep);
  }

  FREE(&pfx);
  FREE(&arrow);
}