void CustomColorButton::usePopupGrid(bool bGrid)
{
   if (bGrid == true)
   {
      setMenu(mpMenu);
      setPopupMode(QToolButton::MenuButtonPopup);
   }
   else
   {
      setMenu(NULL);
      setPopupMode(QToolButton::DelayedPopup);
   }
}