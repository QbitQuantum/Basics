void MainWindow::onRetroArchUpdateDownloadFinished()
{
   QNetworkReply *reply = m_updateReply.data();
   QNetworkReply::NetworkError error;
   int code;

   m_updateProgressDialog->cancel();

   /* At least on Linux, the progress dialog will refuse to hide itself and will stay on screen in a corrupted way if we happen to show an error message in this function. processEvents() will sometimes fix it, other times not... seems random. */
   qApp->processEvents();

   if (!reply)
      return;

   error = reply->error();
   code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

   if (m_updateFile.isOpen())
      m_updateFile.close();

   if (code != 200)
   {
      emit showErrorMessageDeferred(QString(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_NETWORK_ERROR)) + ": HTTP Code " + QString::number(code));
      RARCH_ERR("[Qt]: RetroArch update failed with HTTP status code: %d\n", code);
      reply->disconnect();
      reply->abort();
      reply->deleteLater();
      return;
   }

   if (error == QNetworkReply::NoError)
   {
      int index = m_updateFile.fileName().lastIndexOf(PARTIAL_EXTENSION);
      QString newFileName = m_updateFile.fileName().left(index);
      QFile newFile(newFileName);

      /* rename() requires the old file to be deleted first if it exists */
      if (newFile.exists() && !newFile.remove())
         RARCH_ERR("[Qt]: RetroArch update finished, but old file could not be deleted.\n");
      else
      {
         if (m_updateFile.rename(newFileName))
         {
            RARCH_LOG("[Qt]: RetroArch update finished downloading successfully.\n");
            emit extractArchiveDeferred(newFileName);
         }
         else
         {
            RARCH_ERR("[Qt]: RetroArch update finished, but temp file could not be renamed.\n");
            emit showErrorMessageDeferred(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_COULD_NOT_RENAME_FILE));
         }
      }
   }
   else
   {
      QByteArray errorArray = reply->errorString().toUtf8();
      const char *errorData = errorArray.constData();

      RARCH_ERR("[Qt]: RetroArch update ended prematurely: %s\n", errorData);
      emit showErrorMessageDeferred(QString(msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QT_NETWORK_ERROR)) + ": Code " + QString::number(code) + ": " + errorData);
   }

   reply->disconnect();
   reply->close();
   reply->deleteLater();
}