void __declspec(dllexport) LangDialog(HWND hwndParent, int string_size, 
                                      char *variables, stack_t **stacktop)
{
  g_hwndParent=hwndParent;
  EXDLL_INIT();

  {
    int i;
    int doauto = 0;
    BOOL pop_empty_string = FALSE;

    // get texts
    if (popstring(g_wndtitle)) return;
    if (popstring(g_wndtext)) return;

    // get flags
    if (popstring(temp)) return;

    // parse flags
    {
      char *p=temp;
      while (*p)
      {
        if (*p == 'A') doauto=1; // parse auto count flag
        if (*p == 'F') dofont=1; // parse font flag
        if (*p == 'C') docp=1;   // parse codepage flag
        p++;
      }
    }
 
    if (doauto) {
      // automatic language count
      stack_t *th;
      langs_num=0;
      th=(*g_stacktop);
      while (th && th->text[0]) {
        langs_num++;
        th = th->next;
      }
      if (!th) return;
      if (docp)
        langs_num /= 3;
      else
        langs_num /= 2;
      pop_empty_string = TRUE;
    } else {
      // use counts languages
      langs_num = myatou(temp);
    }

    // zero languages?
    if (!langs_num) return;

    // initialize visible languages count
    visible_langs_num = 0;

    // allocate language struct
    langs = (struct lang *)GlobalAlloc(GPTR, langs_num*sizeof(struct lang));
    if (!langs) return;

    // fill language struct
    for (i = 0; i < langs_num; i++) {
      if (popstring(temp)) { visible_langs_num = 0; break; }
      langs[visible_langs_num].name = GlobalAlloc(GPTR, lstrlen(temp)+1);
      if (!langs[visible_langs_num].name) { visible_langs_num = 0; break; }
      lstrcpy(langs[visible_langs_num].name, temp);

      if (popstring(temp)) { visible_langs_num = 0; break; }
      langs[visible_langs_num].id = GlobalAlloc(GPTR, lstrlen(temp)+1);
      if (!langs[visible_langs_num].id) { visible_langs_num = 0; break; }
      lstrcpy(langs[visible_langs_num].id, temp);

      if (docp)
      {
        if (popstring(temp)) { visible_langs_num = 0; break; }
        langs[visible_langs_num].cp = myatou(temp);
      }

      if (!docp || langs[visible_langs_num].cp == GetACP() || langs[visible_langs_num].cp == 0)
      {
        visible_langs_num++;
      }
      else
      {
        GlobalFree(langs[visible_langs_num].name);
        GlobalFree(langs[visible_langs_num].id);
      }
    }

    // pop the empty string to keep the stack clean
    if (pop_empty_string) {
      if (popstring(temp)) {
        visible_langs_num = 0;
      }
    }

    // start dialog
    if (visible_langs_num > 1)
    {
      DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG), 0, DialogProc);
    }
    else if (visible_langs_num == 0)
    {
      pushstring("");
    }
    else
    {
      pushstring(langs[0].id);
    }

    // free structs
    for (i = 0; i < visible_langs_num; i++) {
      if (langs[i].name) GlobalFree(langs[i].name);
      if (langs[i].id) GlobalFree(langs[i].id);
    }
    GlobalFree(langs);
  }
}