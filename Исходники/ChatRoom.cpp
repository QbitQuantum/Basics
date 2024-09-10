 void chatRoom::inviteUser() {
     QString username = ui->lineEdit->text();
     bool found = false;
     int userId = 0;
     for(QMap<int, User*>::Iterator it = global->begin(); it != global->end(); ++it) {
         User* user = it.value();
         if(user->getUsername().compare(username) == 0) {
             //addUser(user->getId(), user);
             found = true;
             userId = user->getId();
         }
     }
     if(!found) {
         QMessageBox::StandardButton resBtn = QMessageBox::question( this, "ChatClient",
                                                                     tr("User not found\n"),
                                                                     QMessageBox::Ok | QMessageBox::Cancel);
         if (resBtn == QMessageBox::Ok || resBtn == QMessageBox::Cancel) {
             ui->lineEdit->setText("");
         }
     }
     else {
         QMap<int, User*>::Iterator it = users.find(userId);
         if(it != users.end()) {
             QMessageBox::StandardButton resBtn = QMessageBox::question( this, "ChatClient",
                                                                         tr("User already joined!\n"),
                                                                         QMessageBox::Ok | QMessageBox::Cancel);
             if (resBtn == QMessageBox::Ok || resBtn == QMessageBox::Cancel) {
                 ui->lineEdit->setText("");
             }
         }
         else {
             Message m(6, mainUser->getUserId(), roomID, 1, intToChar(userId));
             m.send(socket);
         }
     }
 }