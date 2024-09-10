PageSetupWindow::PageSetupWindow(BMessage *msg, const char *printerName)
    : BlockingWindow(BRect(0, 0, 100, 100), "Page setup",
                     B_TITLED_WINDOW_LOOK,
                     B_MODAL_APP_WINDOW_FEEL,
                     B_NOT_RESIZABLE | B_NOT_MINIMIZABLE | B_NOT_ZOOMABLE
                     | B_AUTO_UPDATE_SIZE_LIMITS | B_CLOSE_ON_ESCAPE),
      fSetupMsg(msg),
      fPrinterDirName(printerName)
{
    if (printerName)
        SetTitle(BString(printerName).Append(" Page setup").String());

    // load orientation
    if (fSetupMsg->FindInt32("orientation", &fCurrentOrientation) != B_OK)
        fCurrentOrientation = PrinterDriver::PORTRAIT_ORIENTATION;

    // load page rect
    BRect page;
    float width = letter_width;
    float height = letter_height;
    if (fSetupMsg->FindRect("preview:paper_rect", &page) == B_OK) {
        width = page.Width();
        height = page.Height();
    } else {
        page.Set(0, 0, width, height);
    }

    BString label;
    if (fSetupMsg->FindString("preview:paper_size", &label) != B_OK)
        label = "Letter";

    // Load units
    int32 units;
    if (fSetupMsg->FindInt32("units", &units) != B_OK)
        units = kUnitInch;

    // re-calculate the margin from the printable rect in points
    BRect margin = page;
    if (fSetupMsg->FindRect("preview:printable_rect", &margin) == B_OK) {
        margin.top -= page.top;
        margin.left -= page.left;
        margin.right = page.right - margin.right;
        margin.bottom = page.bottom - margin.bottom;
    } else {
        margin.Set(28.34, 28.34, 28.34, 28.34);		// 28.34 dots = 1cm
    }


    fMarginView = new MarginView(int32(width), int32(height), margin,
                                 MarginUnit(units));

    BPopUpMenu* pageSizePopUpMenu = new BPopUpMenu("Page size");
    pageSizePopUpMenu->SetRadioMode(true);

    fPageSizeMenu = new BMenuField("page_size", "Page size:", pageSizePopUpMenu);
    fPageSizeMenu->Menu()->SetLabelFromMarked(true);

    for (int32 i = 0; pageFormat[i].label != NULL; i++) {
        BMessage* message = new BMessage(PAGE_SIZE_CHANGED);
        message->AddFloat("width", pageFormat[i].width);
        message->AddFloat("height", pageFormat[i].height);
        BMenuItem* item = new BMenuItem(pageFormat[i].label, message);
        pageSizePopUpMenu->AddItem(item);

        if (label.Compare(pageFormat[i].label) == 0)
            item->SetMarked(true);
    }

    BPopUpMenu* orientationPopUpMenu = new BPopUpMenu("Orientation");
    orientationPopUpMenu->SetRadioMode(true);

    fOrientationMenu = new BMenuField("orientation", "Orientation:",
                                      orientationPopUpMenu);
    fOrientationMenu->Menu()->SetLabelFromMarked(true);

    for (int32 i = 0; orientation[i].label != NULL; i++) {
        BMessage* message = new BMessage(ORIENTATION_CHANGED);
        message->AddInt32("orientation", orientation[i].orientation);
        BMenuItem* item = new BMenuItem(orientation[i].label, message);
        orientationPopUpMenu->AddItem(item);

        if (fCurrentOrientation == orientation[i].orientation)
            item->SetMarked(true);
    }

    float scale0;
    BString scale;
    if (fSetupMsg->FindFloat("scale", &scale0) == B_OK)
        scale << (int)scale0;
    else
        scale = "100";

    fScaleControl = new BTextControl("scale", "Scale [%]:",
                                     scale.String(), NULL);

    for (uint32 i = 0; i < '0'; i++)
        fScaleControl->TextView()->DisallowChar(i);

    for (uint32 i = '9' + 1; i < 255; i++)
        fScaleControl->TextView()->DisallowChar(i);

    fScaleControl->TextView()->SetMaxBytes(3);

    BBox *separator = new BBox("separator");
    separator->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, 1));

    BButton *cancel = new BButton("cancel", "Cancel", new BMessage(CANCEL_MSG));

    BButton *ok = new BButton("ok", "OK", new BMessage(OK_MSG));
    ok->MakeDefault(true);

    BGridView* settings = new BGridView();
    BGridLayout* settingsLayout = settings->GridLayout();
    settingsLayout->AddItem(fPageSizeMenu->CreateLabelLayoutItem(), 0, 0);
    settingsLayout->AddItem(fPageSizeMenu->CreateMenuBarLayoutItem(), 1, 0);
    settingsLayout->AddItem(fOrientationMenu->CreateLabelLayoutItem(), 0, 1);
    settingsLayout->AddItem(fOrientationMenu->CreateMenuBarLayoutItem(), 1, 1);
    settingsLayout->AddItem(fScaleControl->CreateLabelLayoutItem(), 0, 2);
    settingsLayout->AddItem(fScaleControl->CreateTextViewLayoutItem(), 1, 2);
    settingsLayout->SetSpacing(0, 0);

    SetLayout(new BGroupLayout(B_VERTICAL));
    AddChild(BGroupLayoutBuilder(B_VERTICAL, 0)
             .AddGroup(B_HORIZONTAL, 5, 1)
             .AddGroup(B_VERTICAL, 0, 1.0f)
             .Add(fMarginView)
             .AddGlue()
             .End()
             .AddGroup(B_VERTICAL, 0, 1.0f)
             .Add(settings)
             .AddGlue()
             .End()
             .End()
             .Add(separator)
             .AddGroup(B_HORIZONTAL, 10, 1.0f)
             .AddGlue()
             .Add(cancel)
             .Add(ok)
             .End()
             .SetInsets(10, 10, 10, 10)
            );

    BRect winFrame(Frame());
    BRect screenFrame(BScreen().Frame());
    MoveTo((screenFrame.right - winFrame.right) / 2,
           (screenFrame.bottom - winFrame.bottom) / 2);
}