QString generalFunctions::getOutputFromFileMimeCmd(QString file, QString mimeArg)
{
    try {
      QProcess *process = new QProcess();
      QStringList *args = new QStringList();
      args->append("--brief");
      args->append(mimeArg);
      args->append(file);
      process->start("file", *args);
      if(process->waitForStarted(2000))
      {
          process->closeWriteChannel();
          process->waitForFinished(2000);
          QByteArray qba = process->readAll();
          QTextCodec *codec = QTextCodec::codecForLocale();
          QTextDecoder *decoder = codec->makeDecoder();
          QString result = decoder->toUnicode(qba);

          delete args;
          delete decoder;
          delete process;

          result = result.trimmed();
          return result;
      } else
      {
          return "";
      }

    }
    catch (...) {
       return "";
    }
}