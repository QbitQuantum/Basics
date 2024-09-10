bool SimpleRegion::intersects(SimpleRegion obstacle) {
  return (
    (
      (x1() <= obstacle.x1() && obstacle.x1() <= x2())
      ||
      (x1() <= obstacle.x2() && obstacle.x2() <= x2())
    )
    &&
    (
      (y1() <= obstacle.y1() && obstacle.y1() <= y2())
      ||
      (y1() <= obstacle.y2() && obstacle.y2() <= y2())
    )
  );
}