/**MAJ pour le 3D DJ.Abdemouche 2003**/
double *sciGetPoint(char * pthis, int *numrow, int *numcol)
{
    int iType = -1;
    int *piType = &iType;
    double *tab = NULL;
    int i = 0;

    getGraphicObjectProperty(pthis, __GO_TYPE__, jni_int, (void **)&piType);

    /*
     * Object type determined by string comparisons
     * Required as we have no better way to do this for the moment
     */

    switch (iType)
    {
        case __GO_FIGURE__ :
        {
            int* figurePosition = NULL;
            int* axesSize = NULL;

            *numrow = 2;
            *numcol = 2;
            if ((tab = CALLOC((*numrow) * (*numcol), sizeof(double))) == NULL)
            {
                *numrow = -1;
                *numcol = -1;
                return NULL;
            }

            getGraphicObjectProperty(pthis, __GO_POSITION__, jni_int_vector, (void **)&figurePosition);
            getGraphicObjectProperty(pthis, __GO_AXES_SIZE__, jni_int_vector, (void **)&axesSize);

            tab[0] = (double) figurePosition[0];
            tab[1] = (double) figurePosition[1];
            tab[2] = (double) axesSize[0];
            tab[3] = (double) axesSize[1];

            return tab;
        }
        case __GO_POLYLINE__ :
        {
            char* parentAxes = NULL;
            double* dataX = NULL;
            double* dataY = NULL;
            double* dataZ = NULL;
            int iTmp = 0;
            int* piTmp = &iTmp;
            int iView = 0;
            int *piView = &iView;

            /*
             * Testing whether data properties exist for this object
             * is currently done only for this property. The type comparison already
             * ensures that this is the case, though doing so is awkward.
             */
            getGraphicObjectProperty(pthis, __GO_DATA_MODEL_NUM_ELEMENTS__, jni_int, (void**)&piTmp);

            if (piTmp == NULL)
            {
                *numrow = -2;
                *numcol = -2;
                return NULL;
            }

            *numrow = iTmp;

            getGraphicObjectProperty(pthis, __GO_DATA_MODEL_Z_COORDINATES_SET__, jni_int, (void**)&piTmp);

            if (iTmp)
            {
                *numcol = 3;
            }
            else
            {
                *numcol = 2;
            }

            if ((*numrow) * (*numcol) == 0)
            {
                /* empty data, no warnings */
                *numrow = 0;
                *numcol = 0;
                return NULL;
            }

            getGraphicObjectProperty(pthis, __GO_PARENT_AXES__, jni_string, (void **)&parentAxes);
            getGraphicObjectProperty(parentAxes, __GO_VIEW__, jni_int, (void**)&piView);

            getGraphicObjectProperty(pthis, __GO_DATA_MODEL_X__, jni_double_vector, (void **)&dataX);
            getGraphicObjectProperty(pthis, __GO_DATA_MODEL_Y__, jni_double_vector, (void **)&dataY);

            if (*numcol == 2 && iView)
            {
                *numcol = (*numcol) + 1; /* colonne de 0. a prendre en compte / afficher => numcol+1*/
                if ((tab = CALLOC((*numrow) * (*numcol), sizeof(double))) == NULL)
                {
                    *numrow = -1;
                    *numcol = -1;
                    return NULL;
                }

                for (i = 0 ; i < *numrow ; i++)
                {
                    tab[i] = dataX[i];
                    tab[*numrow + i] = dataY[i];
                    tab[(2 * (*numrow)) + i] = 0.;
                }
            }
            else
            {
                if ((tab = CALLOC((*numrow) * (*numcol), sizeof(double))) == NULL)
                {
                    *numrow = -1;
                    *numcol = -1;
                    return NULL;
                }

                if (*numcol == 3)
                {
                    getGraphicObjectProperty(pthis, __GO_DATA_MODEL_Z__, jni_double_vector, (void **)&dataZ);
                }

                for (i = 0 ; i < *numrow ; i++)
                {
                    tab[i] = dataX[i];
                    tab[*numrow + i] = dataY[i];
                    if (*numcol == 3)
                    {
                        tab[(2 * (*numrow)) + i] = dataZ[i];
                    }
                }

            }
            return tab;
        }
        case __GO_RECTANGLE__ :
        {
            char* parentAxes = NULL;
            double* upperLeftPoint = NULL;
            double width = 0.0;
            double *pdblWidth = &width;
            double height = 0.0;
            double *pdblHeight = &height;
            int iView = 0;
            int *piView = &iView;

            *numrow = 1;

            getGraphicObjectProperty(pthis, __GO_PARENT_AXES__, jni_string, (void **)&parentAxes);
            getGraphicObjectProperty(parentAxes, __GO_VIEW__, jni_int, (void**)&piView);

            *numcol = iView ? 5 : 4;

            if ((tab = CALLOC((*numrow) * (*numcol), sizeof(double))) == NULL)
            {
                *numrow = -1;
                *numcol = -1;
                return NULL;
            }

            getGraphicObjectProperty(pthis, __GO_UPPER_LEFT_POINT__, jni_double_vector, (void **)&upperLeftPoint);

            getGraphicObjectProperty(pthis, __GO_WIDTH__, jni_double, (void**)&pdblWidth);
            getGraphicObjectProperty(pthis, __GO_HEIGHT__, jni_double, (void **)&pdblHeight);

            tab[0] = upperLeftPoint[0];
            tab[1] = upperLeftPoint[1];

            if (iView)
            {
                tab[2] = upperLeftPoint[2];
                tab[3] = width;
                tab[4] = height;
            }
            else
            {
                tab[2] = width;
                tab[3] = height;
            }
            return (double*)tab;
        }
        case __GO_ARC__ :
        {
            char* parentAxes = NULL;
            double* upperLeftPoint = NULL;
            double width = 0.0;
            double *pdblWidth = &width;

            double height = 0.;
            double *pdblHeight = &height;

            double startAngle = 0.;
            double *pdblStartAngle = &startAngle;
            double endAngle = 0.;
            double *pdblEndAngle = &endAngle;
            int view = 0;
            int *piView = &view;

            *numrow = 1;

            getGraphicObjectProperty(pthis, __GO_PARENT_AXES__, jni_string, (void **)&parentAxes);
            getGraphicObjectProperty(parentAxes, __GO_VIEW__, jni_int, (void**)&piView);

            *numcol = view ? 7 : 6;

            if ((tab = CALLOC((*numrow) * (*numcol), sizeof(double))) == NULL)
            {
                *numrow = -1;
                *numcol = -1;
                return NULL;
            }

            getGraphicObjectProperty(pthis, __GO_UPPER_LEFT_POINT__, jni_double_vector, (void **)&upperLeftPoint);

            getGraphicObjectProperty(pthis, __GO_WIDTH__, jni_double, (void **)&pdblWidth);
            getGraphicObjectProperty(pthis, __GO_HEIGHT__, jni_double, (void **)&pdblHeight);

            getGraphicObjectProperty(pthis, __GO_START_ANGLE__, jni_double, (void **)&pdblStartAngle);
            getGraphicObjectProperty(pthis, __GO_END_ANGLE__, jni_double, (void **)&pdblEndAngle);

            tab[0] = upperLeftPoint[0];
            tab[1] = upperLeftPoint[1];

            if (view)
            {
                tab[2] = upperLeftPoint[2];
                tab[3] = width;
                tab[4] = height;
                tab[5] = RAD2DEG(startAngle);
                tab[6] = RAD2DEG(endAngle);
            }
            else
            {
                tab[2] = width;
                tab[3] = height;
                tab[4] = RAD2DEG(startAngle);
                tab[5] = RAD2DEG(endAngle);
            }

            return (double*)tab;
        }
        case __GO_COMPOUND__ :
        {
            return (double*)NULL;
        }
        case __GO_TEXT__ :
        {
            char* parentAxes = NULL;
            double* textPosition = NULL;
            int iView = 0;
            int* piView = &iView;

            *numrow = 1;

            getGraphicObjectProperty(pthis, __GO_PARENT_AXES__, jni_string, (void **)&parentAxes);
            getGraphicObjectProperty(parentAxes, __GO_VIEW__, jni_int, (void**)&piView);

            *numcol = iView ? 3 : 2;

            if ((tab = CALLOC((*numrow) * (*numcol), sizeof(double))) == NULL)
            {
                *numrow = -1;
                *numcol = -1;
                return NULL;
            }

            getGraphicObjectProperty(pthis, __GO_POSITION__, jni_double_vector, (void **)&textPosition);

            tab[0] = textPosition[0];
            tab[1] = textPosition[1];

            if (iView)
            {
                tab[2] = textPosition[2];
            }

            return (double*)tab;
        }
        case __GO_SEGS__ :
        {
            int iView = 0;
            int* piView = &iView;
            int iNumArrows = 0;
            int* piNumArrows = &iNumArrows;
            char* parentAxes = NULL;
            double* arrowBases = NULL;
            double* arrowDirections = NULL;

            getGraphicObjectProperty(pthis, __GO_NUMBER_ARROWS__, jni_int, (void**)&piNumArrows);
            *numrow = iNumArrows;

            /* only two coordinates are displayed if the axe is in 2d
            and the z coordinates has never been modified */

            getGraphicObjectProperty(pthis, __GO_PARENT_AXES__, jni_string, (void **)&parentAxes);

            getGraphicObjectProperty(parentAxes, __GO_VIEW__, jni_int, (void**)&piView);

            if (iView == 0) // 2-D
            {
                *numcol = 2;
            }
            else // 3-D
            {
                *numcol = 3;
            }

            if ((tab = CALLOC(2 * (*numrow) * (*numcol), sizeof(double))) == NULL)
            {
                *numrow = -1;
                *numcol = -1;
                return NULL;
            }

            getGraphicObjectProperty(pthis, __GO_BASE__, jni_double_vector, (void **)&arrowBases);
            getGraphicObjectProperty(pthis, __GO_DIRECTION__, jni_double_vector, (void **)&arrowDirections);

            for (i = 0; i < *numrow; i++)
            {
                tab[2 * i] = arrowBases[3 * i];
                tab[2 * i + 1] = arrowDirections[3 * i];
                tab[2 * (*numrow) + 2 * i] = arrowBases[3 * i + 1];
                tab[2 * (*numrow) + 2 * i + 1] = arrowDirections[3 * i + 1];
                if (*numcol == 3)
                {
                    tab[4 * (*numrow) + 2 * i] = arrowBases[3 * i + 2];
                    tab[4 * (*numrow) + 2 * i + 1] = arrowDirections[3 * i + 2];
                }
            }

            /* There are twice as many points as arrows (2 endpoints) */
            *numrow = 2 * (*numrow);

            return (double*)tab;
        }
        case __GO_FAC3D__ :
        case __GO_PLOT3D__ :
        {
            *numrow = -1;
            *numcol = -1;
            return (double*) NULL;
        }
        case __GO_MATPLOT__ :
        {
            int nx = 0;
            int *piNx = &nx;
            int ny = 0;
            int *piNy = &ny;
            double* data;

            getGraphicObjectProperty(pthis, __GO_DATA_MODEL_NUM_X__, jni_int, (void**)&piNx);

            getGraphicObjectProperty(pthis, __GO_DATA_MODEL_NUM_Y__, jni_int, (void**)&piNy);

            /* The z data matrix has (ny-1) rows and (nx-1) cols */
            nx = nx - 1;
            ny = ny - 1;

            *numrow = ny;
            *numcol = nx;

            if ((tab = CALLOC(nx * ny, sizeof(double))) == NULL)
            {
                *numrow = -1;
                *numcol = -1;
                return (double*)NULL;
            }

            getGraphicObjectProperty(pthis, __GO_DATA_MODEL_Z__, jni_double_vector, (void **)&data);

            for (i = 0; i < nx * ny; i++)
            {
                tab[i] = data[i];
            }

            return (double*)tab;
        }
        case __GO_FEC__ :
        {
            double* coordinates = NULL;
            double* values = NULL;
            int iTmp = 0;
            int* piTmp = &iTmp;

            *numcol = 3;

            getGraphicObjectProperty(pthis, __GO_DATA_MODEL_NUM_VERTICES__, jni_int, (void**)&piTmp);
            *numrow = iTmp;

            if ((tab = CALLOC(*numrow * 3, sizeof(double))) == NULL)
            {
                *numrow = -1;
                *numcol = -1;
                return (double*)NULL;
            }

            getGraphicObjectProperty(pthis, __GO_DATA_MODEL_COORDINATES__, jni_double_vector, (void **)&coordinates);
            getGraphicObjectProperty(pthis, __GO_DATA_MODEL_VALUES__, jni_double_vector, (void **)&values);

            for (i = 0; i < *numrow; i++)
            {
                tab[i] = coordinates[3 * i];
                tab[*numrow + i] = coordinates[3 * i + 1];
                tab[*numrow * 2 + i] = values[i];

            }

            return (double*)tab;
        }
        case __GO_LEGEND__ :
        case __GO_AXES__ :
        case __GO_LABEL__ :
        default :
        {
            *numrow = -2;
            *numcol = -2;
            return (double*)NULL;
        }
    }
#if 0
case SCI_UIMENU:
#endif
    return (double*)NULL;
}