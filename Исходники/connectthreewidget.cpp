const boost::shared_ptr<ribi::TextCanvas> ribi::con3::ConnectThreeWidget::ToTextCanvas() const noexcept
{
  assert(m_game);
  const int n_cols { m_game->GetCols() };
  const int n_rows { m_game->GetCols() };

  const boost::shared_ptr<TextCanvas> canvas {
    new TextCanvas(n_cols,n_rows)
  };
  for (int y=0; y!=n_rows; ++y)
  {
    for (int x=0; x!=n_cols; ++x)
    {
      char c = ' ';
      switch (m_game->GetSquare(x,y))
      {
        case Square::empty  : c = (x + y % 2 ? '.' : ' '); break;
        case Square::player1: c = 'O'; break;
        case Square::player2: c = 'X'; break;
        case Square::player3: c = 'A'; break;
        default:
          assert(!"Should not get here");
      }
      canvas->PutChar(x,y,c);
    }
  }

  const char c = canvas->GetChar(m_x,m_y);
  char d = ' ';
  switch (c)
  {
    case ' ': d = '.'; break;
    case '.': d = ' '; break;
    case 'O': d = 'o'; break;
    case 'X': d = 'x'; break;
    case 'A': d = 'a'; break;
    case 'o': d = 'O'; break;
    case 'x': d = 'X'; break;
    case 'a': d = 'A'; break;
  }
  canvas->PutChar(m_x,m_y,d);
  return canvas;
}