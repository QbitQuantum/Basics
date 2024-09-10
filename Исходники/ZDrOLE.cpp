void
ZDrOleClient::OnGetItemPosition( CRect& rPosition )
{
   ASSERT_VALID( this );

   // During in-place activation, ZDrOleClient::OnGetItemPosition
   // will be called to determine the location of this item.  The default
   // implementation created from AppWizard simply returns a hard-coded
   // rectangle.  Usually, this rectangle would reflect the current
   // position of the item relative to the view used for activation.
   // You can obtain the view by calling ZDrOleClient::GetActiveView.

   // TODO: return correct rectangle (in pixels) in rPosition

   if ( m_bFullClient )
   {
      CView *pParentView = GetParentView( );
      if ( pParentView )
      {
         pParentView->GetClientRect( &rPosition );
         rPosition.left = m_pAttr->X;
         rPosition.top = m_pAttr->Y;
      }
      else
         rPosition = GetRect( );
   }
   else
   {
      rPosition = GetRect( );
   }
}