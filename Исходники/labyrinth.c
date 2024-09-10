++h;}SDL_FillRect(e,&k,255);}int main(int a,char**b){SDL_Event d;char z[99]="L"
"abyrinth ";SDL_Init(32);SDL_Surface*c=SDL_SetVideoMode(480,480,32,0);e=SDL_Cr\
eateRGBSurface(0,480,480,32,0,0,0,0);int t=SDL_GetTicks();g();while(1){if(SDL_\
PollEvent(&d)){if(d.type==12)break;else{int x=d.button.x;int y=d.button.y;if(d.
button.button==1&&x<f.x+13&&x>f.x-5&&y<f.y+13&&y>f.y-5){x=((x>>3)<<3)+1;y=((y>>
3)<<3)+1;if(!p(x+2,y+2)){f.x=x;f.y=y;if(f.x==k.x&&f.y==k.y){t=SDL_GetTicks();g(
);}}}}}SDL_BlitSurface(e,0,c,0);SDL_FillRect(c,&f,0);int u=SDL_GetTicks()-t;sp\
rintf(z+10,"%d",20-u/1000);SDL_WM_SetCaption(z,z);if(u>20000)break;SDL_Flip(c);
SDL_Delay(20);}SDL_FreeSurface(e);SDL_Quit();return 0;}