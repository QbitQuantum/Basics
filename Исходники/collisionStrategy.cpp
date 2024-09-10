bool PerPixelCollisionStrategy::execute(
      const Drawable& obj1, const Drawable& obj2) const {

  RectangularCollisionStrategy strategy;
  if ( not strategy.execute(obj1, obj2) ) return false;
  // If we got this far, we know that the sprite rectangles intersect!

  Vector2f p1 = obj1.getPosition();
  Vector2f p2 = obj2.getPosition();
  const Frame * const frame1 = obj1.getFrame();
  const Frame * const frame2 = obj2.getFrame();

  int o1Left = p1[0]; 
  int o1Right = o1Left+frame1->getWidth();

  int o2Left = p2[0]; 
  int o2Right = o2Left+frame2->getWidth();
  std::vector<int> sides;
  sides.reserve(4);
  sides.push_back( o1Left );
  sides.push_back( o1Right );
  sides.push_back( o2Left );
  sides.push_back( o2Right );
  std::sort( sides.begin(), sides.end() );

  int o1Up = p1[1];
  int o1Down = o1Up+frame1->getHeight();
  int o2Up = p2[1];
  int o2Down = o2Up+frame2->getHeight();
  std::vector<int> lids;
  lids.reserve(4);
  lids.push_back( o1Up );
  lids.push_back( o1Down );
  lids.push_back( o2Up );
  lids.push_back( o2Down );
  std::sort( lids.begin(), lids.end() );

  SDL_Surface* surface1 = frame1->getSurface();
  SDL_Surface* surface2 = frame2->getSurface();
  SDL_LockSurface(surface1);
  SDL_LockSurface(surface2);
  unsigned pixels1;
  unsigned pixels2;
  for (int i = sides[1]; i < sides[2]; ++i) {
    for (int j = lids[1]; j < lids[2]; ++j) {
      // check pixels in obj1 and obj2!
      pixels1 = obj1.getPixel(i, j);
      pixels2 = obj2.getPixel(i, j);
      if ( pixels1 != surface1->format->colorkey && 
           pixels2 != surface2->format->colorkey) {
        SDL_UnlockSurface(surface1);
        SDL_UnlockSurface(surface2);
        return true;
      }
    }
  }
  SDL_UnlockSurface(surface1);
  SDL_UnlockSurface(surface2);

  return false;
}