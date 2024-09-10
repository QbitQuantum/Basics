static inline void p8idct(DCTELEM data[64], FLOAT temp[64], uint8_t *dest, int stride, int x, int y, int type){
    int i;
    FLOAT av_unused tmp0;
    FLOAT s04, d04, s17, d17, s26, d26, s53, d53;
    FLOAT os07, os16, os25, os34;
    FLOAT od07, od16, od25, od34;

    for(i=0; i<y*8; i+=y){
        s17= temp[1*x + i] + temp[7*x + i];
        d17= temp[1*x + i] - temp[7*x + i];
        s53= temp[5*x + i] + temp[3*x + i];
        d53= temp[5*x + i] - temp[3*x + i];

        od07=  s17 + s53;
        od25= (s17 - s53)*(2*A4);

#if 0 //these 2 are equivalent
        tmp0= (d17 + d53)*(2*A2);
        od34=  d17*( 2*B6) - tmp0;
        od16=  d53*(-2*B2) + tmp0;
#else
        od34=  d17*(2*(B6-A2)) - d53*(2*A2);
        od16=  d53*(2*(A2-B2)) + d17*(2*A2);
#endif

        od16 -= od07;
        od25 -= od16;
        od34 += od25;

        s26 = temp[2*x + i] + temp[6*x + i];
        d26 = temp[2*x + i] - temp[6*x + i];
        d26*= 2*A4;
        d26-= s26;

        s04= temp[0*x + i] + temp[4*x + i];
        d04= temp[0*x + i] - temp[4*x + i];

        os07= s04 + s26;
        os34= s04 - s26;
        os16= d04 + d26;
        os25= d04 - d26;

        if(type==0){
            temp[0*x + i]= os07 + od07;
            temp[7*x + i]= os07 - od07;
            temp[1*x + i]= os16 + od16;
            temp[6*x + i]= os16 - od16;
            temp[2*x + i]= os25 + od25;
            temp[5*x + i]= os25 - od25;
            temp[3*x + i]= os34 - od34;
            temp[4*x + i]= os34 + od34;
        }else if(type==1){
            data[0*x + i]= lrintf(os07 + od07);
            data[7*x + i]= lrintf(os07 - od07);
            data[1*x + i]= lrintf(os16 + od16);
            data[6*x + i]= lrintf(os16 - od16);
            data[2*x + i]= lrintf(os25 + od25);
            data[5*x + i]= lrintf(os25 - od25);
            data[3*x + i]= lrintf(os34 - od34);
            data[4*x + i]= lrintf(os34 + od34);
        }else if(type==2){
            dest[0*stride + i]= av_clip_uint8(((int)dest[0*stride + i]) + lrintf(os07 + od07));
            dest[7*stride + i]= av_clip_uint8(((int)dest[7*stride + i]) + lrintf(os07 - od07));
            dest[1*stride + i]= av_clip_uint8(((int)dest[1*stride + i]) + lrintf(os16 + od16));
            dest[6*stride + i]= av_clip_uint8(((int)dest[6*stride + i]) + lrintf(os16 - od16));
            dest[2*stride + i]= av_clip_uint8(((int)dest[2*stride + i]) + lrintf(os25 + od25));
            dest[5*stride + i]= av_clip_uint8(((int)dest[5*stride + i]) + lrintf(os25 - od25));
            dest[3*stride + i]= av_clip_uint8(((int)dest[3*stride + i]) + lrintf(os34 - od34));
            dest[4*stride + i]= av_clip_uint8(((int)dest[4*stride + i]) + lrintf(os34 + od34));
        }else{
            dest[0*stride + i]= av_clip_uint8(lrintf(os07 + od07));
            dest[7*stride + i]= av_clip_uint8(lrintf(os07 - od07));
            dest[1*stride + i]= av_clip_uint8(lrintf(os16 + od16));
            dest[6*stride + i]= av_clip_uint8(lrintf(os16 - od16));
            dest[2*stride + i]= av_clip_uint8(lrintf(os25 + od25));
            dest[5*stride + i]= av_clip_uint8(lrintf(os25 - od25));
            dest[3*stride + i]= av_clip_uint8(lrintf(os34 - od34));
            dest[4*stride + i]= av_clip_uint8(lrintf(os34 + od34));
        }
    }
}