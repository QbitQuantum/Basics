KeyhoteeMainWindow::KeyhoteeMainWindow(const TKeyhoteeApplication& mainApp) :
  _identities_root(nullptr),
  _connectionProcessor(*this, bts::application::instance()->get_profile()),
  _currentMailbox(nullptr),
  _isClosing(false)
{
  ui = new Ui::KeyhoteeMainWindow;
  ui->setupUi(this);

  QString profileName = mainApp.getLoadedProfileName();

  QString title = QString("%1 (%2)").arg(mainApp.getAppName().c_str()).arg(profileName);
  setWindowTitle(title);
  setEnabledAttachmentSaveOption(false);
  setEnabledDeleteOption(false);
  setEnabledMailActions(false);
  setEnabledShareContactOption(false);

  QString settings_file = "keyhotee_";
  settings_file.append(profileName);
  setSettingsFile(settings_file);
  readSettings();

  connect(ui->contacts_page, &ContactsTable::contactOpened, this, &KeyhoteeMainWindow::openContactGui);
  connect(ui->contacts_page, &ContactsTable::contactDeleted, this, &KeyhoteeMainWindow::deleteContactGui);
  

#ifdef Q_OS_MAC
  //QMacNativeToolBar* native_toolbar = QtMacExtras::setNativeToolBar(ui->toolbar, true);
  ui->side_bar->setAttribute(Qt::WA_MacShowFocusRect, 0);
#endif /// Q_OS_MAC

  setupStatusBar();

  QWidget* empty = new QWidget();
  empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  ui->toolbar->addWidget(empty);

  _search_edit = new QLineEdit(ui->toolbar);
  ui->toolbar->addWidget(_search_edit);
  _search_edit->setMaximumSize(QSize(150, 22) );
  _search_edit->setAttribute(Qt::WA_MacShowFocusRect, 0);
  const char* search_style = "QLineEdit { " \
                             "padding-right: 20px; " \
                             "padding-left: 5px; " \
                             "background: url(:/images/search24x16.png);" \
                             "background-position: right;" \
                             "background-repeat: no-repeat;" \
                             "border: 1px solid gray;" \
                             "border-radius: 10px;}";
  _search_edit->setStyleSheet(search_style);
  _search_edit->setPlaceholderText(tr("Search") );

  QWidget* empty2 = new QWidget();
  empty->resize(QSize(10, 10) );
  ui->toolbar->addWidget(empty2);

  ui->actionEnable_Mining->setEnabled(gMiningIsPossible);
  ui->actionEnable_Mining->setVisible(gMiningIsPossible);

  ui->side_bar->setModificationsChecker (this);

  menuEdit = new MenuEditControl(this, ui->actionCopy, ui->actionCut, ui->actionPaste);
  //init ui->actionPaste
  onClipboardChanged();
  connect(QApplication::clipboard(), &QClipboard::changed, this, &KeyhoteeMainWindow::onClipboardChanged);

  // ---------------------- MenuBar
  // File
  connect(ui->actionExit, &QAction::triggered, this, &KeyhoteeMainWindow::onExit);
  // Edit
  connect(ui->actionCopy, &QAction::triggered, this, &KeyhoteeMainWindow::onCopy);
  connect(ui->actionCut, &QAction::triggered, this, &KeyhoteeMainWindow::onCut);
  connect(ui->actionPaste, &QAction::triggered, this, &KeyhoteeMainWindow::onPaste);
  connect(ui->actionSelect_All, &QAction::triggered, this, &KeyhoteeMainWindow::onSelectAll);
  // Identity
  connect(ui->actionNew_identity, &QAction::triggered, this, &KeyhoteeMainWindow::onNewIdentity);
  connect(ui->actionEnable_Mining, &QAction::toggled, this, &KeyhoteeMainWindow::onEnableMining);
  // Mail
  connect(ui->actionNew_Message, &QAction::triggered, this, &KeyhoteeMainWindow::newMailMessage);
  connect(ui->actionSave_attachement, &QAction::triggered, this, &KeyhoteeMainWindow::onSaveAttachement);
  // Contact
  connect(ui->actionNew_Contact, &QAction::triggered, this, &KeyhoteeMainWindow::addContact);
  connect(ui->actionSet_Icon, &QAction::triggered, this, &KeyhoteeMainWindow::onSetIcon);
  connect(ui->actionShow_Contacts, &QAction::triggered, this, &KeyhoteeMainWindow::showContacts);
  connect(ui->actionRequest_authorization, &QAction::triggered, this, &KeyhoteeMainWindow::onRequestAuthorization);
  connect(ui->actionShare_contact, &QAction::triggered, this, &KeyhoteeMainWindow::onShareContact);
  // Help
  connect(ui->actionDiagnostic, &QAction::triggered, this, &KeyhoteeMainWindow::onDiagnostic);
  connect(ui->actionAbout, &QAction::triggered, this, &KeyhoteeMainWindow::onAbout);

  connect(ui->splitter, &QSplitter::splitterMoved, this, &KeyhoteeMainWindow::sideBarSplitterMoved);
  connect(ui->side_bar, &TreeWidgetCustom::itemSelectionChanged, this, &KeyhoteeMainWindow::onSidebarSelectionChanged);
  connect(ui->side_bar, &TreeWidgetCustom::itemDoubleClicked, this, &KeyhoteeMainWindow::onSidebarDoubleClicked);
  connect(ui->side_bar, &TreeWidgetCustom::itemContactRemoved, this, &KeyhoteeMainWindow::onItemContactRemoved);

  connect(ui->side_bar, &TreeWidgetCustom::itemContextAcceptRequest, this, &KeyhoteeMainWindow::onItemContextAcceptRequest);
  connect(ui->side_bar, &TreeWidgetCustom::itemContextDenyRequest, this, &KeyhoteeMainWindow::onItemContextDenyRequest);
  connect(ui->side_bar, &TreeWidgetCustom::itemContextBlockRequest, this, &KeyhoteeMainWindow::onItemContextBlockRequest);
  
  //connect( _search_edit, SIGNAL(textChanged(QString)), this, SLOT(searchEditChanged(QString)) );
  connect(_search_edit, &QLineEdit::textChanged, this, &KeyhoteeMainWindow::searchEditChanged);

  auto space2 = ui->side_bar->topLevelItem(TopLevelItemIndexes::Space2);
  auto space3 = ui->side_bar->topLevelItem(TopLevelItemIndexes::Space3);
  auto space_flags = space2->flags() & (~Qt::ItemFlags(Qt::ItemIsSelectable) );
  space_flags |= Qt::ItemNeverHasChildren;
  space2->setFlags(space_flags);
  space3->setFlags(space_flags);

  //_identities_root = ui->side_bar->topLevelItem(TopLevelItemIndexes::Identities);
  _mailboxes_root = ui->side_bar->topLevelItem(TopLevelItemIndexes::Mailboxes);
  _contacts_root = ui->side_bar->topLevelItem(TopLevelItemIndexes::Contacts);
  _wallets_root = ui->side_bar->topLevelItem(TopLevelItemIndexes::Wallets);
  _requests_root = ui->side_bar->topLevelItem(TopLevelItemIndexes::Requests);

  _contacts_root->setExpanded(true);
  _requests_root->setExpanded(true);
  _requests_root->setHidden(true);
  //_identities_root->setExpanded(true);
  _mailboxes_root->setExpanded(true);
  _inbox_root = _mailboxes_root->child(Inbox);
  _drafts_root = _mailboxes_root->child(Drafts);
  _out_box_root = _mailboxes_root->child(Outbox);
  _sent_root = _mailboxes_root->child(Sent);

  _wallets_root->setExpanded(true);
  _bitcoin_root = _wallets_root->child(Bitcoin);
  _bitshares_root = _wallets_root->child(BitShares);
  _litecoin_root = _wallets_root->child(Litecoin);

  auto app = bts::application::instance();
  auto profile = app->get_profile();
  auto idents = profile->identities();

  auto addressbook = profile->get_addressbook();
  _addressbook_model = new AddressBookModel(this, addressbook);

  _inbox_model = new MailboxModel(this, profile, profile->get_inbox_db(), *_addressbook_model, false);
  _draft_model = new MailboxModel(this, profile, profile->get_draft_db(), *_addressbook_model, true);
  _pending_model = new MailboxModel(this, profile, profile->get_pending_db(), *_addressbook_model, false);
  _sent_model = new MailboxModel(this, profile, profile->get_sent_db(), *_addressbook_model, false);

  connect(_addressbook_model, &QAbstractItemModel::dataChanged, this,
    &KeyhoteeMainWindow::addressBookDataChanged);

  ui->contacts_page->setAddressBook(_addressbook_model);
  ui->new_contact->setAddressBook(_addressbook_model);

  ui->inbox_page->initial(_connectionProcessor, _inbox_model, Mailbox::Inbox, this);
  ui->draft_box_page->initial(_connectionProcessor, _draft_model, Mailbox::Drafts, this);
  ui->out_box_page->initial(_connectionProcessor, _pending_model, Mailbox::Outbox, this);
  ui->sent_box_page->initial(_connectionProcessor, _sent_model, Mailbox::Sent, this);

  ui->widget_stack->setCurrentWidget(ui->inbox_page);
  ui->actionDelete->setShortcut(QKeySequence::Delete);
  connect(ui->actionDelete, SIGNAL(triggered()), ui->inbox_page, SLOT(onDeleteMail()));
  connect(ui->actionShow_details, SIGNAL(toggled(bool)), ui->inbox_page, SLOT(on_actionShow_details_toggled(bool)));
  connect(ui->actionReply, SIGNAL(triggered()), ui->inbox_page, SLOT(onReplyMail()));
  connect(ui->actionReply_all, SIGNAL(triggered()), ui->inbox_page, SLOT(onReplyAllMail()));
  connect(ui->actionForward, SIGNAL(triggered()), ui->inbox_page, SLOT(onForwardMail()));

  wlog("idents: ${idents}", ("idents", idents) );

  if(isIdentityPresent() == false )
  {
      ui->actionNew_Message->setEnabled(false);
      ui->actionRequest_authorization->setEnabled(false);
  }

  for (size_t i = 0; i < idents.size(); ++i)
  {
     try {
          app->mine_name(idents[i].dac_id_string,
                         profile->get_keychain().get_identity_key(idents[i].dac_id_string).get_public_key(),
                         idents[i].mining_effort);
     } 
     catch ( const fc::exception& e )
     {
        wlog( "${e}", ("e",e.to_detail_string()) );
     }
  }
  app->set_mining_intensity(0);
  ui->actionEnable_Mining->setChecked(app->get_mining_intensity() != 0);
  _addressbook = profile->get_addressbook();

  /*
     auto abook  = profile->get_addressbook();
     auto contacts = abook->get_known_bitnames();
     for( auto itr = contacts.begin(); itr != contacts.end(); ++itr )
   {
      auto new_contact_item = new QTreeWidgetItem(_contacts_root, (QTreeWidgetItem::ItemType)ContactItem );

      auto id_rec = app->lookup_name( *itr );
      if( !id_rec )
    {
         new_contact_item->setText( 0, (*itr + " [unknown]").c_str() );
    }
      else
    {
         new_contact_item->setText( 0, (*itr + " [" + std::to_string(id_rec->repute)+"]" ).c_str() );
    }
   }
   */

  QAction* actionMenu = new QAction(tr("Keyhotee"), this);
  actionMenu->setCheckable(true);
  this->setMenuWindow(ui->menuWindow);
  this->registration(actionMenu);
  actionMenu->setVisible(false);
}