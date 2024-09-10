void pmove(void) 
{
  int i,j;
  double dir, dx,dy ;

    if (rotcore) 
      for (j =0; j < 4; j++)
	for (i =0; i < 4; i++) {
	  dir =(atan2((double) (planets[pl_core[j][i]].pl_y - planets[pl_home[j]].pl_y),
                       (double) (planets[pl_core[j][i]].pl_x - planets[pl_home[j]].pl_x))
                 );
	  if (dir > pi) dir = dir - 2.0*pi;
	  if (dir >= 0.0)
	     dir = (dir*incrementrecip+1.5);
	  else
	     dir = (dir*incrementrecip+0.5);
          planets[pl_core[j][i]].pl_x = planets[pl_home[j]].pl_x + pl_dist1[j][i] * COS(dir);
          planets[pl_core[j][i]].pl_y = planets[pl_home[j]].pl_y + pl_dist1[j][i] * SIN(dir);
	  dx = (double) (planets[pl_core[j][i]].pl_x - GWIDTH/2);
	  dy = (double) (GWIDTH/2 - planets[pl_core[j][i]].pl_y);
	  pl_dist[i] = sqrt(dx * dx + dy * dy);
          planets[pl_core[j][i]].pl_flags |= PLREDRAW;
        }

    if (rotall) 
      for (i = 0; i < MAXPLANETS; i++) {
	dir = atan2((double) (planets[i].pl_y - GWIDTH/2),
		    (double) (planets[i].pl_x - GWIDTH/2));
/*	printf("Atan2 Dir is %f (%d,%d).\n", dir, planets[i].pl_x,
	       planets[i].pl_y);*/
	if (dir > pi) dir = dir - 2.0*pi;
/*	printf("dir = %f, dir*100 = %f, rint() = %f. %f = %d.\n", dir, dir*100.0, rint(dir*100.0), rint(dir*100.0+1.5), (int) (rint(dir*100.0) + 1.0));*/
	if (dir >= 0.0)
	    dir = (dir*incrementrecip+1.5);
	else
	    dir = (dir*incrementrecip+0.5);

	planets[i].pl_x = GWIDTH/2 + (int) (pl_dist[i] * COS(dir));
	planets[i].pl_y = GWIDTH/2 + (int) (pl_dist[i] * SIN(dir));

	planets[i].pl_flags |= PLREDRAW;
      }
}