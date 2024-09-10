static void bitblit(GrxFrame *dst,int dx,int dy,
                    GrxFrame *src,int sx,int sy,
                    int w,int h,GrxColor op)
{
    int pl;
    GRX_ENTER();
    if(grx_color_get_mode(op) == GRX_COLOR_MODE_IMAGE)
        bitblt(dst,dx,dy,src,sx,sy,w,h,op);
    else
        for (pl=0; pl < 3; ++pl)
            _GrFrDrvPackedBitBltR2Rpl(dst,dx,dy,src,sx,sy,w,h,op,pl);
    GRX_LEAVE();
}