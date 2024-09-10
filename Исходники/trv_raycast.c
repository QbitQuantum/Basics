void trv_raycast(int16_t pitch, int16_t yaw, int16_t screenyaw,
                FAR struct trv_raycast_s *result)
{
  /* Set the camera pitch and yaw angles for this cast */

  g_camera.pitch = pitch;
  g_camera.yaw = yaw;

  /* Initialize the result structure, assuming that there will be no hit */

  result->rect  = NULL;
  result->type  = NO_HIT;
  result->xpos  = 0;
  result->ypos  = 0;
  result->xdist = TRV_INFINITY;
  result->ydist = TRV_INFINITY;
  result->zdist = TRV_INFINITY;

  /* Prepare for X and Y ray casts.  These casts will need the adjusted tangent
   * of the pitch angle in order to correct for "fish eye" distortion.  This
   * correction consists of multiplying by the cosine of the relative screen
   * yaw position. The tangent is double precision, the cosine is double
   * precision, the result will be retained as double precision.
   */

  screenyaw = ABS(screenyaw);
#if ENABLE_VIEW_CORRECTION
  g_adj_tanpitch = qTOd(TAN(pitch) * ((int32_t) g_cos_table[screenyaw]));
#else
  g_adj_tanpitch = TAN(pitch);
#endif

  /* Perform X & Y raycasting based on the quadrant of the yaw angle */

  if (g_camera.yaw < ANGLE_90)
    {
      trv_ray_xcaster14(result);
      trv_ray_ycaster12(result);
    }
  else if (g_camera.yaw < ANGLE_180)
    {
      trv_ray_xcaster23(result);
      trv_ray_ycaster12(result);
    }
  else if (g_camera.yaw < ANGLE_270)
    {
      trv_ray_xcaster23(result);
      trv_ray_ycaster34(result);
    }
  else
    {
      trv_ray_xcaster14(result);
      trv_ray_ycaster34(result);
    }

  /* Perform Z ray casting based upon if we are looking up or down */

  if (g_camera.pitch < ANGLE_90)
    {
      /* Get the adjusted cotangent of the pitch angle which is used to correct
       * for the "fish eye" distortion.  This correction consists of
       * multiplying by the inverted cosine of the relative screen yaw
       * position.  The cotangent is double precision, the secant is double
       * precision, the result will be retained as double precision.
       */

#if ENABLE_VIEW_CORRECTION
      g_adj_cotpitch = qTOd(g_cot_table(pitch) * g_sec_table[screenyaw]);
#else
      g_adj_cotpitch = g_cot_table(pitch);
#endif
      trv_ray_zcasteru(result);
    }
  else
    {
      /* Get the adjusted cotangent of the pitch angle which is used to correct
       * for the "fish eye" distortion.  This correction consists of
       * multiplying by the inverted cosine of the relative screen yaw
       * position. The cotangent is double precision, the secant is double
       * precision, the result will be retained as double precision.
       */

#if ENABLE_VIEW_CORRECTION
      g_adj_cotpitch =
        qTOd(g_cot_table(ANGLE_360 - pitch) * g_sec_table[screenyaw]);
#else
      g_adj_cotpitch = g_cot_table(ANGLE_360 - pitch);
#endif
      trv_ray_zcasterl(result);
    }
}