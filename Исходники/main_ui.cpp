void
make_window_banks ()
{

  int i, j, x, y, num;
  int elw, elh;

  elw = 176 * gui.BankWindow->w () / 800;
  elh = 24 * gui.BankWindow->h () / 600;



  gui.ob->begin ();

  x = 40;
  y = 10;
  num = 0;

  for (i = 1; i < 21; i++)
    {
      y += elh + 2;

      for (j = 1; j < 5; j++)
	{

	  Fl_Button *butX =
	    new Fl_Button (x + 1, y + 1, elw, elh, Banco[num].Name);
	  butX->type (0);
	  butX->color (FL_BLUE);
	  butX->box (FL_FLAT_BOX);
	  butX->selection_color (FL_RED);
	  butX->labelsize (14);
	  butX->align (68 | FL_ALIGN_INSIDE);
	  butX->user_data ((void *) (num));
	  butX->value (0);
	  butX->callback ((Fl_Callback *) preset_click);
	  gui.ob->add (butX);

	  x += elw + 4;
	  num++;

	}
      x = 40;

    }


  gui.ob->end ();

  gui.made = 1;

}