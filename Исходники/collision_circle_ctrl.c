void draw(void *_prms)
{
  param_set *p = (param_set *) _prms;
  int i;
  double psc = 2 * R / Hmax, vdistmax;

  gclr(*p->win);
  copylayer(*p->win, 2, 1);
  for (i = 0; i < DN; i++) {
    putimg24m(*p->win, x[i] - 4, y[i] - 4, 8, 8, Xpm_image_stone4);
  }
  copylayer(*p->win, 1, 0);

  gclr(*p->win2);
  vdistmax = vdist[0];
  for (i = 0; i < Hmax; i++) {
    if (vdistmax < vdist[i])
      vdistmax = vdist[i];
  }
  newcolor(*p->win2, "steelblue4");
  for (i = 0; i < Hmax; i++) {
    fillrect(*p->win2, psc * i, 0, psc, vdist[i] / vdistmax * R);
  }
  newcolor(*p->win2, "steelblue");
  for (i = 0; i < Hmax; i++) {
    drawrect(*p->win2, psc * i, 0, psc, vdist[i] / vdistmax * R);
  }
  copylayer(*p->win2, 1, 0);
}