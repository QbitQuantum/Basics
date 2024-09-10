bool DialogChangePassword::SendNewPassword(void) {
  bool communicationSuccess;
  QByteArray PasswordString;
  int password_length = STICK20_PASSOWRD_LEN;
  unsigned char Data[password_length + 2];

  // Set kind of password
  switch (PasswordKind) {
  case STICK20_PASSWORD_KIND_USER:
    Data[0] = 'P';
    break;
  case STICK20_PASSWORD_KIND_ADMIN:
    Data[0] = 'A';
    break;
  default:
    Data[0] = '?';
    break;
  }

  // Send old password
  PasswordString = ui->lineEdit_OldPW->text().toLatin1();

  STRNCPY((char *)&Data[1], STICK20_PASSOWRD_LEN - 1, PasswordString.data(), STICK20_PASSOWRD_LEN);
  Data[STICK20_PASSOWRD_LEN + 1] = 0;

  communicationSuccess = cryptostick->stick20SendPassword(Data);
  if (!communicationSuccess) {
    csApplet->warningBox(tr("There was a problem during communicating with device. Please retry."));
    return false;
  }

  bool isOldPasswordCorrect = CheckResponse(TRUE) == 1;
  if (!isOldPasswordCorrect) {
    csApplet->warningBox(tr("Current password is not correct. Please retry."));
    return false;
  }

  // Change password
  PasswordString = ui->lineEdit_NewPW_1->text().toLatin1();

  STRNCPY((char *)&Data[1], STICK20_PASSOWRD_LEN, PasswordString.data(), STICK20_PASSOWRD_LEN);
  Data[STICK20_PASSOWRD_LEN + 1] = 0;

  communicationSuccess = cryptostick->stick20SendNewPassword(Data);
  if (!communicationSuccess) {
    csApplet->warningBox(tr("There was a problem during communicating with device. Please retry."));
    return false;
  }

  bool isNewPasswordCorrect = CheckResponse(FALSE) == 1;
  if (!isNewPasswordCorrect) {
    csApplet->warningBox(tr("New password is not correct. Please retry."));
    return false;
  }
  csApplet->messageBox(tr("New password is set"));
  return true;
}