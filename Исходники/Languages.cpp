static void edit_lang(int nn) {
  int i1;
  languagerec *n;

  out->Cls();
  bool done = false;
  int cp = 0;
  n = &(languages[nn]);
  out->SetColor(Scheme::NORMAL);

  Printf("Language name  : %s\n", n->name);
  Printf("Data Directory : %s\n", n->dir);
  Printf("Menu Directory : %s\n", n->mdir);
  out->SetColor(Scheme::PROMPT);
  Puts("\n<ESC> when done.\n\n");
  out->SetColor(Scheme::NORMAL);
  do {
    out->GotoXY(17, cp);
    switch (cp) {
    case 0:
      editline(n->name, sizeof(n->name) - 1, ALL, &i1, "");
      trimstr(n->name);
#ifdef WHY
      ss = strchr(n->name, ' ');
      if (ss) {
        *ss = 0;
      }
#endif
      Puts(n->name);
      Puts("                  ");
      break;
    case 1:
      editline(n->dir, 60, EDITLINE_FILENAME_CASE, &i1, "");
      trimstrpath(n->dir);
      Puts(n->dir);
      break;
    case 2:
      editline(n->mdir, 60, EDITLINE_FILENAME_CASE, &i1, "");
      trimstrpath(n->mdir);
      Puts(n->mdir);
      break;
    }
    cp = GetNextSelectionPosition(0, 2, cp, i1);
    if (i1 == DONE) {
      done = true;
    }
  } while (!done);
}