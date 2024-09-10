void change()
{z=random(4);
if(z==0)
{if(getpixel(x++,y)!=c)x++;}
else if(z==1)
{if(getpixel(x--,y)!=c)x--;}
else if(z==2)
{if(getpixel(x,y++)!=c)y++;}
else if(z==3)
{if(getpixel(x,y--)!=c)y--;}
}