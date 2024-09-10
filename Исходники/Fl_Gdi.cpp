void Fl_Gdi::place(double x, double y, double w, double h, double tx, double ty, double tw, double th, double dpi, int align)
{
    double s = 72/dpi;
    double dy = (th - s * h)*iy/144;
    double dx = (tw - s * w)*ix/144;

    if(align & 3)
        if(align & FL_ALIGN_TOP)
            dy=0;
        else
            dy *=2;
    if(align & 12)
        if(align & FL_ALIGN_LEFT)
            dx=0;
        else
            dx *=2;

    SetViewportOrgEx(gc_, VOx = (int)(ix * (lm_+tx) /72 - ox + dx), VOy = (int)( iy *(tm_+ty) /72 - oy + dy),0);
    SetWindowOrgEx(gc_, WOx = (int)x,  WOy = (int)y,0);
    SetViewportExtEx(gc_,  VEx = (int)(ix*s),  VEy = (int)(iy*s), 0);
    SetWindowExtEx(gc_, WEx = 72,  WEy = 72,0);
};