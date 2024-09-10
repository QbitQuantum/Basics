   virtual void layout()
    {
     Point size=getSize();

     Coord dx=Div(4,21)*size.x;
     Coord dy=Div(4,21)*size.y;

     Coord x0=dx/4;
     Coord y0=dy/4;

     Coord delta_x=dx+x0;
     Coord delta_y=dy+y0;

     if( dx>0 && dy>0 )
       {
        for(int i=0; i<4 ;i++)
          for(int j=0; j<4 ;j++)
            {
             pane[i][j]=Pane(x0+i*delta_x,y0+j*delta_y,dx,dy);
            }
       }
     else
       {
        for(int i=0; i<4 ;i++)
          for(int j=0; j<4 ;j++)
            {
             pane[i][j]=Empty;
            }
       }
    }