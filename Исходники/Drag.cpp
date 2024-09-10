    virtual Omm::Gui::View* createMainView()
    {
        Omm::Gui::Label* pSource = new Omm::Gui::Label;
        pSource->setName("source view");
        pSource->setLabel("Source");
        pSource->setBackgroundColor(Omm::Gui::Color("blue"));
        pSource->setAlignment(Omm::Gui::View::AlignCenter);
        pSource->attachController(new DragController(pSource));
        pSource->setAcceptDrops(true);

        Omm::Gui::Label* pTarget = new Omm::Gui::Label;
        pTarget->setName("target view");
        pTarget->setLabel("Target");
        pTarget->setBackgroundColor(Omm::Gui::Color("white"));
        pTarget->setAlignment(Omm::Gui::View::AlignCenter);
        pTarget->attachController(new DragController(pTarget));
        pTarget->setAcceptDrops(true);

        Omm::Gui::View* pView = new Omm::Gui::View;
        pView->setName("main view");
        pSource->setParent(pView);
        pTarget->setParent(pView);
        pView->setLayout(new Omm::Gui::VerticalLayout);
        pView->attachController(new DragController(pView));

        return pView;
    }