void CSpaceInvadersAppView::DrawShip(CWindowGc& aGc) const
{
    // Draw the image in the desired position
    TPoint shipPoint(iShip->X(), iShip->Y());
    aGc.BitBlt( shipPoint, iBitmapShip);

    if ( iShip->HasFired() )
    {
        TPoint shotPoint(iShip->Shot()->X(), iShip->Shot()->Y());
        aGc.BitBlt( shotPoint, iBitmapShot );
    }
}