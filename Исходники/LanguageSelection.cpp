bool LanguageSelection::loadTranslations(const TranslationInfoList& translations)
{
  unloadTranslations();
  resizeTranslatorsList(translations.count());
  for(int i=0; i < translations.count(); ++i){
    if( mTranslators[i]->load(translations.at(i).absoluteFilePath()) ){
      QCoreApplication::installTranslator(mTranslators[i].get());
    }else{
      const auto msg = tr("Could not load translation file '%1'.")
                       .arg(translations.at(i).fullFileName());
      auto error = mdtErrorNewQ(msg, Mdt::Error::Warning, this);
      setLastError(error);
      qWarning() << QLatin1String("Mdt::Translation::LanguageSelection::loadTranslations(): ") << msg;
      //error.commit(); Error logger will crash (because logging is not enabled, have to fix it in Mdt::Error)
    }
  }

  return true;
}