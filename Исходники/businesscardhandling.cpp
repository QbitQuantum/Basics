void BusinessCardHandling::saveAvatar(const QString filename, QPixmap p, QContact& contact)
{

    // Path to store avatar picture
    QString path;
#ifdef Q_OS_SYMBIAN
    path.append("c:/System/");
#endif
    path.append(filename);

    // Remove same file if exists
    QFile file;
    if (file.exists(path))
        file.remove(path);

    // Save pixmap into file
    bool saveRet = p.save(path);

    if (saveRet) {
        // Create avatar
        QContactAvatar contactAvatar;
        contactAvatar.setImageUrl(QUrl(path));
        bool saveAvatar = contact.saveDetail(&contactAvatar);

        // Save contact
        if (saveAvatar)
            m_contactManager->saveContact(&contact);

        // NOTE: Do not remove picture, system needs it for showing avatar
        // Remove picture file
        //bool removeRet = file.remove(path);
    }
}