// Construct free-floating window
CommandWindow::CommandWindow(FXApp* a, const FXString& name, FXString strcmd, int nblines, int nbcols) :
    DialogBox(a, name, DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE|DECOR_MAXIMIZE|DECOR_MINIMIZE|DECOR_CLOSE, 0, 0, 0, 0, 6, 6, 6, 6, 4, 4)
{
    // Get command to execute
    command = strcmd;

    // Bottom part
    FXHorizontalFrame* buttonbox = new FXHorizontalFrame(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
    new FXButton(buttonbox, _("Cl&ose"), NULL, this, ID_CLOSE, BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 20, 20, 5, 5);
    FXButton* cancelbutton = new FXButton(buttonbox, _("&Cancel"), NULL, this, ID_KILLPROCESS, BUTTON_INITIAL|BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 20, 20, 5, 5);

    // Text part
    FXHorizontalFrame* textbox = new FXHorizontalFrame(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_SUNKEN, 0, 0, 0, 0, 0, 0, 0, 0);
    text = new FXText(textbox, NULL, 0, TEXT_READONLY|TEXT_WORDWRAP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    text->setVisibleRows(nblines);
    text->setVisibleColumns(nbcols);

	appendText(_("Please wait...\n\n"));

    cancelbutton->setFocus();

    // Initialize variables
    pid = -1;
    killed = false;
    closed = false;
}