static int
msProjectShapeLine(projectionObj *in, projectionObj *out,
                   shapeObj *shape, int line_index)

{
  int i;
  pointObj  lastPoint, thisPoint, wrkPoint, firstPoint;
  lineObj *line = shape->line + line_index;
  lineObj *line_out = line;
  int valid_flag = 0; /* 1=true, -1=false, 0=unknown */
  int numpoints_in = line->numpoints;
  int line_alloc = numpoints_in;
  int wrap_test;

#ifdef USE_PROJ_FASTPATHS
#define MAXEXTENT 20037508.34
#define M_PIby360 .0087266462599716479
#define MAXEXTENTby180 111319.4907777777777777777
  if(in->wellknownprojection == wkp_lonlat && out->wellknownprojection == wkp_gmerc) {
    for( i = line->numpoints-1; i >= 0; i-- ) {
#define p_x line->point[i].x
#define p_y line->point[i].y
      p_x *= MAXEXTENTby180;
      p_y = log(tan((90 + p_y) * M_PIby360)) * MS_RAD_TO_DEG;
      p_y *= MAXEXTENTby180;
      if (p_x > MAXEXTENT) p_x = MAXEXTENT;
      if (p_x < -MAXEXTENT) p_x = -MAXEXTENT;
      if (p_y > MAXEXTENT) p_y = MAXEXTENT;
      if (p_y < -MAXEXTENT) p_y = -MAXEXTENT;
#undef p_x
#undef p_y
    }
    return MS_SUCCESS;
  }
#endif



  wrap_test = out != NULL && out->proj != NULL && pj_is_latlong(out->proj)
              && !pj_is_latlong(in->proj);

  line->numpoints = 0;

  if( numpoints_in > 0 )
    firstPoint = line->point[0];

  memset( &lastPoint, 0, sizeof(lastPoint) );

  /* -------------------------------------------------------------------- */
  /*      Loop over all input points in linestring.                       */
  /* -------------------------------------------------------------------- */
  for( i=0; i < numpoints_in; i++ ) {
    int ms_err;
    wrkPoint = thisPoint = line->point[i];

    ms_err = msProjectPoint(in, out, &wrkPoint );

    /* -------------------------------------------------------------------- */
    /*      Apply wrap logic.                                               */
    /* -------------------------------------------------------------------- */
    if( wrap_test && i > 0 && ms_err != MS_FAILURE ) {
      double dist;
      pointObj pt1Geo;

      if( line_out->numpoints > 0 )
        pt1Geo = line_out->point[0];
      else
        pt1Geo = wrkPoint; /* this is a cop out */

      dist = wrkPoint.x - pt1Geo.x;
      if( fabs(dist) > 180.0
          && msTestNeedWrap( thisPoint, firstPoint,
                             pt1Geo, in, out ) ) {
        if( dist > 0.0 )
          wrkPoint.x -= 360.0;
        else if( dist < 0.0 )
          wrkPoint.x += 360.0;
      }
    }

    /* -------------------------------------------------------------------- */
    /*      Put result into output line with appropriate logic for          */
    /*      failure breaking lines, etc.                                    */
    /* -------------------------------------------------------------------- */
    if( ms_err == MS_FAILURE ) {
      /* We have started out invalid */
      if( i == 0 ) {
        valid_flag = -1;
      }

      /* valid data has ended, we need to work out the horizon */
      else if( valid_flag == 1 ) {
        pointObj startPoint, endPoint;

        startPoint = lastPoint;
        endPoint = thisPoint;
        if( msProjectSegment( in, out, &startPoint, &endPoint )
            == MS_SUCCESS ) {
          line_out->point[line_out->numpoints++] = endPoint;
        }
        valid_flag = -1;
      }

      /* Still invalid ... */
      else if( valid_flag == -1 ) {
        /* do nothing */
      }
    }

    else {
      /* starting out valid. */
      if( i == 0 ) {
        line_out->point[line_out->numpoints++] = wrkPoint;
        valid_flag = 1;
      }

      /* Still valid, nothing special */
      else if( valid_flag == 1 ) {
        line_out->point[line_out->numpoints++] = wrkPoint;
      }

      /* we have come over the horizon, figure out where, start newline*/
      else {
        pointObj startPoint, endPoint;

        startPoint = lastPoint;
        endPoint = thisPoint;
        if( msProjectSegment( in, out, &endPoint, &startPoint )
            == MS_SUCCESS ) {
          lineObj newLine;

          /* force pre-allocation of lots of points room */
          if( line_out->numpoints > 0
              && shape->type == MS_SHAPE_LINE ) {
            newLine.numpoints = numpoints_in - i + 1;
            newLine.point = line->point;
            msAddLine( shape, &newLine );

            /* new line is now lineout, but start without any points */
            line_out = shape->line + shape->numlines-1;

            line_out->numpoints = 0;

            /* the shape->line array is realloc, refetch "line" */
            line = shape->line + line_index;
          } else if( line_out == line
                     && line->numpoints >= i-2 ) {
            newLine.numpoints = numpoints_in;
            newLine.point = line->point;
            msAddLine( shape, &newLine );

            line = shape->line + line_index;

            line_out = shape->line + shape->numlines-1;
            line_out->numpoints = line->numpoints;
            line->numpoints = 0;

            /*
             * Now realloc this array large enough to hold all
             * the points we could possibly need to add.
             */
            line_alloc = line_alloc * 2;

            line_out->point = (pointObj *)
                              realloc(line_out->point,
                                      sizeof(pointObj) * line_alloc);
          }

          line_out->point[line_out->numpoints++] = startPoint;
        }
        line_out->point[line_out->numpoints++] = wrkPoint;
        valid_flag = 1;
      }
    }

    lastPoint = thisPoint;
  }

  /* -------------------------------------------------------------------- */
  /*      Make sure that polygons are closed, even if the trip over       */
  /*      the horizon left them unclosed.                                 */
  /* -------------------------------------------------------------------- */
  if( shape->type == MS_SHAPE_POLYGON
      && line_out->numpoints > 2
      && (line_out->point[0].x != line_out->point[line_out->numpoints-1].x
          || line_out->point[0].y != line_out->point[line_out->numpoints-1].y) ) {
    /* make a copy because msAddPointToLine can realloc the array */
    pointObj sFirstPoint = line_out->point[0];
    msAddPointToLine( line_out, &sFirstPoint );
  }

  return(MS_SUCCESS);
}