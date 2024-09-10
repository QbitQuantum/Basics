// 10 <= HeightPct <= 100
void RgbEffects::RenderFire(int HeightPct)
{
    int x,y,i,r,v1,v2,v3,v4,n,new_index;
    if (state == 0)
    {
        for (i=0; i < FireBuffer.size(); i++)
        {
            FireBuffer[i]=0;
        }
    }
    // build fire
    for (x=0; x<BufferWi; x++)
    {
        r=x%2==0 ? 190+(rand() % 10) : 100+(rand() % 50);
        SetFireBuffer(x,0,r);
    }
    int step=255*100/BufferHt/HeightPct;
    int sum;
    for (y=1; y<BufferHt; y++)
    {
        for (x=0; x<BufferWi; x++)
        {
            v1=GetFireBuffer(x-1,y-1);
            v2=GetFireBuffer(x+1,y-1);
            v3=GetFireBuffer(x,y-1);
            v4=GetFireBuffer(x,y-1);
            n=0;
            sum=0;
            if(v1>=0)
            {
                sum+=v1;
                n++;
            }
            if(v2>=0)
            {
                sum+=v2;
                n++;
            }
            if(v3>=0)
            {
                sum+=v3;
                n++;
            }
            if(v4>=0)
            {
                sum+=v4;
                n++;
            }
            new_index=n > 0 ? sum / n : 0;
            if (new_index > 0)
            {
                new_index+=(rand() % 100 < 20) ? step : -step;
                if (new_index < 0) new_index=0;
                if (new_index >= FirePalette.size()) new_index = FirePalette.size()-1;
            }
            SetFireBuffer(x,y,new_index);
        }
    }
    for (y=0; y<BufferHt; y++)
    {
        for (x=0; x<BufferWi; x++)
        {
            //SetPixel(x,y,FirePalette[y]);
            SetPixel(x,y,FirePalette[GetFireBuffer(x,y)]);
        }
    }
}