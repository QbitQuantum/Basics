 void MapNetwork::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
 {
     qDebug() << "Proxy Aut req" << proxy.hostName() << &authenticator;
     QDialog dialog;
     QGridLayout layout;
     QLabel username, password;
     username.setText("Username:"******"Password:"******"OK");
     connect(&button, SIGNAL(clicked()), &dialog, SLOT(accept()));
     layout.addWidget(&button, 2, 0, 1, 2, Qt::AlignCenter);
     dialog.setLayout(&layout);
     dialog.exec();
     authenticator->setUser(user.text());
     authenticator->setPassword(pass.text());
 }