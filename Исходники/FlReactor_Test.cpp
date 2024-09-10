int run_main (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("FlReactor_Test"));

  Fl_Window window (300, 370);

  Test_Window tw (10, 75, window.w () - 20, window.h ()-90);
  window.resizable (&tw);

  Fl_Hor_Slider slider (60, 5, window.w () - 70, 30, "Sides:");
  slider.align (FL_ALIGN_LEFT);
  slider.callback (sides_cb, &tw);
  slider.value (tw.sides ());
  slider.step (1);
  slider.bounds (3, 10);

  ACE_FlReactor reactor;
  ACE_Reactor r (&reactor);

  Fl_Box *box = new Fl_Box (FL_UP_BOX, 10, 40,
                            window.w () - 20, 30,
                            "Setting up");
  box->labelfont (FL_BOLD);

  Acceptor acceptor (&tw, box);

  ACE_INET_Addr address;

  if (acceptor.open (address, &r) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "open acceptor"),
                      -1);

  acceptor.acceptor ().get_local_addr (address);

  const int bufsiz = 128;
  char buf[bufsiz];

  address.addr_to_string (buf, bufsiz, 0);

  char msg[2 * bufsiz];
  ACE_OS::sprintf (msg, "Listening on <%s>\n", buf);

  box->label (msg);
  box->redraw ();

  window.end ();
  window.show (argc, argv);
  tw.show ();

  return Fl::run ();

  ACE_END_TEST;
}