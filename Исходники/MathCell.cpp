/***
 * Find the first cell in rectangle rect in this line.
 */
void MathCell::SelectFirst(wxRect& rect, MathCell** first)
{
  if (rect.Intersects(GetRect(false)))
    *first = this;
  else if (m_nextToDraw != NULL)
    m_nextToDraw->SelectFirst(rect, first);
  else
    *first = NULL;
}