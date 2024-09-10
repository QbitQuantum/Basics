double QgsComposerHtml::findNearbyPageBreak( double yPos )
{
  if ( !mWebPage || !mRenderedPage || !mUseSmartBreaks )
  {
    return yPos;
  }

  //convert yPos to pixels
  int idealPos = yPos * htmlUnitsToMM();

  //if ideal break pos is past end of page, there's nothing we need to do
  if ( idealPos >= mRenderedPage->height() )
  {
    return yPos;
  }

  int maxSearchDistance = mMaxBreakDistance * htmlUnitsToMM();

  //loop through all lines just before ideal break location, up to max distance
  //of maxSearchDistance
  int changes = 0;
  QRgb currentColor;
  bool currentPixelTransparent = false;
  bool previousPixelTransparent = false;
  QRgb pixelColor;
  QList< QPair<int, int> > candidates;
  int minRow = qMax( idealPos - maxSearchDistance, 0 );
  for ( int candidateRow = idealPos; candidateRow >= minRow; --candidateRow )
  {
    changes = 0;
    currentColor = qRgba( 0, 0, 0, 0 );
    //check all pixels in this line
    for ( int col = 0; col < mRenderedPage->width(); ++col )
    {
      //count how many times the pixels change color in this row
      //eventually, we select a row to break at with the minimum number of color changes
      //since this is likely a line break, or gap between table cells, etc
      //but very unlikely to be midway through a text line or picture
      pixelColor = mRenderedPage->pixel( col, candidateRow );
      currentPixelTransparent = qAlpha( pixelColor ) == 0;
      if ( pixelColor != currentColor && !( currentPixelTransparent && previousPixelTransparent ) )
      {
        //color has changed
        currentColor = pixelColor;
        changes++;
      }
      previousPixelTransparent = currentPixelTransparent;
    }
    candidates.append( qMakePair( candidateRow, changes ) );
  }

  //sort candidate rows by number of changes ascending, row number descending
  qSort( candidates.begin(), candidates.end(), candidateSort );
  //first candidate is now the largest row with smallest number of changes

  //ok, now take the mid point of the best candidate position
  //we do this so that the spacing between text lines is likely to be split in half
  //otherwise the html will be broken immediately above a line of text, which
  //looks a little messy
  int maxCandidateRow = candidates[0].first;
  int minCandidateRow = maxCandidateRow + 1;
  int minCandidateChanges = candidates[0].second;

  QList< QPair<int, int> >::iterator it;
  for ( it = candidates.begin(); it != candidates.end(); ++it )
  {
    if (( *it ).second != minCandidateChanges || ( *it ).first != minCandidateRow - 1 )
    {
      //no longer in a consecutive block of rows of minimum pixel color changes
      //so return the row mid-way through the block
      //first converting back to mm
      return ( minCandidateRow + ( maxCandidateRow - minCandidateRow ) / 2 ) / htmlUnitsToMM();
    }
    minCandidateRow = ( *it ).first;
  }

  //above loop didn't work for some reason
  //return first candidate converted to mm
  return candidates[0].first / htmlUnitsToMM();
}