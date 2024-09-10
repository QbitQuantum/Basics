/*
 * Converts specified int array into GraphicsPath object
 */
static inline GraphicsPath *createGraphicsPath(JNIEnv *env, jfloatArray jpath, jint len, jint winding) 
{
    jfloat *path = (jfloat *)malloc(sizeof(jfloat)*len);
    env->GetFloatArrayRegion(jpath, 0, len, path);

    
    GraphicsPath *res = new GraphicsPath((winding == java_awt_geom_PathIterator_WIND_EVEN_ODD)?FillModeAlternate:FillModeWinding);
    float x1 = 0;
    float y1 = 0;
    float mx = 0;
    float my = 0;
    for (int i = 0; i < len; i++) {
        int seg = (int)path[i];
        switch (seg) {
            case java_awt_geom_PathIterator_SEG_MOVETO:
                res->StartFigure();
                x1 = path[i+1];
                y1 = path[i+2];
                mx = path[i+1];
                my = path[i+2];
                i += 2;
                break;
            case java_awt_geom_PathIterator_SEG_LINETO:
                res->AddLine(x1, y1, path[i+1], path[i+2]);
                x1 = path[i+1];
                y1 = path[i+2];
                i += 2;
                break;
            case java_awt_geom_PathIterator_SEG_CLOSE:
                res->AddLine(x1, y1, mx, my);
                x1 = mx;
                y1 = my;
                res->CloseFigure();
                break;
        }
    }
    
    free(path);
    
    return res;
}    