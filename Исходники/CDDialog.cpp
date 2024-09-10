void CDDialog::upload(){

  if(!checkit())
    return;

  /*
  switch( QMessageBox::information( this,klocale->translate("Message"),

klocale->translate(
"The submission you are about to make will go to the test server\n"\
"[email protected]. This is because this is the first release of\n"\
"the cddb addition to Kscd and I need to avoid corruption\n"\
"of the remote cddb data bases due to possible bugs in Kscd.\n"\
"Since we need about a 100 error free test submissions\n"\
"before we will be granted write acces to the 'true' cddb databases, 
I would like you ask you to upload as many test submissions as possible.\n"\
"You don't need to try to find a CD that is not in the database \n"\
"(thought that would be helpful),it suffices to submit existing\n"\
"entries with Kscd.\n"\
"After submission you should receive a mail notifying you of success or\n"\
"or failure of your submission. Should you receive a failure notice\n"\
"please forward the failure report to me: <*****@*****.**>\n"\
"Check back often for the availablity of a fully enabled version of kscd.\n"\
"Thank you for your support.\n"),
				    klocale->translate("OK"),
				    klocale->translate("Cancel"),
				    0,
				    1 ) ){

  case 0: 
    break;
  case 1: 
    return;
    break;
  }

  */


  InexactDialog *dialog;

  dialog = new InexactDialog(0,"Dialog",true);


  QStrList catlist;

  catlist.append("rock");
  catlist.append("classical");
  catlist.append("jazz");
  catlist.append("soundtrack");
  catlist.append("newage");
  catlist.append("blues");
  catlist.append("folk");
  catlist.append("country");
  catlist.append("reggae");
  catlist.append("misc");
  catlist.append("data");

  dialog->insertList(catlist);
  dialog->setErrorString((char *)klocale->translate("Please select a Category or press Cancel"));
  dialog->setTitle((char *)klocale->translate("To which category does the CD belong?"));
  if(dialog->exec() != QDialog::Accepted){
    delete dialog;
    return;
  }

  dialog->getSelection(submitcat);
  delete dialog;

  QString tempfile;
  tempfile = tempfile.sprintf("%s",tmpnam(0L));

  save_cddb_entry(tempfile,true);

  mykapp->processEvents();
  mykapp->flushX();


/*  QString subject;
  subject.sprintf("cddb %s %08lx",submitcat.data(),cdinfo.magicID);

  QString formatstr;
  //  formatstr = mailcmd + " [email protected]";
  formatstr = mailcmd;
  formatstr += " ";
  formatstr += submitaddress;
  */
  if(smtpConfigData->enabled){
      if(debugflag)
          printf("Submitting cddb entry via SMTP...\n");
      QFile file(tempfile);

      file.open(IO_ReadOnly);
      QTextStream ti(&file);

      QString s;
      QString subject;
      
      while (!ti.eof()){
          s += ti.readLine() + "\r\n";
//          if(!ti.eof()){
              //  mimetranslate(s);
//              to << s.data() << '\n';
 //         }
      }

//      smtpMailer = new SMTP;

      smtpMailer->setServerHost(smtpConfigData->serverHost.data());
      smtpMailer->setPort(smtpConfigData->serverPort.toInt());
      
      smtpMailer->setSenderAddress(smtpConfigData->senderAddress.data());
      smtpMailer->setRecipientAddress(submitaddress.data());
      
      subject.sprintf("cddb %s %08lx", submitcat.data(), cdinfo.magicID);
      smtpMailer->setMessageSubject(subject.data());
      smtpMailer->setMessageBody(s.data());

      smtpMailer->sendMessage();
      
      return;
  }

      
  QString cmd;
  //  cmd = cmd.sprintf("mail -s \"%s\" [email protected]",subject.data());
  //  cmd = cmd.sprintf("sendmail [email protected]");
  cmd = cmd.sprintf("sendmail -tU");
  //  cmd = cmd.sprintf(formatstr.data(),subject.data());

  if (debugflag ) printf(klocale->translate("Submitting cddb entry: %s\n"),cmd.data());
  
  FILE* mailpipe;
  mailpipe = popen(cmd.data(),"w");

  if(mailpipe == NULL){
    QString str;
    str.sprintf(klocale->translate("Could not pipe contents into:\n %s"),cmd.data());

    QMessageBox::critical(this, "Kscd", str.data());
    pclose(mailpipe);
    return;
    
  }
  
  QFile file(tempfile);
  //  QFile file2("/home/wuebben/test.txt"); // ******

  file.open(IO_ReadOnly);
  //file2.open(IO_ReadWrite); // ******
  QTextStream ti(&file);
  //QTextStream to(&file2); // ******

  QTextStream to(mailpipe,IO_WriteOnly );

  QString s;

  //to << "Content-Transfer-Encoding: quoted-printable\n";

  while ( !ti.eof() ) {
      s = ti.readLine();
      if(!ti.eof()){
          //  mimetranslate(s);
          to << s.data() << '\n';
      }
  }

  pclose(mailpipe);

  file.close();
  //  file2.close();   // *****

  unlink(tempfile.data());
  if ( debugflag ) printf("DONE SENDING\n");
}