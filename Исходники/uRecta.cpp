void TRecta::graphic(TImage *i, double cx, double cy, double z)
{
    double maxx, minx, maxy, miny;
    double gx, gy, x, y;
    TCanvas *c = i->Canvas;
    int W, H;
    W = i->Picture->Bitmap->Width;
    H = i->Picture->Bitmap->Height;
    maxx = (double)(W-cx)/z;
    minx = (double)(-cx)/z;
    maxy = (double)(cy)/z;
    miny = (double)(cy-H)/z;
    i->Canvas->Pen->Assign(style);
    //Obtener x para la izq de la pantalla
    x = -1.0*(double)cx/(double)z;
    y = k*(x-x0)+y0;
    if(miny <= y && y <= maxy) // A
    {
        c->MoveTo(cx + x*z, cy - y*z);
        //Obtener x para la der de la pantalla
        x = (double)(W-cx)/(double)z;
        y = k*(x-x0)+y0;
        if(miny <= y && y <= maxy) // B
        {
            c->LineTo(cx + x*z, cy - y*z);
        }
        else
        {
            y = 1.0*cy/z;
            x = (y-y0)/k+x0;
            if(minx <= x && x <= maxx) // C
            {
                c->LineTo(cx + x*z, cy - y*z);
            }
            else //B
            {
                x = (double)(W-cx)/(double)z;
                y = k*(x-x0)+y0;
                c->LineTo(cx + x*z, cy - y*z);
            }
        }
    }
    else // B o C o D
    {
        y = 1.0*cy/z;
        x = (y-y0)/k+x0;
        if(minx <= x && x <= maxx) // C
        {
            c->MoveTo(cx + x*z, cy - y*z);
            y = 1.0*(cy-H)/z;
            x = (y-y0)/k+x0;
            if(minx <= x && x <= maxx) // D
            {
                c->LineTo(cx + x*z, cy - y*z);
            }
            else //B
            {
                x = (double)(W-cx)/(double)z;
                y = k*(x-x0)+y0;
                c->LineTo(cx + x*z, cy - y*z);
            }
        }
        else
        {   // B o D
            y = 1.0*(cy-H)/z;
            x = (y-y0)/k+x0;
            if(minx <= x && x <= maxx) // D
            {
                c->MoveTo(cx + x*z, cy - y*z);
                x = (double)(W-cx)/(double)z;
                y = k*(x-x0)+y0;
                c->LineTo(cx + x*z, cy - y*z);
            }
            else //B
            {   //ERROR
                /*
                x = (double)(W-cx)/(double)z;
                   y = k*(x-x0)+y0;
                   c->LineTo(cx + x*z, cy - y*z);
                   */
            }
        }
    }

    if(vdirector)
    {
        c->MoveTo(cx, cy);
        double m = sqrt(a1*a1 + a2*a2);
        c->LineTo(cx + a1/m*z, cy - a2/m*z);
    }
    if(vnormal)
    {
        c->MoveTo(cx, cy);
        double m = sqrt(A*A + B*B);
        c->LineTo(cx + A/m*z, cy - B/m*z);
    }
}