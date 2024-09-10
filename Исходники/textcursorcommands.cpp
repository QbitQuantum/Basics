  /*!
     * \class TextCursorChangeFontColor
   * \author Anders Fernström
   * \date 2005-11-03
   * \date 2006-01-13 (update)
     *
     * \brief Command for changing font color
   *
   * 2005-11-07 AF, implemented the function
   * 2005-11-15 AF, added trick to get correct style on links
   * 2006-01-13 AF, remove trick to get correct style on links because
   * it made undo/redo work incorrectly
     */
  void TextCursorChangeFontColor::execute()
  {
    QTextEdit *editor = document()->getCursor()->currentCell()->textEdit();

    if( editor )
    {
      editor->setTextColor( color_ );


      // ugly trick to make the sure that the links haven't change
      // color
      /*
      if( !editor->toPlainText().isEmpty() )
      {
        int start = editor->textCursor().selectionStart();
        int end = editor->textCursor().selectionEnd();
        editor->setHtml( editor->toHtml() );

        QTextCursor cursor( editor->textCursor() );
        cursor.setPosition( start );
        cursor.setPosition( end, QTextCursor::KeepAnchor );
        editor->setTextCursor( cursor );
      }
      */
    }
  }