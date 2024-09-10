bool OpenBook::load(const char * fname, const Board & i_board)
{
  QFile qf(fname);
  if ( !qf.open(QIODevice::ReadOnly) )
    return false;

  QTextStream sbook(&qf);

  if ( sbook.status() != QTextStream::Ok )
    return false;

  UndoInfo tundo[Board::GameLength];

  for ( ; !sbook.atEnd(); )
  {
    QString sline = sbook.readLine();
    if ( sline.isEmpty() )
      break;

    Board board = i_board;
    board.set_undoStack(tundo);
    board.fromFEN(0);

    MovesLine moves;
    QStringList slist = sline.split( QObject::tr(" "), QString::SkipEmptyParts);
    for (QStringList::iterator it = slist.begin(); it != slist.end(); ++it)
    {
      Move move;
      if ( !strToMove(it->toAscii().data(), board, move) || !board.validateMove(move) )
        break;

      board.makeMove(move);
      moves.push_back(move);
    }

    mtable_.push_back(moves);
  }

  return true;
}