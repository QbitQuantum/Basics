static void tracer_invariant(recel_tracer *t)
{
  int32_t x0 = t->x, y0 = t->y;

  char dx = t->dx, dy = t->dy;
  assert (dx == 0 || dy == 0);
  assert (!(dx == 0 && dy == 0));

  int32_t x1 = x0 + dx * t->n, y1 = y0 + dy * t->n;

  // Line is in shape
  assert (DISTANCE(x0, y0) >= t->level);
  assert (DISTANCE(x1, y1) >= t->level);

  // Extremities are corner
  assert (DISTANCE(x0 - dx, y0 - dy) < t->level ||
          DISTANCE(x0 - dy, y0 + dx) < t->level);

  assert (DISTANCE(x1 + dx, y1 + dy) < t->level ||
          DISTANCE(x1 - dy, y1 + dx) < t->level);
}