PRBool nsWinGesture::EndPanningFeedback(HWND hWnd)
{
  if (!beginPanningFeedback)
    return PR_FALSE;

  return endPanningFeedback(hWnd, TRUE);
}