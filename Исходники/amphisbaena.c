/* The following function is the very core of the simulation.
 * When called, it does the following:-
 *  Pick a random snake
 *  Choose which end will be the 'head'
 *  Choose a random direction for the head to 'move in'
 *  If that location is not free, return immediately.
 *  Otherwise, calculated the Energy of the snakes in the new 'shifted' position versus the current configuration.
 *  Compare this energy shift with an energy randomly pulled from a Boltzmann distribution of temperature/energy
 *  If energetically favourable, move the snake.
 *  Otherwise, put the tail back in place
 *  Return!
 */
void
wriggle ()
{
  int s, head, heads, tail;
  int dx, dy, dz;
  int x, y, z;
  double dE = 0.0;
  struct coord h, t;
  int mat, i;

  s = rand_int (num_snakes);
  //choose a snake at random

  heads = -rand_int (2);
  //change this to use dedicated bit random generator
  // i.e.heads = 0, -1 with equal prob.

  dx = dy = dz = 0;
  switch (rand_int (6) + 1)
    //choose which of 6 directions to attempt wriggle in
    {
    case 1:
      dx = 1;
      break;
    case 2:
      dx = -1;
      break;
    case 3:
      dy = 1;
      break;
    case 4:
      dy = -1;
      break;
    case 5:
      dz = 1;
      break;
    case 6:
      dz = -1;
      break;
    }

//  fprintf(stderr,"\nWriggle: s: %d\t head: %d\theads: %d\t (dx,dy,dz): %d %d %d\n", s, snakes[s].head, heads, dx, dy, dz);

  head = snakes[s].head + heads; //Either choose head1, where the .head points to, 
                                 //or the tail/head2 to act as head this time

  if (head >= snakes[s].segs) //The Oroborus datatype is circular, so wrap around...
    head = 0;
  if (head < 0)
    head = snakes[s].segs - 1;

//  printf("head: %d\t tail:%d\n", head, tail);
  x = snakes[s].oroborus[head].x;
  y = snakes[s].oroborus[head].y;
  z = snakes[s].oroborus[head].z;

  if (x + dx < 0 || x + dx >= X
      || y + dy < 0 || y + dy >= Y 
      || z + dz < 0 || z + dz >= Z)
    return;
  //not allowed lattice location !
  //The majority of calls to this function will have returned at this point, 
  // so the above code is stripped to the bare essentials to reach here as quickly as possible
  
  //Now we can calculate other variables necessary to actually move the snake - like the tail location;

  if (heads < 0)
    tail = head + 1; //tail location before head i.e.going forwards
  else
    tail = head - 1; //tail location after head i.e.going backwards

  if (tail >= snakes[s].segs) //The Oroborus datatype is circular, so wrap around...
    tail = 0;
  if (tail < 0)
    tail = snakes[s].segs - 1;
   
   
  lattice[snakes[s].oroborus[tail].x]
    [snakes[s].oroborus[tail].y][snakes[s].oroborus[tail].z] = -1;
  //i.e.Tail moves out of the way first
  // This is so that the 'head' can follow the tail around in a closed circle
  // I this allows enclosed / boxed-in snakes to 'cycle' around and then escape

  if (lattice[x + dx][y + dy][z + dz] == -1)
    //gap where head is being forced
    // i.e.move is PHYSICALLY possible now need to see whether ENERGETICALLY FAVOURABLE
    {
//      fprintf(stderr,"Space at: (x,y,z) %d %d %d\n", x + dx, y + dy, z + dz);
      //printf("c");

      h.x = x + dx; //h is new head location
      h.y = y + dy;
      h.z = z + dz;
      
      //maybe just copy the pointer to coord ?
      t.x = snakes[s].oroborus[tail].x; //t is tail location
      t.y = snakes[s].oroborus[tail].y;
      t.z = snakes[s].oroborus[tail].z;

      dE = 0.0;
      for (i = 1; i <= 6; i++)
	//all 6 directions
	{
	  dx = dy = dz = 0;
	  switch (i)
	    {

	    case 1:
	      dx = 1;
	      break;
	    case 2:
	      dx = -1;
	      break;
	    case 3:
	      dy = 1;
	      break;
	    case 4:
	      dy = -1;
	      break;
	    case 5:
	      dz = 1;
	      break;
	    case 6:
	      dz = -1;
	      break;
	    }

	   //NB: Energy change as a result of where the new head is going affect the overall snake positively
	   //Enthalpy of where the tail used to be affects the overall energy negatively
	  if (h.x + dx >= 0 && h.x + dx < X	// if prospective interaction site within lattice
	      && h.y + dy >= 0 && h.y + dy < Y
	      && h.z + dz >= 0 && h.z + dz < Z)
	    {
	      if (lattice[h.x + dx][h.y + dy][h.z + dz] == -1)
		mat = 0;  //if empty lattice site material 0[non snake]
	      else
		mat = 1;  //if snake material type 1[snake type]
	      dE += iE[1][mat] - iE[0][mat];

	      if (lattice[h.x + dx][h.y + dy][h.z + dz] == snakes[s].id) //if touching ourselves
		dE += iE[1][mat] - iE[0][mat];
	      //count energy change twice - once for head
	      //segment interaction and once for segment head interaction
	    }

	  if (t.x + dx >= 0 && t.x + dx < X	// if prospective interaction site within lattice
	      && t.y + dy >= 0 && t.y + dy < Y
	      && t.z + dz >= 0 && t.z + dz < Z)
	    {

	      if (lattice[t.x + dx][t.y + dy][t.z + dz] == -1)
		mat = 0;   //if empty lattice site, material 0[non snake]
	      else
		mat = 1;   //if snake material type 1[snake type] 
	      dE += iE[0][mat] - iE[1][mat];

	      if (lattice[t.x + dx][t.y + dy][t.z + dz] == snakes[s].id)
		dE += iE[0][mat] - iE[1][mat];
	      //if touching ourselves count energy change twice - 
	      //once for head-segment interaction
	      // and once for segment-head interaction}
	    }
	   
	   //SUBSTRATE substrate interactions
	   if (t.z+dz<0) //added JMF 22-1-07
	     dE-=500000.0;
	   if (h.z+dz<0)
	     dE+=500000.0;
	}

//      fprintf(stderr, "dE: %f\t", dE);

      if (dE > 0.0 || exp(dE * beta) > rand_float ())
	//if dE exothermic, reaction progresses automatically
	//or if sufficient boltzmann energy to drive endothermic reaction
	{
//	   fprintf(stderr,"Going! (x,y,z) %d %d %d\n",h.x,h.y,h.z);
	   
	  lattice[h.x][h.y][h.z] = snakes[s].id;
	  //mark new head location on lattice
//	   print_lattice();
	   
	  if (heads < 0)
	    {
	      //forwards 
	      snakes[s].head = (tail + 1) % snakes[s].segs;
	    }
	  else
	    snakes[s].head = tail;

	  snakes[s].oroborus[tail].x = h.x;	//tail now becomes new head...
	  snakes[s].oroborus[tail].y = h.y;
	  snakes[s].oroborus[tail].z = h.z;
	}
      else
	{
//	   fprintf(stderr,"Holding!\n");
	  lattice[snakes[s].oroborus[tail].x]
	    [snakes[s].oroborus[tail].y]
	    [snakes[s].oroborus[tail].z] = snakes[s].id;
	  //i.e.Tail put back in location
	}

    }
  else
    {
      lattice[snakes[s].oroborus[tail].x]
	[snakes[s].oroborus[tail].y]
	[snakes[s].oroborus[tail].z] = snakes[s].id;
      //i.e.Tail put back in location


      // printf("f");
      //printf("No space at: (x,y,z) %d %d %d\n", x + dx, y + dy, z + dz);
    }

}