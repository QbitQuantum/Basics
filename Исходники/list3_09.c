int effect(ImageData *img,ImageData *outimg)
{
    int val;
    int x,y;
    int xx,yy;
    int hh;
    int endn;
    int vv, vr, vg, vb;
    int ave, rr, gg,bb;
    Pixel col,ncol;
    Pixel ans;
    int *sobel;
    int sadr;
    int rate,nn,i;
    int x1,y1,x2,y2;

    x1=0;
    y1=0;
    x2=img->width-1;
    y2=img->height-1;

    setRegInfo();
    nn=2;
    for(y=y1;y<=y2;y++){
        for(x=x1;x<=x2;x++){
            rr=gg=bb=0;
            sadr=0;
            for(yy=(-nn);yy<=nn;yy++){
                for(xx=(-nn);xx<=nn;xx++){
                    val = getPixel(img,x+xx,y+yy,&ncol);
                    imgR[sadr]=ncol.r;
                    imgG[sadr]=ncol.g;
                    imgB[sadr]=ncol.b;
                    sadr++;
                }
            }
            vr=vg=vb=1000;
            for(i=0;i<=8;i++){
                vv=getRegVal(imgR,i,&ave);
                if(vr>vv){
                    vr=vv;
                    rr=ave;
                }
                vv=getRegVal(imgG,i,&ave);
                if(vg>vv){
                    vg=vv;
                    gg=ave;
                }
                vv=getRegVal(imgB,i,&ave);
                if(vb>vv){
                    vb=vv;
                    bb=ave;
                }
            }
            vv=getRegVal(imgB,i,&ave);
            if(vb>vv){
                vb=vv;
                bb=ave;
            }
        }
        ans.r = rr;
        ans.g = gg;
        ans.b = bb;
        setPixel(outimg,x,y,&ans);
    }
}