// ===========================================================================
// method definitions
// ===========================================================================
GUIDialog_EditViewport::GUIDialog_EditViewport(GUISUMOAbstractView* parent,
        const char* name, int x, int y)
    : FXDialogBox(parent, name, DECOR_TITLE | DECOR_BORDER, x, y, 0, 0),
      myParent(parent) {
    FXVerticalFrame* f1 = new FXVerticalFrame(this, LAYOUT_TOP | FRAME_NONE | LAYOUT_FILL_X, 0, 0, 0, 0, 0, 0, 1, 1);
    {
        FXHorizontalFrame* frame0 =
            new FXHorizontalFrame(f1, FRAME_THICK, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2);
        new FXButton(frame0, "\t\tLoad viewport from file",
                     GUIIconSubSys::getIcon(ICON_OPEN_CONFIG), this, GUIDialog_EditViewport::MID_LOAD, GUIDesignButtonToolbar);
        new FXButton(frame0, "\t\tSave viewport to file",
                     GUIIconSubSys::getIcon(ICON_SAVE), this, GUIDialog_EditViewport::MID_SAVE, GUIDesignButtonToolbar);
    }
    FXMatrix* m1 = new FXMatrix(f1, 2, MATRIX_BY_COLUMNS);
    new FXLabel(m1, "Zoom:", 0, LAYOUT_CENTER_Y);
    myZoom = new FXRealSpinDial(m1, 16, this, MID_CHANGED, LAYOUT_CENTER_Y | LAYOUT_TOP | FRAME_SUNKEN | FRAME_THICK);
    myZoom->setRange(0.0001, 100000);
    myZoom->setNumberFormat(4);
    new FXLabel(m1, "X:", 0, LAYOUT_CENTER_Y);
    myXOff = new FXRealSpinDial(m1, 16, this, MID_CHANGED, GUIDesignSpinDial | SPINDIAL_NOMIN | SPINDIAL_NOMAX);
    new FXLabel(m1, "Y:", 0, LAYOUT_CENTER_Y);
    myYOff = new FXRealSpinDial(m1, 16, this, MID_CHANGED, GUIDesignSpinDial | SPINDIAL_NOMIN | SPINDIAL_NOMAX);
    new FXLabel(m1, "Z:", 0, LAYOUT_CENTER_Y);
    myZOff = new FXRealSpinDial(m1, 16, this, MID_CHANGED, GUIDesignSpinDial | SPINDIAL_NOMIN | SPINDIAL_NOMAX);
#ifdef HAVE_OSG
    new FXLabel(m1, "LookAtX:", 0, LAYOUT_CENTER_Y);
    myLookAtX = new FXRealSpinDial(m1, 16, this, MID_CHANGED, GUIDesignSpinDial | SPINDIAL_NOMIN | SPINDIAL_NOMAX);
    new FXLabel(m1, "LookAtY:", 0, LAYOUT_CENTER_Y);
    myLookAtY = new FXRealSpinDial(m1, 16, this, MID_CHANGED, GUIDesignSpinDial | SPINDIAL_NOMIN | SPINDIAL_NOMAX);
    new FXLabel(m1, "LookAtZ:", 0, LAYOUT_CENTER_Y);
    myLookAtZ = new FXRealSpinDial(m1, 16, this, MID_CHANGED, GUIDesignSpinDial | SPINDIAL_NOMIN | SPINDIAL_NOMAX);
#endif
    // ok/cancel
    new FXHorizontalSeparator(f1, GUIDesignHorizontalSeparator);
    FXHorizontalFrame* f6 = new FXHorizontalFrame(f1, LAYOUT_TOP | LAYOUT_LEFT | LAYOUT_FILL_X | PACK_UNIFORM_WIDTH, 0, 0, 0, 0, 10, 10, 5, 0);
    FXButton* initial =
        new FXButton(f6, "&OK", NULL, this, GUIDialog_EditViewport::MID_OK,
                     BUTTON_INITIAL | BUTTON_DEFAULT | FRAME_RAISED | FRAME_THICK | LAYOUT_TOP | LAYOUT_LEFT | LAYOUT_CENTER_X,
                     0, 0, 0, 0,  4, 4, 3, 3);
    new FXButton(f6, "&Cancel", NULL, this, GUIDialog_EditViewport::MID_CANCEL,
                 FRAME_RAISED | FRAME_THICK | LAYOUT_TOP | LAYOUT_LEFT | LAYOUT_CENTER_X,
                 0, 0, 0, 0,  4, 4, 3, 3);
    initial->setFocus();
    setIcon(GUIIconSubSys::getIcon(ICON_EMPTY));
}