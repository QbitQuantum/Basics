static void LayoutOnEscape ()
	{ if (try_and_replace_rule (layout_rule, layout_dir))
	     { XtPopdown (layout_popup);
	       Escape ();
	     }
	  else
	     { StartArgs;
	       SetArg (XtNlabel, tuple_error_buffer);
	       XtSetValues (layout_error, UseArgs);
	       StartArgs;
	       SetArg (XtNeditable, True);
	       XtSetValues (layout_edit, UseArgs);
	     };
	};