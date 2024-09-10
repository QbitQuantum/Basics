static void
pick_unichar (ModeInfo *mi)
{
  unicrud_configuration *bp = &bps[MI_SCREEN(mi)];
  int i;
  unsigned long min = 0;
  unsigned long max = 0x2F800;
  unsigned long last = 0;
  int retries = 0;

 AGAIN:
  bp->unichar = min + (random() % (max - min));

  if (++retries > 0xF0000 / 2)
    {
      fprintf (stderr, "%s: internal error: too many retries\n", progname);
      exit (1);
    }

  /* bp->unichar = 0x1F4A9; */

  last = 0;
  bp->charplane = "Unassigned";
  bp->charblock = "Unassigned";
  for (i = 0; i < countof(unicode_block_names); i++)
    {
      if (unicode_block_names[i].start < last)
        {
          fprintf (stderr, "%s: progname: internal error: misordered: 0x%lX\n",
                   progname, unicode_block_names[i].start);
          exit (1);
        }
      last = unicode_block_names[i].start;
      if (bp->unichar >= unicode_block_names[i].start)
        {
          if (unicode_block_names[i].name[0] == '*')
            {
              bp->charplane = unicode_block_names[i].name + 1;
              bp->charblock = "Unassigned";
            }
          else
            bp->charblock = unicode_block_names[i].name;
        }
      else
        break;
    }

  if (!strncmp (bp->charblock, "Unassigned", 10) ||
      !strncmp (bp->charblock, "Combining", 9))
    goto AGAIN;

  if (*do_block && !matches (do_block, bp->charblock))
    goto AGAIN;

  /* Skip blank characters */
  {
    XCharStruct e;
    char text[10];
    i = utf8_encode (bp->unichar, text, sizeof(text) - 1);
    text[i] = 0;
    texture_string_metrics (bp->char_font, text, &e, 0, 0);
    if (e.width < 2 || e.ascent + e.descent < 2)
      goto AGAIN;
  }

# ifdef HAVE_JWXYZ
  bp->charname = texfont_unicode_character_name (bp->char_font, bp->unichar);
# endif

  bp->color[0] = 0.5 + frand(0.5);
  bp->color[1] = 0.5 + frand(0.5);
  bp->color[2] = 0.5 + frand(0.5);
  bp->color[3] = 1;
}