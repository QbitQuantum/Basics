/*!
    \internal
    Wraps the Motif dialog by setting the X window for the
    QtMotifDialog to the X window id of the dialog shell.
*/
void QtMotifDialog::realize( Widget w )
{
    // use the winid of the dialog shell, reparent any children we have
    if ( XtWindow( w ) != winId() ) {
	XSync(QtMotif::display(), FALSE);

	XtSetMappedWhenManaged( d->shell, False );

	// save the window title
	QString wtitle = windowTitle();
	if (wtitle.isEmpty()) {
 	    char *t = 0;
 	    XtVaGetValues(w, XtNtitle, &t, NULL);
 	    wtitle = QString::fromLocal8Bit(t);
	}
        setWindowTitle(QString()); // make sure setWindowTitle() works below

        QString icontext = windowIconText();
        if (icontext.isEmpty()) {
 	    char *iconName = 0;
 	    XtVaGetValues(w, XtNiconName, &iconName, NULL);
 	    icontext = QString::fromLocal8Bit(iconName);
        }
        setWindowIconText(QString()); // make sure setWindowTitle() works below

	Window newid = XtWindow(w);
	QObjectList list = children();
	for (int i = 0; i < list.size(); ++i) {
	    QWidget *widget = qobject_cast<QWidget*>(list.at(i));
	    if (!widget || widget->isWindow()) continue;

	    XReparentWindow(widget->x11Info().display(), widget->winId(), newid,
			    widget->x(), widget->y());
	}
	QApplication::syncX();

	create( newid, true, true );

	// restore the window title and icon text
 	if (!wtitle.isEmpty())
 	    setWindowTitle(wtitle);
        if (!icontext.isEmpty())
            setWindowIconText(icontext);

	// if this dialog was created without a QWidget parent, then the transient
	// for will be set to the root window, which is not acceptable.
	// instead, set it to the window id of the shell's parent
	if ( ! parent() && XtParent( d->shell ) )
	    XSetTransientForHint(x11Info().display(), newid, XtWindow(XtParent(d->shell)));
    }
    QtMotif::registerWidget( this );
}