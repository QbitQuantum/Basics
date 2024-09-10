U0 DrawIt(CTask *task,CDC *dc)
{
  U8 buf[128];
  I64 i;
//<CTLR-T> to see the syntax of the
//"Insert Binary" statement in the following.
  for (i=0;i<NUM_TREES;i++)
    SpritePlot3(dc,trees_x[i],trees_y[i]-cur_screen_y,0,$IB,"<2>",2$);

  dc->collision_cnt=0;
  dc->color=ROP_COLLISION;
  dc->bkcolor=WHITE;
  SpritePlot3(dc,x,y,0,$IB,"<1>",1$);
  if (dc->collision_cnt) {
    Snd(400);
    penalty++;
  } else
    Snd(0);

  dc->color=ROP_EQU;
  SpritePlot3(dc,x,y,0,$IB,"<1>",1$);
//Text attr include forground in the
//lowest 4 bits and background in the upper 4.
  SPrintF(buf,"Penalty:%d",penalty);
  PlotWinStr(task,buf,BLACK+WHITE*16,1,1);
}