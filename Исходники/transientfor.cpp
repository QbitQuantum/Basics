bool
compiz::X11TransientForReader::isGroupTransientFor (unsigned int clientLeader)
{
  Window        serverClientLeader = None;
  Window        ancestor           = getAncestor ();
  unsigned long nItems, nLeft;
  int           actualFormat;
  Atom          actualType;
  void          *prop;
  std::vector<std::string> strings;
  std::list<Atom>   atoms;

  if (!clientLeader ||
      !priv->mXid)

  if (XGetWindowProperty (priv->mDpy, priv->mXid, wmClientLeader, 0L, 2L, false,
                          XA_WINDOW, &actualType, &actualFormat, &nItems, &nLeft, (unsigned char **)&prop) == Success)
  {
    if (actualType == XA_WINDOW && actualFormat == 32 && nLeft == 0 && nItems == 1)
    {
      Window *data = static_cast <Window *> (prop);

      serverClientLeader = *data;
    }

    XFree (prop);
  }

  /* Check if the returned client leader matches
     * the requested one */
  if (serverClientLeader == clientLeader &&
      clientLeader != priv->mXid)
  {
    if (ancestor == None || ancestor == DefaultRootWindow (priv->mDpy))
    {
	    Atom wmWindowType = XInternAtom (priv->mDpy, "_NET_WM_WINDOW_TYPE", 0);

	    /* We need to get some common type strings */
	    strings.push_back ("_NET_WM_WINDOW_TYPE_UTILITY");
	    strings.push_back ("_NET_WM_WINDOW_TYPE_TOOLBAR");
	    strings.push_back ("_NET_WM_WINDOW_TYPE_MENU");
	    strings.push_back ("_NET_WM_WINDOW_TYPE_DIALOG");

      for (std::string &s : strings)
	    {
        atoms.push_back (XInternAtom (priv->mDpy, s.c_str (), 0));
	    }

	    const unsigned int atomsSize = atoms.size ();

	    /* Now get the window type and check to see if this is a type that we
      * should consider to be part of a window group by this client leader */

	    if (XGetWindowProperty (priv->mDpy, priv->mXid, wmWindowType, 0L, 15L, false,
                              XA_ATOM, &actualType, &actualFormat, &nItems, &nLeft, (unsigned char **)&prop) == Success)
      {
        if (actualType == XA_ATOM && actualFormat == 32 && nLeft == 0 && nItems)
        {
          Atom *data = static_cast <Atom *> (prop);

          while (nItems--)
          {
            atoms.remove (*data++);
          }
        }
	    }

	    /* Means something was found */
	    if (atomsSize != atoms.size ())
        return true;
    }
  }

  return false;
}