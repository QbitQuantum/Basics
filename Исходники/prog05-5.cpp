//--------------------------------------------------------------------------
// WindowProc() -> Processa as mensagens enviadas para o programa
//--------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  // Variáveis para manipulação da parte gráfica do programa
  HDC hDC = NULL;
  PAINTSTRUCT psPaint;

  // Canetas e pincéis
  HPEN hPen = NULL;
  HPEN hPenOld = NULL;
  HBRUSH hBrush = NULL;
  HBRUSH hBrushOld = NULL;
  
  // Verifica qual foi a mensagem enviada
  switch(uMsg)
  {

    case WM_CREATE: // Janela foi criada
    {
      // Retorna 0, significando que a mensagem foi processada corretamente
      return(0);
    } break;
	
    case WM_PAINT: // Janela (ou parte dela) precisa ser atualizada
    {
	  // Obtém identificador do DC e preenche PAINTSTRUCT
      hDC = BeginPaint(hWnd, &psPaint);

	  // Cria e seleciona nova caneta no DC e salva caneta antiga
	  hPen = CreatePen(PS_SOLID, 1, RGB(0, 128, 0));
	  hPenOld = (HPEN)SelectObject(hDC, hPen);

	  // Cria e seleciona novo pincel no DC e salva pincel antigo
	  hBrush = CreateSolidBrush(RGB(255, 255, 0));
	  hBrushOld = (HBRUSH)SelectObject(hDC, hBrush);

	  // Desenha elipse
	  Ellipse(hDC, 80, 100, 180, 200);

	  // Desenha combinação de arco e corda
	  Chord(hDC, 10, 10, 100, 100, 80, 80, 50, 25);

	  // Desenha "pizza"
	  Pie(hDC, 110, 10, 200, 100, 180, 80, 150, 25);

	  // Desenha "pizza" no formato Pac-Man
	  Pie(hDC, 210, 10, 400, 200, 380, 50, 380, 130);

	  // Restaura pincel antigo e deleta novo pincel
	  SelectObject(hDC, hBrushOld);
	  DeleteObject(hBrush);

	  // Restaura caneta antiga e deleta nova caneta
	  SelectObject(hDC, hPenOld);
	  DeleteObject(hPen);

	  // Libera DC e valida área
      EndPaint(hWnd, &psPaint);

      return(0);
    } break;

    case WM_CLOSE: // Janela foi fechada
    {
      // Destrói a janela
      DestroyWindow(hWnd);

      return(0);
    } break;
	
    case WM_DESTROY: // Janela foi destruída
    {
      // Envia mensagem WM_QUIT para o loop de mensagens
      PostQuitMessage(0);

      return(0);
    } break;

    default: // Outra mensagem
    {
      /* Deixa o Windows processar as mensagens que não foram verificadas na função */
	  return(DefWindowProc(hWnd, uMsg, wParam, lParam));
    }

  }
}