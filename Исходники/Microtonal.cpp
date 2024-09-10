/*
 * Convert a line to tunings; returns -1 if it ok
 */
int Microtonal::linetotunings(unsigned int nline, const char *line)
{
    int      x1 = -1, x2 = -1, type = -1;
    REALTYPE x  = -1.0, tmp, tuning = 1.0;
    if(strstr(line, "/") == NULL) {
        if(strstr(line, ".") == NULL) { // M case (M=M/1)
            sscanf(line, "%d", &x1);
            x2   = 1;
            type = 2; //division
        }
        else {  // float number case
            sscanf(line, "%f", &x);
            if(x < 0.000001)
                return 1;
            type = 1; //float type(cents)
        }
    }
    else {  // M/N case
        sscanf(line, "%d/%d", &x1, &x2);
        if((x1 < 0) || (x2 < 0))
            return 1;
        if(x2 == 0)
            x2 = 1;
        type = 2; //division
    }

    if(x1 <= 0)
        x1 = 1;     //not allow zero frequency sounds (consider 0 as 1)

    //convert to float if the number are too big
    if((type == 2)
       && ((x1 > (128 * 128 * 128 - 1)) || (x2 > (128 * 128 * 128 - 1)))) {
        type = 1;
        x    = ((REALTYPE) x1) / x2;
    }
    switch(type) {
    case 1:
        x1     = (int) floor(x);
        tmp    = FMOD(x, 1.0);
        x2     = (int) (floor(tmp * 1e6));
        tuning = pow(2.0, x / 1200.0);
        break;
    case 2:
        x      = ((REALTYPE)x1) / x2;
        tuning = x;
        break;
    }

    tmpoctave[nline].tuning = tuning;
    tmpoctave[nline].type   = type;
    tmpoctave[nline].x1     = x1;
    tmpoctave[nline].x2     = x2;

    return -1; //ok
}