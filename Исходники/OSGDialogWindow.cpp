DialogWindowUnrecPtr DialogWindow::createInputDialog(const std::string& Title, const std::string& Message, const int& Type, const bool& showCancel, const std::vector<std::string>& InputValues, const std::string& ConfirmBtnText, const std::string& CancelBtnText)
{
    int DialogHeight = 175;
    DialogWindowRefPtr TheDialog = DialogWindow::create();

    ImageComponentRefPtr TheIcon = ImageComponent::create();
    LineBorderRefPtr TempIconBorder = OSG::LineBorder::create();
    TheIcon->setPreferredSize(Vec2f(45,45));
    TheIcon->setBorders(TempIconBorder);

    // Create Panel for input
    PanelRefPtr InputPanel = OSG::Panel::createEmpty();
    FlowLayoutRefPtr InputPanelLayout = OSG::FlowLayout::create();
    InputPanel->setLayout(InputPanelLayout);
    InputPanel->setPreferredSize(Vec2f(450,75));

    ButtonRefPtr InputButton;
    switch (Type) {
        case INPUT_TEXT:
            TheDialog->_InputTextField = OSG::TextField::create();
            TheDialog->_InputTextField->setText(InputValues[0]);
            TheDialog->_InputTextField->setPreferredSize(Vec2f(200,25));
            InputPanel->pushToChildren(TheDialog->_InputTextField);
            break;
        case INPUT_BTNS:	
            DialogHeight = 150;
            for (std::vector<std::string>::const_iterator it = InputValues.begin(); it!=InputValues.end(); ++it)
            {
                InputButton = OSG::Button::create();
                InputButton->setText(*it);
                InputButton->setMinSize(InputButton->getPreferredSize());
                InputButton->setPreferredSize(InputButton->getRequestedSize());
                InputButton->addActionListener(&TheDialog->_InputButtonListener);
                InputPanel->pushToChildren(InputButton);
            }				
            break;
        case INPUT_COMBO:
        default:
            TheDialog->_InputComboBox = OSG::ComboBox::create();
            DefaultMutableComboBoxModelRefPtr _InputComboBoxModel;
            _InputComboBoxModel = DefaultMutableComboBoxModel::create();

            for (std::vector<std::string>::const_iterator it = InputValues.begin(); it!=InputValues.end(); ++it)
            {
                _InputComboBoxModel->addElement(boost::any(std::string(*it)));
            }

            TheDialog->_InputComboBox->setPreferredSize(Vec2f(150, 23));
            TheDialog->_InputComboBox->setModel(_InputComboBoxModel);
            TheDialog->_InputComboBox->setSelectedIndex(0);

            InputPanel->pushToChildren(TheDialog->_InputComboBox);
            break;
    }

    FlowLayoutRefPtr MessagePanelBottomLayout;
    PanelRefPtr MessageButtonPanel;
    ButtonRefPtr ConfirmationButton;
    ButtonRefPtr CancelButton;


    if(Type != INPUT_BTNS)
    {
        ConfirmationButton = OSG::Button::create();
        //Confirm Button
        ConfirmationButton->setText(ConfirmBtnText);
        ConfirmationButton->setMinSize(ConfirmationButton->getPreferredSize());
        ConfirmationButton->setPreferredSize(ConfirmationButton->getRequestedSize());

        if(Type == INPUT_TEXT)
        {
            ConfirmationButton->addActionListener(&TheDialog->_TextButtonListener);
        }
        else
        {
            ConfirmationButton->addActionListener(&TheDialog->_ComboButtonListener);
        }
    }

    if(showCancel)
    {
        CancelButton = OSG::Button::create();
        //Cancel Button
        CancelButton->setText(CancelBtnText);
        CancelButton->setMinSize(CancelButton->getPreferredSize());
        CancelButton->setPreferredSize(CancelButton->getRequestedSize());

        //Attach listener to the Cancel button
        CancelButton->addActionListener(&TheDialog->_CancelButtonListener);
    }

    // Create Panel for top half of SplitPanel
    TextAreaRefPtr MessagePanelText = createTransparentTextArea(Message);

    //If the type of input is buttons and showCancel is true, just push the cancel button onto the input panel
    if(Type == INPUT_BTNS && showCancel)
    {
        InputPanel->pushToChildren(CancelButton);
    }
    else if(Type != INPUT_BTNS)
    {
        // Create Panel for bottom half of SplitPanel
        MessageButtonPanel = OSG::Panel::createEmpty();
        MessagePanelBottomLayout = OSG::FlowLayout::create();
        MessageButtonPanel->pushToChildren(ConfirmationButton);
        if(showCancel) 
            MessageButtonPanel->pushToChildren(CancelButton);
        MessageButtonPanel->setLayout(MessagePanelBottomLayout);
        MessageButtonPanel->setPreferredSize(Vec2f(450,75));
    } 

    // Create SplitPanel itself
    PanelRefPtr MessagePanel = OSG::Panel::createEmpty();
    SpringLayoutRefPtr MessagePanelLayout = SpringLayout::create();
    MessagePanel->pushToChildren(MessagePanelText);
    MessagePanel->pushToChildren(TheIcon);
    MessagePanel->pushToChildren(InputPanel);
    if(Type != INPUT_BTNS)
        MessagePanel->pushToChildren(MessageButtonPanel);
    MessagePanel->setLayout(MessagePanelLayout);


    //MessagePanelLayout
    //Icon
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheIcon, 10, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, TheIcon, LayoutSpring::width(TheIcon));
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheIcon, 10, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TheIcon, LayoutSpring::height(TheIcon));

    //Message
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10, SpringLayoutConstraints::EAST_EDGE, TheIcon);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, 20, SpringLayoutConstraints::NORTH_EDGE, InputPanel);

    //Input Panel
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, InputPanel, 0, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, InputPanel, 0, SpringLayoutConstraints::EAST_EDGE, MessagePanel);

    if(Type != INPUT_BTNS)
    {
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, InputPanel, 40, SpringLayoutConstraints::NORTH_EDGE, MessageButtonPanel);
        //Button Panel
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, MessageButtonPanel, LayoutSpring::height(MessageButtonPanel));
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, MessagePanel);
    }
    else
    {
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, InputPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, MessagePanel);
    }

    //Internals Layout and constraints
    BorderLayoutConstraintsRefPtr MessagePanelConstraints = BorderLayoutConstraints::create();
    MessagePanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    MessagePanel->setConstraints(MessagePanelConstraints);

    BorderLayoutRefPtr DialogLayout = BorderLayout::create();

    //Create the Dialog box
    TheDialog->setLayout(DialogLayout);
    TheDialog->setPreferredSize(Vec2f(350,DialogHeight));
    TheDialog->pushToChildren(MessagePanel);
    TheDialog->setTitle(Title);

    return TheDialog;
}