int collision_bleu(Calque calque,int posx_bleu,int y)
{ if(getpixel(calque.img,posx_bleu+20,y+88)== 65535 && getpixel(calque.img,posx_bleu+80,y+88)== 65535)
   {return 2;}
  else if(getpixel(calque.img,posx_bleu+20,y+88) == 16777215)
  {return 1;}
  else
  {return 0;}
}