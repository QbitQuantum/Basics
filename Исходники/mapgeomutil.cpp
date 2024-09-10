shapeObj *msRasterizeArc(double x0, double y0, double radius, double startAngle, double endAngle, int isSlice) {
    static int allocated_size=100;
    shapeObj *shape = (shapeObj*)calloc(1,sizeof(shapeObj));
    MS_CHECK_ALLOC(shape, sizeof(shapeObj), NULL);
    mapserver::arc arc ( x0, y0,radius,radius, startAngle*MS_DEG_TO_RAD, endAngle*MS_DEG_TO_RAD,true );
    arc.approximation_scale ( 1 );
    arc.rewind(1);
    msInitShape(shape);

    lineObj *line = (lineObj*)calloc(1,sizeof(lineObj));
    if (!line) {
        msSetError(MS_MEMERR, "%s: %d: Out of memory allocating %u bytes.\n", "msRasterizeArc()" ,
                   __FILE__, __LINE__, sizeof(lineObj));
        free(shape);
        return NULL;
    }
    shape->line = line;
    shape->numlines = 1;
    line->point = (pointObj*)calloc(allocated_size,sizeof(pointObj));
    if (!line->point) {
        msSetError(MS_MEMERR, "%s: %d: Out of memory allocating %u bytes.\n", "msRasterizeArc()" ,
                   __FILE__, __LINE__, allocated_size*sizeof(pointObj));
        free(line);
        free(shape);
        return NULL;
    }

    line->numpoints = 0;

    double x,y;

    //first segment from center to first point of arc
    if(isSlice) {
        line->point[0].x = x0;
        line->point[0].y = y0;
        line->numpoints = 1;
    }
    while(arc.vertex(&x,&y) != mapserver::path_cmd_stop) {
        if(line->numpoints == allocated_size) {
            allocated_size *= 2;
            line->point = (pointObj*)realloc(line->point, allocated_size * sizeof(pointObj));
            if (!line->point) {
                msSetError(MS_MEMERR, "%s: %d: Out of memory allocating %u bytes.\n", "msRasterizeArc()" ,
                           __FILE__, __LINE__, allocated_size * sizeof(pointObj));
                free(line);
                free(shape);
                return NULL;
            }
        }
        line->point[line->numpoints].x = x;
        line->point[line->numpoints].y = y;
        line->numpoints++;
    }

    //make sure the shape is closed if we're doing a full circle
    if(!isSlice && !(endAngle-startAngle)%360) {
        if(line->point[line->numpoints-1].x != line->point[0].x ||
                line->point[line->numpoints-1].y != line->point[0].y) {
            if(line->numpoints == allocated_size) {
                allocated_size *= 2;
                line->point = (pointObj*)realloc(line->point, allocated_size * sizeof(pointObj));
                if (!line->point) {
                    msSetError(MS_MEMERR, "%s: %d: Out of memory allocating %u bytes.\n", "msRasterizeArc()" ,
                               __FILE__, __LINE__, allocated_size * sizeof(pointObj));
                    free(line);
                    free(shape);
                    return NULL;
                }
            }
            line->point[line->numpoints].x = line->point[0].x;
            line->point[line->numpoints].y = line->point[0].y;
            line->numpoints++;
        }

    }
    if(isSlice) {
        if(line->numpoints == allocated_size) {
            allocated_size *= 2;
            line->point = (pointObj*)realloc(line->point, allocated_size * sizeof(pointObj));
            if (!line->point) {
                msSetError(MS_MEMERR, "%s: %d: Out of memory allocating %u bytes.\n", "msRasterizeArc()" ,
                           __FILE__, __LINE__, allocated_size * sizeof(pointObj));
                free(line);
                free(shape);
                return NULL;
            }
        }
        line->point[line->numpoints].x = x0;
        line->point[line->numpoints].y = y0;
        line->numpoints++;
    }
    return shape;
}