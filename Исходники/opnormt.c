static void* worker(tdat_t *td)
{

#ifdef HAVE_SIGNAL_H

  /* set this thread as cancellable */

  if (set_cancellable() != 0)
    {
      td->status = OPNORM_THREAD;
      return NULL;
    }

#endif

  /*
    unpack arguments, mostly for readability but also saves
    a few dereferences
  */

  tdat_shared_t *ts = td->shared;

  index_t
    n = ts->n,
    m = ts->m;

  double
    p    = ts->p,
    q    = ts->q,
    eps  = ts->eps,
    LCRP = ts->LCRP,
    SCD  = ts->SCD;

  const double *M = ts->M;

  fifo_t *fifo = ts->fifo;

  /* working data */

  double  pcent[n];
  cube_t  cube0, cube1;
  patch_t patch;
  double  tmax = 0.0;

  patch.centres = pcent;

  int fifoerr;

  while (1)
    {
      /* thread cancellation point  */

      pthread_testcancel();

      /* dequeue a cube */

      if (pthread_mutex_lock(&(ts->fifolock)) < 0)
	{
	  td->status = OPNORM_THREAD;
	  return NULL;
	}

      fifoerr = fifo_dequeue(fifo, &cube0);

      if (pthread_mutex_unlock(&(ts->fifolock)) < 0)
	{
	  td->status = OPNORM_THREAD;
	  return NULL;
	}

      if (fifoerr != FIFO_OK)
	{
	  td->status = (fifoerr == FIFO_EMPTY ?
			OPNORM_OK :
			OPNORM_FIFO);
	  return NULL;
	}

      cube_print(&cube0, n, ">");

      /* nfifo is the total number dequeue */

      td->nfifo++;

      /* cube subdivide */

      int hwnexp = cube0.hwnexp + 1;
      double halfwidth = ldexp(1, -hwnexp);

      /*
	if halfwidth < DBL_EPSILON then we cannot
	calulate the centres of the subdivided cubes
	accurately, we break out and report that the
	requested accuracy could not be achieved
      */

      if (halfwidth < DBL_EPSILON)
	{
	  td->status = OPNORM_INACC;
	  return NULL;
	}

      for (size_t k = 0 ; k < (1UL << (n-1)) ; k++)
	{
	  cube1.side = cube0.side;
	  cube1.hwnexp = hwnexp;

	  /*
	    we give our cube1 a temporary set of centres
	    while we evaluate and decide whether to jetison
	    or enqueue it, only if the latter do we make a
	    malloc and copy the temporary centres.  this
	    saves a *lot* of malloc/free pairs
	  */

	  double centres[n];
	  cube1.centres = centres;

	  size_t k0 = k;

	  for (size_t j = 0 ; j < n ; j++)
	    {
	      if (cube0.side == j)
		{
		  cube1.centres[j] = cube0.centres[j];
		  continue;
		}

	      cube1.centres[j] = cube0.centres[j] +
		((k0 % 2) ? halfwidth : -halfwidth);

	      k0 /= 2;
	    }

	  cube_print(&cube1, n, "<");

	  /* get the corresponding patch */

	  cube_to_patch(&cube1, n, p, LCRP, SCD, &patch);
	  patch_print(patch, n);

	  double ratio = radius_to_ratio(patch.radius, p);

	  /*
	    check for patch viability - this check almost
	    always succeeds (on Drury K, this is false in
	    80/164016 cases, so 0.05% of the time) very
	    small beer. Yet it introduces a branch point,
	    so one might think it worth removing. Timing
	    tests indicate that there is no speedup in
	    doing so, so we keep it.
	  */

	  if (ratio > 0)
	    {
	      /* evaluate M at patch centre */

	      double v[m];

	      ts->matvec(M, pcent, m, n, v);
	      td->neval++;

	      double t = pnorm(v, m, q);

	      /* test first with the previous value of tmax */

	      if (t < tmax)
		{
		  /* test whether we can jettison this cube */

		  if (t < (tmax * ratio * (1 + eps))) continue;

		  /*
		    note that the global ts->tmax >= tmax so it would
		    be pointless (and cost a mutex access) to test
		    for that here
		  */
		}
	      else
		{
		  if (pthread_mutex_lock(&(ts->maxlock)) < 0)
		    {
		      td->status = OPNORM_THREAD;
		      return NULL;
		    }

		  /* update local tmax from global */

		  tmax = ts->tmax;

		  /*
		    if we have found a new global maximum then we
		    update it (and the global maximising vector)
		    as well as the local copy
		  */

		  if (t > tmax)
		    {
		      ts->tmax = tmax = t;

		      if (ts->vmax)
			memcpy(ts->vmax, pcent, n*sizeof(double));
		    }

		  if (pthread_mutex_unlock(&(ts->maxlock)) < 0)
		    {
		      td->status = OPNORM_THREAD;
		      return NULL;
		    }

		  /*
		    test whether we can jettison this cube but
		    now with the updated value of tmax
		  */

		  if (t < (tmax * ratio * (1 + eps))) continue;

		}
	    }

	  /*
	    we will enqueue this cube, so we need to
	    allocate and copy its temporary centres set
	  */

	  if (! (cube1.centres = malloc(n*sizeof(double))))
	    {
	      td->status = OPNORM_ALLOC;
	      return NULL;
	    }

	  memcpy(cube1.centres, centres, n*sizeof(double));

	  if (pthread_mutex_lock(&(ts->fifolock)) < 0)
	    {
	      free(cube1.centres);
	      td->status = OPNORM_THREAD;
	      return NULL;
	    }

	  fifoerr = fifo_enqueue(fifo, &cube1);

	  if (pthread_mutex_unlock(&(ts->fifolock)) < 0)
	    {
	      td->status = OPNORM_THREAD;
	      return NULL;
	    }

	  switch(fifoerr)
	    {
	    case FIFO_OK:
	      break;
	    case FIFO_USERMAX:
	      td->status = OPNORM_FIFOMAX;
	      return NULL;
	    default:
	      td->status = OPNORM_FIFO;
	      return NULL;
	    }
	}

      free(cube0.centres);
    }

  /* we should not arrive here */

  td->status = OPNORM_BUG;

  return NULL;
}