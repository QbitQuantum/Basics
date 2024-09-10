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
	  hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	  hPenOld = (HPEN)SelectObject(hDC, hPen);

	  // Move “cursor invisível” para (100, 100)
	  MoveToEx(hDC, 100, 100, NULL);
	  // Desenha quatro retas, formando um losango
	  LineTo(hDC, 70, 120);
	  LineTo(hDC, 100, 140);
	  LineTo(hDC, 130, 120);
	  LineTo(hDC, 100, 100);

	  // Define pontos do losango
	  POINT ptLosango[4];
	  ptLosango[0].x = 20;
	  ptLosango[0].y = 70;
	  ptLosango[1].x = 50;
	  ptLosango[1].y = 90;
	  ptLosango[2].x = 80;
	  ptLosango[2].y = 70;
	  ptLosango[3].x = 50;
	  ptLosango[3].y = 50;

	  // Move “cursor invisível” para (50, 50)
	  MoveToEx(hDC, 50, 50, NULL);
	
	  // Desenha quatro retas formadas pelos pontos do vetor ptLosango[4],
	  // formando o losango
	  PolylineTo(hDC, ptLosango, 4);

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