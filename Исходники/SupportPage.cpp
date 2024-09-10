void SupportWidget::setupUi()
{
   QVBoxLayout * vb = new QVBoxLayout;
   setLayout(vb);

   QTextBrowser * lblContact = new QTextBrowser(this);
   lblContact->setOpenExternalLinks(true);
   QString supText = "<h3>We love to hear from the people who use our software.</h3>"
      "<font color=orange>Contact us</font>"
      "<p>"
      "Technical support is available by e-mail addressed to our support department at <a href=\"mailto:[email protected]\" target=_blank>[email protected]</a>. "
      "Please feel free to email us, normally we will reply to you within one business day."
      "<p>Please specify in your message the following details:<ul>"
      "<li> program version"
      "<li> processor type"
      "<li> operating system version"
      "<li> amount of memory available"
      "<li> active applications</ul>"
      "<p><font color=orange>Registration key reclamation</font><p>"
      "If you are a registered user of the program and for a certain reason you need to reclaim your registration key, please contact us at <a href=\"mailto:[email protected]\" target=_blank>[email protected]</a> subject <b>Registration key reclamation</b>,"
      "  message with the following information:<ul>"
      "<li> Your first and last names</li>"
      "<li> The e-mail address the registration message was sent to</li>"
      "<li>  Program name</li>"
      "<li>  License type</li>"
      "<li>  Purchase date</li>"
      "<li>  Purchase method</li>"
      "<li>  Other purchase details</li></ul>"
      "The new registration data will be sent to you within 24 hours."
      "We will send you a registration key by e-mail free of charge. If you use an e-mail address different from the one specified during the registration, please specify all your registration information, including your previous e-mail address. We will send you a registration key after we have checked the registration information.";

   lblContact->setHtml(supText);
   vb->addWidget(lblContact);

   QLabel * lblInfo = new QLabel(this);
   lblInfo->setTextInteractionFlags(Qt::TextSelectableByMouse);
   QDate dtRelease = QDate::fromString(RELEASE_DATE, "yyyy-MM-dd");
   
   lblInfo->setText(QString("Holdem Folder (c) v. %1 by %2 All Right Reserved")
      .arg(VERSION).arg(dtRelease.toString(Qt::SystemLocaleShortDate)));
   lblInfo->setCursor(Qt::IBeamCursor);
   vb->addWidget(lblInfo);
}