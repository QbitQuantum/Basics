/*!
Opens the Add to Contacts popup
*/
void CntServiceAssignContactCardView::addToContacts()
{  
    CNT_ENTRY
    
    HbDialog* popup = new HbDialog();
    popup->setDismissPolicy(HbDialog::NoDismiss);
    popup->setHeadingWidget(
            new HbLabel(hbTrId("txt_phob_title_add_to_contacts"), popup));
    popup->setAttribute(Qt::WA_DeleteOnClose);
    popup->setTimeout( HbPopup::NoTimeout );
    popup->addAction(
            new HbAction(hbTrId("txt_common_button_cancel"), popup));

    HbWidget* buttonWidget = new HbWidget(popup);
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Vertical);
    
    HbPushButton* addButton = new HbPushButton(buttonWidget);
    addButton->setStretched(true);
    addButton->setText(hbTrId("txt_phob_button_save_as_a_new_contact"));
    HbIcon plusIcon("qtg_mono_plus");
    addButton->setIcon(plusIcon);
    connect(addButton, SIGNAL(clicked()), popup, SLOT(close()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(saveNew()));
    connect(addButton, SIGNAL(longPress(QPointF)), popup, SLOT(close()));
    connect(addButton, SIGNAL(longPress(QPointF)), this, SLOT(saveNew()));
    
    HbPushButton* updateButton = new HbPushButton(buttonWidget);
    updateButton->setStretched(true);
    updateButton->setText(hbTrId("txt_phob_button_update_existing_contact"));
    updateButton->setIcon(plusIcon);
    connect(updateButton, SIGNAL(clicked()), popup, SLOT(close()));
    connect(updateButton, SIGNAL(clicked()), this, SLOT(updateExisting()));
    connect(updateButton, SIGNAL(longPress(QPointF)), popup, SLOT(close()));
    connect(updateButton, SIGNAL(longPress(QPointF)), this, SLOT(updateExisting()));
    
    
    layout->addItem(addButton);
    layout->addItem(updateButton);
    
    buttonWidget->setLayout(layout);
    popup->setContentWidget(buttonWidget);

    popup->open();
    
    CNT_EXIT
}