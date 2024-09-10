GdkWindow *gdk_selection_owner_get(GdkAtom selection)
{
   GdkWindow *window;
   gchar *sel_name;

#if 0
   /* XXX Hmm, gtk selections seem to work best with this. This causes
    * gtk to always get the clipboard contents from Windows, and not
    * from the editable's own stashed-away copy.
    */
   return NULL;
#else
   if (selection != gdk_clipboard_atom)
      window = NULL;
   else {
      window = gdk_window_lookup(GetClipboardOwner());
      if (window == NULL)
         window = (GdkWindow *)GetClipboardOwner();
   }

#endif

   GDK_NOTE(DND,
            (sel_name = gdk_atom_name(selection),
             g_print("gdk_selection_owner_get: %#x (%s) = %#x\n",
                     selection, sel_name,
                     (window ? GDK_DRAWABLE_XID(window) : 0)),
             g_free(sel_name)));

   return window;
}