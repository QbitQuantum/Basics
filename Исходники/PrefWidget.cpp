void PrefWidget::onChangeClicked()
{
  std::string pass1(password1->text().toUTF8());
  std::string pass2(password2->text().toUTF8());
  if (pass1 != pass2)
  {
    errorText->show();
  }
  else
  {
    errorText->hide();

    QSharedPointer<std::vector<QSharedPointer<common::User> > > users =
      common::DbSession::getInstance().getUsers();

    for (int i = 0; i < users->size(); i++)
    {
      QSharedPointer<loader::User> user = users->at(i).
        dynamicCast<loader::User>();

      std::string token = user->getToken();
      if (m_token == token)
      {
        user->setPassword(pass1);
        common::DbSession::getInstance().storeUser(user);
        break;
      }
    }
    password1->setText("");
    password2->setText("");
  }
}