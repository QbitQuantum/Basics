void RgbEffects::draw_chase(int x,int y,wxImage::HSVValue hsv,int ColorScheme,int Number_Chases,
                            int width,bool R_TO_L1,int Chase_Width,bool Chase_Fade3d1,
                            int ChaseDirection)
{
    float  orig_v,new_v;
    int new_x,i,max_chase_width,pixels_per_chase;
    wxColour color;
    size_t colorcnt=GetColorCount();
    int ColorIdx;

    orig_v=hsv.value;
    SetPixel(x,y,hsv); // Turn pixel on

    max_chase_width = width * Chase_Width/100.0;
    pixels_per_chase = width/Number_Chases;

    int pulsar=0;
    int n;
    float val;
    int mid = 0.5 + (max_chase_width/2.0);
    int pixels_per_color=max_chase_width/colorcnt;
    if(pixels_per_color<1) pixels_per_color=1;
    /*


    RRRRGGGG........+........................
    .RRRRGGGG.......+........................
    ..RRRRGGGG......+........................
    ...RRRRGGGG.....+........................
    ....RRRRGGGG....+........................
    .....RRRRGGGG...+........................
    ......RRRRGGGG..+........................
    .......RRRRGGGG.+........................
    ........RRRRGGGG+..............<===========   this is what fist version would end at
    .........RRRRGGG+........................
     .........RRRRGG+........................
      .........RRRRG+........................
       .........RRRR+........................
        .........RRR+........................



    */
    if(max_chase_width>=1)
    {
        for (i=0; i<=max_chase_width; i++)
        {
            if(pulsar==1)
            {
                n=state%10;
                switch (n)
                {
                case 0:
                case 4:
                    pulse(x,y,hsv,0.30);
                    break;
                case 1:
                case 3:
                    pulse(x,y,hsv,0.50);
                    pulse(x-1,y,hsv,0.30);
                    pulse(x+1,y,hsv,0.30);

                    break;
                case 2:
                    pulse(x,y,hsv,1.0);
                    pulse(x-1,y,hsv,0.50);
                    pulse(x+1,y,hsv,0.50);
                    pulse(x-2,y,hsv,0.30);
                    pulse(x+2,y,hsv,0.30);
                    break;
                }
            }
            else // not pulsar
            {
                if(ColorScheme==0)
                {
                    if(max_chase_width) hsv.hue = 1.0 - (i*1.0/max_chase_width); // rainbow hue
                }
                //  if(R_TO_L1)
                if(ChaseDirection==1) // are we going R-L?
                    new_x = x-i;    //  yes
                else
                    new_x = x+i;
                if(new_x<0)
                {
                    y++;
                    ChaseDirection=1;   // we were going R to L, now switch to L-R
                    new_x+=width;
                }
                else if(new_x>width)
                {
                    y++;
                    ChaseDirection=0;   // we were going L-R, now switch to R-L
                    new_x-=width;
                }
                //new_x=new_x%BufferWi;
                if(i<=pixels_per_chase) // as long as the chase fits, keep drawing it
                {
                    if(ColorScheme==0)
                        SetPixel(new_x,y,hsv); // Turn pixel on
                    else
                    {
                        if(colorcnt==1)
                            ColorIdx=0;
                        else
                        {
                            ColorIdx=i/pixels_per_color;
                        }
                        if(ColorIdx>=colorcnt) ColorIdx=colorcnt-1;
                        palette.GetHSV(ColorIdx, hsv);
                        if(Chase_Fade3d1) hsv.value=orig_v - (i*1.0/max_chase_width); // fades data down over chase width
                        if(hsv.value<0.0) hsv.value=0.0;
                        SetPixel(new_x,y,hsv); // Turn pixel on
                    }
                }
            }
        }
    }
}