static int
constraintSatIso(pullTask *task, pullPoint *point,
                 double stepMax, unsigned int iterMax,
                 /* output */
                 int *constrFailP) {
  static const char me[]="constraintSatIso";
  double
    step,         /* current step size */
    val, aval,    /* last and current function values */
    hack,         /* how to control re-tries in the context of a single
                     for-loop, instead of a nested do-while loop */
    grad[4], dir[3], len, state[1 + 1 + 3 + 3];
  unsigned int iter = 0;  /* 0: initial probe, 1..iterMax: probes in loop */

  PROBE(val, aval, grad);
  SAVE(state, aval, val, grad, point->pos);
  hack = 1;
  for (iter=1; iter<=iterMax; iter++) {
    /* consider? http://en.wikipedia.org/wiki/Halley%27s_method */
    NORMALIZE(dir, grad, len);
    if (!len) {
      /* no gradient; back off */
      hack *= task->pctx->sysParm.backStepScale;
      RESTORE(aval, val, grad, point->pos, state);
      continue;
    }
    step = -val/len; /* the newton-raphson step */
    step = step > 0 ? AIR_MIN(stepMax, step) : AIR_MAX(-stepMax, step);
    ELL_3V_SCALE_INCR(point->pos, hack*step, dir);
    _pullPointHistAdd(point, pullCondConstraintSatA);
    PROBE(val, aval, grad);
    if (aval <= state[0]) {  /* we're no further from the root */
      if (AIR_ABS(step) < stepMax*task->pctx->sysParm.constraintStepMin) {
        /* we have converged! */
        break;
      }
      SAVE(state, aval, val, grad, point->pos);
      hack = 1;
    } else { /* oops, try again, don't update dir or len, reset val */
      hack *= task->pctx->sysParm.backStepScale;
      RESTORE(aval, val, grad, point->pos, state);
    }
  }
  if (iter > iterMax) {
    *constrFailP = pullConstraintFailIterMaxed;
  } else {
    *constrFailP = AIR_FALSE;
  }
  return 0;
}