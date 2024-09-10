void MoveShot( int i )
{
  // We're going to test if the far end of the shot is off the screen yet (that's why we add ShotLen)
  int dist = Shots[i].dist + ShotLen + 1;

  int a = Shots[i].ang << 7;  // scale the angle value back up from when we stored it

  // Compute the rotated location of the shot
  int x = ( Sin(a) * dist + 32768) / 65536;
  int y = (-Cos(a) * dist + 32768) / 65536;

  // If the rotated x or y are outside the range of the display, the shot has gone off the screen
  if( abs(x) >= Width || abs(y) >= Height )
  {
    // out of bounds - remove this shot from the active list
    UsedShots--;
    FreeShots++;

    // Do we still have any shots that are active?
    if( UsedShots )
    {
      // Copy the data for the LAST active shot into this spot in the shots array
      // This compacts the list.
      memcpy( Shots + i, Shots + UsedShots, sizeof(SHOT) );

      // Because we just moved the LAST shot in the list to this spot in the Shots array,
      // the moved entry would get skipped by the updating code, because it has no idea
      // that we changed the list order.  We call MoveShot AGAIN, on the updated entry, so it doesn't get missed.
      // This is overkill for a simple demo, but it's good to know that this kind of thing happens.  :)
      MoveShot( i );
    }
  }
  else
  {
    Shots[i].dist = dist;
  }
}