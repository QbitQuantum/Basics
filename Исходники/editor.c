void Editor::InsertDialog (Glyph* g) { 
    ManagedWindow* w = GetWindow();
    if (w != nil) w->deiconify();
    TransientWindow* dialog = nil;
    for (ListItr(EditorImpl) i(*_impl); i.more(); i.next()) {
	TransientWindow* t = i.cur();
	if (t->glyph() == g) {
	    dialog = t;
	    break;
	}
    }
    if (dialog == nil) {
	dialog = new TransientWindow(g);
	_impl->prepend(dialog);
    }
    dialog->transient_for(w);
    dialog->place(
	w->left() + w->width() * 0.5, w->bottom() + w->height() * 0.5
    );
    dialog->align(0.5, 0.5);
    dialog->map();
}