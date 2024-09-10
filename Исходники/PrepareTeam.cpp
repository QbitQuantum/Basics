void PrepareTeam::doDraw( Surface& dest )
{
    menuImage.bltTrans(dest, menuImageXY.x, menuImageXY.y); // blit full
    dest.FillRoundRect(rect, 12, ctWindowsbackground);
    dest.RoundRect(rect,12, ctWindowsBorder);

//    DrawInfo(dest);
//    drawTeams(dest);
//    vsImage.bltTrans(dest, firstrect.max.x+40, firstrect.max.y-vsImage.getHeight()-10);
//    StateTeam1->UpdateState(false);
//    StateTeam2->UpdateState(false);
    
    View::doDraw( dest );
}