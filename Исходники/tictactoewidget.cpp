const boost::shared_ptr<ribi::TextCanvas> ribi::TicTacToeWidget::ToTextCanvas() const noexcept
{
  const boost::shared_ptr<TextCanvas> canvas {
    m_tictactoe->ToTextCanvas()
  };
  assert(canvas);

  if (m_tictactoe->GetWinner() == TicTacToe::player1 || m_tictactoe->GetWinner() == TicTacToe::player2)
  {
    for (int i=0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        canvas->PutChar(i,j, m_tictactoe->GetWinner() == TicTacToe::player1 ? 'X': 'O');
      }
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
    case 'o': d = 'O'; break;
    case 'x': d = 'X'; break;
  }
  canvas->PutChar(m_x,m_y,d);
  return canvas;
}