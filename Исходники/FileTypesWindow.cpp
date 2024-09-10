FileTypesWindow::FileTypesWindow(const BMessage& settings)
    :
    BWindow(_Frame(settings), B_TRANSLATE_SYSTEM_NAME("FileTypes"),
           B_TITLED_WINDOW, B_NOT_ZOOMABLE | B_ASYNCHRONOUS_CONTROLS
           | B_AUTO_UPDATE_SIZE_LIMITS),
    fNewTypeWindow(NULL)
{
    bool showIcons;
    bool showRule;
    if (settings.FindBool("show_icons", &showIcons) != B_OK)
        showIcons = true;
    if (settings.FindBool("show_rule", &showRule) != B_OK)
        showRule = false;

    float padding = be_control_look->DefaultItemSpacing();
    BAlignment labelAlignment = be_control_look->DefaultLabelAlignment();
    BAlignment fullAlignment(B_ALIGN_USE_FULL_WIDTH, B_ALIGN_USE_FULL_HEIGHT);

    // add the menu
    BMenuBar* menuBar = new BMenuBar("");

    BMenu* menu = new BMenu(B_TRANSLATE("File"));
    BMenuItem* item = new BMenuItem(
        B_TRANSLATE("New resource file" B_UTF8_ELLIPSIS), NULL, 'N',
        B_COMMAND_KEY);
    item->SetEnabled(false);
    menu->AddItem(item);

    BMenu* recentsMenu = BRecentFilesList::NewFileListMenu(
                             B_TRANSLATE("Open" B_UTF8_ELLIPSIS), NULL, NULL,
                             be_app, 10, false, NULL, kSignature);
    item = new BMenuItem(recentsMenu, new BMessage(kMsgOpenFilePanel));
    item->SetShortcut('O', B_COMMAND_KEY);
    menu->AddItem(item);

    menu->AddItem(new BMenuItem(
                      B_TRANSLATE("Application types" B_UTF8_ELLIPSIS),
                      new BMessage(kMsgOpenApplicationTypesWindow)));
    menu->AddSeparatorItem();

    menu->AddItem(new BMenuItem(B_TRANSLATE("Quit"),
                                new BMessage(B_QUIT_REQUESTED), 'Q', B_COMMAND_KEY));
    menu->SetTargetForItems(be_app);
    menuBar->AddItem(menu);

    menu = new BMenu(B_TRANSLATE("Settings"));
    item = new BMenuItem(B_TRANSLATE("Show icons in list"),
                         new BMessage(kMsgToggleIcons));
    item->SetMarked(showIcons);
    item->SetTarget(this);
    menu->AddItem(item);

    item = new BMenuItem(B_TRANSLATE("Show recognition rule"),
                         new BMessage(kMsgToggleRule));
    item->SetMarked(showRule);
    item->SetTarget(this);
    menu->AddItem(item);
    menuBar->AddItem(menu);
    menuBar->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT, B_ALIGN_TOP));

    // MIME Types list
    BButton* addTypeButton = new BButton("add",
                                         B_TRANSLATE("Add" B_UTF8_ELLIPSIS), new BMessage(kMsgAddType));

    fRemoveTypeButton = new BButton("remove", B_TRANSLATE("Remove"),
                                    new BMessage(kMsgRemoveType) );

    fTypeListView = new MimeTypeListView("typeview", NULL, showIcons, false);
    fTypeListView->SetSelectionMessage(new BMessage(kMsgTypeSelected));
    fTypeListView->SetExplicitMinSize(BSize(200, B_SIZE_UNSET));

    BScrollView* typeListScrollView = new BScrollView("scrollview",
            fTypeListView, B_FRAME_EVENTS | B_WILL_DRAW, false, true);

    // "Icon" group

    fIconView = new TypeIconView("icon");
    fIconBox = new BBox("Icon BBox");
    fIconBox->SetLabel(B_TRANSLATE("Icon"));
    BLayoutBuilder::Group<>(fIconBox, B_VERTICAL, padding)
    .SetInsets(padding)
    .AddGlue(1)
    .Add(fIconView, 3)
    .AddGlue(1);

    // "File Recognition" group

    fRecognitionBox = new BBox("Recognition Box");
    fRecognitionBox->SetLabel(B_TRANSLATE("File recognition"));
    fRecognitionBox->SetExplicitAlignment(fullAlignment);

    fExtensionLabel = new StringView(B_TRANSLATE("Extensions:"), NULL);
    fExtensionLabel->LabelView()->SetExplicitAlignment(labelAlignment);

    fAddExtensionButton = new BButton("add ext",
                                      B_TRANSLATE("Add" B_UTF8_ELLIPSIS), new BMessage(kMsgAddExtension));
    fAddExtensionButton->SetExplicitMaxSize(
        BSize(B_SIZE_UNLIMITED, B_SIZE_UNSET));

    fRemoveExtensionButton = new BButton("remove ext", B_TRANSLATE("Remove"),
                                         new BMessage(kMsgRemoveExtension));

    fExtensionListView = new ExtensionListView("listview ext",
            B_SINGLE_SELECTION_LIST);
    fExtensionListView->SetSelectionMessage(
        new BMessage(kMsgExtensionSelected));
    fExtensionListView->SetInvocationMessage(
        new BMessage(kMsgExtensionInvoked));

    BScrollView* scrollView = new BScrollView("scrollview ext",
            fExtensionListView, B_FRAME_EVENTS | B_WILL_DRAW, false, true);

    fRuleControl = new BTextControl("rule", B_TRANSLATE("Rule:"), "",
                                    new BMessage(kMsgRuleEntered));
    fRuleControl->SetAlignment(B_ALIGN_RIGHT, B_ALIGN_LEFT);
    fRuleControl->Hide();

    BLayoutBuilder::Grid<>(fRecognitionBox, padding, padding / 2)
    .SetInsets(padding, padding * 2, padding, padding)
    .Add(fExtensionLabel->LabelView(), 0, 0)
    .Add(scrollView, 0, 1, 2, 2)
    .Add(fAddExtensionButton, 2, 1)
    .Add(fRemoveExtensionButton, 2, 2)
    .Add(fRuleControl, 0, 3, 3, 1);

    // "Description" group

    fDescriptionBox = new BBox("description BBox");
    fDescriptionBox->SetLabel(B_TRANSLATE("Description"));
    fDescriptionBox->SetExplicitAlignment(fullAlignment);

    fInternalNameView = new StringView(B_TRANSLATE("Internal name:"), NULL);
    fInternalNameView->SetEnabled(false);
    fTypeNameControl = new BTextControl("type", B_TRANSLATE("Type name:"), "",
                                        new BMessage(kMsgTypeEntered));
    fDescriptionControl = new BTextControl("description",
                                           B_TRANSLATE("Description:"), "", new BMessage(kMsgDescriptionEntered));

    BLayoutBuilder::Grid<>(fDescriptionBox, padding / 2, padding / 2)
    .SetInsets(padding, padding * 2, padding, padding)
    .Add(fInternalNameView->LabelView(), 0, 0)
    .Add(fInternalNameView->TextView(), 1, 0)
    .Add(fTypeNameControl->CreateLabelLayoutItem(), 0, 1)
    .Add(fTypeNameControl->CreateTextViewLayoutItem(), 1, 1, 2)
    .Add(fDescriptionControl->CreateLabelLayoutItem(), 0, 2)
    .Add(fDescriptionControl->CreateTextViewLayoutItem(), 1, 2, 2);

    // "Preferred Application" group

    fPreferredBox = new BBox("preferred BBox");
    fPreferredBox->SetLabel(B_TRANSLATE("Preferred application"));

    menu = new BPopUpMenu("preferred");
    menu->AddItem(item = new BMenuItem(B_TRANSLATE("None"),
                                       new BMessage(kMsgPreferredAppChosen)));
    item->SetMarked(true);
    fPreferredField = new BMenuField("preferred", (char*)NULL, menu);

    fSelectButton = new BButton("select",
                                B_TRANSLATE("Select" B_UTF8_ELLIPSIS),
                                new BMessage(kMsgSelectPreferredApp));

    fSameAsButton = new BButton("same as",
                                B_TRANSLATE("Same as" B_UTF8_ELLIPSIS),
                                new BMessage(kMsgSamePreferredAppAs));

    BLayoutBuilder::Group<>(fPreferredBox, B_HORIZONTAL, padding)
    .SetInsets(padding, padding * 2, padding, padding)
    .Add(fPreferredField)
    .Add(fSelectButton)
    .Add(fSameAsButton);

    // "Extra Attributes" group

    fAttributeBox = new BBox("Attribute Box");
    fAttributeBox->SetLabel(B_TRANSLATE("Extra attributes"));

    fAddAttributeButton = new BButton("add attr",
                                      B_TRANSLATE("Add" B_UTF8_ELLIPSIS), new BMessage(kMsgAddAttribute));
    fAddAttributeButton->SetExplicitMaxSize(
        BSize(B_SIZE_UNLIMITED, B_SIZE_UNSET));

    fRemoveAttributeButton = new BButton("remove attr", B_TRANSLATE("Remove"),
                                         new BMessage(kMsgRemoveAttribute));
    fRemoveAttributeButton->SetExplicitMaxSize(
        BSize(B_SIZE_UNLIMITED, B_SIZE_UNSET));

    fMoveUpAttributeButton = new BButton("move up attr", B_TRANSLATE("Move up"),
                                         new BMessage(kMsgMoveUpAttribute));
    fMoveUpAttributeButton->SetExplicitMaxSize(
        BSize(B_SIZE_UNLIMITED, B_SIZE_UNSET));
    fMoveDownAttributeButton = new BButton("move down attr",
                                           B_TRANSLATE("Move down"), new BMessage(kMsgMoveDownAttribute));
    fMoveDownAttributeButton->SetExplicitMaxSize(
        BSize(B_SIZE_UNLIMITED, B_SIZE_UNSET));

    fAttributeListView = new AttributeListView("listview attr");
    fAttributeListView->SetSelectionMessage(
        new BMessage(kMsgAttributeSelected));
    fAttributeListView->SetInvocationMessage(
        new BMessage(kMsgAttributeInvoked));

    BScrollView* attributesScroller = new BScrollView("scrollview attr",
            fAttributeListView, B_FRAME_EVENTS | B_WILL_DRAW, false, true);

    BLayoutBuilder::Group<>(fAttributeBox, B_HORIZONTAL, padding)
    .SetInsets(padding, padding * 2, padding, padding)
    .Add(attributesScroller, 1.0f)
    .AddGroup(B_VERTICAL, padding / 2, 0.0f)
    .SetInsets(0)
    .Add(fAddAttributeButton)
    .Add(fRemoveAttributeButton)
    .AddStrut(padding)
    .Add(fMoveUpAttributeButton)
    .Add(fMoveDownAttributeButton)
    .AddGlue();

    fMainSplitView = new BSplitView(B_HORIZONTAL, floorf(padding / 2));

    BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
    .SetInsets(0)
    .Add(menuBar)
    .AddGroup(B_HORIZONTAL, 0)
    .SetInsets(padding, padding, padding, padding)
    .AddSplit(fMainSplitView)
    .AddGroup(B_VERTICAL, padding)
    .Add(typeListScrollView)
    .AddGroup(B_HORIZONTAL, padding)
    .Add(addTypeButton)
    .Add(fRemoveTypeButton)
    .AddGlue()
    .End()
    .End()
    // Right side
    .AddGroup(B_VERTICAL, padding)
    .AddGroup(B_HORIZONTAL, padding)
    .Add(fIconBox, 1)
    .Add(fRecognitionBox, 3)
    .End()
    .Add(fDescriptionBox)
    .Add(fPreferredBox)
    .Add(fAttributeBox, 5);

    _SetType(NULL);
    _ShowSnifferRule(showRule);

    float leftWeight;
    float rightWeight;
    if (settings.FindFloat("left_split_weight", &leftWeight) != B_OK
            || settings.FindFloat("right_split_weight", &rightWeight) != B_OK) {
        leftWeight = 0.2;
        rightWeight = 1.0 - leftWeight;
    }
    fMainSplitView->SetItemWeight(0, leftWeight, false);
    fMainSplitView->SetItemWeight(1, rightWeight, true);

    BMimeType::StartWatching(this);
}