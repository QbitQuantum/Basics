void QuizFrame::setTerm( const Term& term ) {
    Translation firstLangTranslation = term.getTranslation( controller->getQuizFirstLanguage() );
    Translation testLangTranslation = term.getTranslation( controller->getQuizTestLanguage() );

    const QString firstLangWord = firstLangTranslation.getWord();
    const QString testLangAlt = testLangTranslation.getAlt();
    const QString testLangWord = testLangTranslation.getWord();

    QString comment;
    BilingualKey commentKey( controller->getQuizFirstLanguage(), controller->getQuizTestLanguage() );
    if( term.isCommentExists( commentKey ) )
        comment = term.getComment( commentKey );

    firstLangTermLineEdit->setText( firstLangWord );
    firstLangTermLineEdit->setCursorPosition( 0 );

    testLangTermAltLineEdit->setText( testLangAlt );
    testLangTermAltLineEdit->setCursorPosition( 0 );

    testLangTermLineEdit->setText( testLangWord );
    testLangTermLineEdit->setCursorPosition( 0 );

    commentMultiLineEdit->setText( comment );

    Folder* vocabTree = controller->getVocabTree();
    Vocabulary* vocab = vocabTree->getVocabulary( term.getVocabId() );
    if( vocab ) {
        QString absPath = controller->getResolvedImagePath( term.getImagePath(), *vocab );
        setImage( absPath ); 
    }
}