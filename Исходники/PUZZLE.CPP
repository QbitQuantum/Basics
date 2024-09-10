void main()
{
 int gdriver = DETECT, gmode;
 initgraph(&gdriver, &gmode, "\\tc\\bgi");
 fstream file;
 file.open("levels.txt",ios::binary|ios::in);
 if(!file)
  cout<<"Couldnt open the file";
 file.read((char*)&game.level,sizeof(game.level));
 file.close();
 cleardevice();
 while(game.level<16)
 { if(game.level==1)
   { game.level1();
     drawextra(game.level,game.lives); }
   else if(game.level==2)
   { game.level2();
     drawextra(game.level,game.lives); }
   else if(game.level==3)
   { game.level3();
     drawextra(game.level,game.lives); }
   else if(game.level==4)
   { game.level4();
     drawextra(game.level,game.lives); }
   else if(game.level==5)
   { game.level5();
     drawextra(game.level,game.lives); }
   else if(game.level==6)
   { game.level6();
     drawextra(game.level,game.lives); }
   else if(game.level==7)
   { game.level7();
     drawextra(game.level,game.lives); }
   else if(game.level==8)
   { game.level8();
     drawextra(game.level,game.lives); }
   else if(game.level==9)
   { game.level9();
     drawextra(game.level,game.lives); }
   else if(game.level==10)
   { game.level10();
     drawextra(game.level,game.lives); }
   else if(game.level==11)
   { game.level11();
     drawextra(game.level,game.lives); }
   else if(game.level==12)
   { game.level12();
     drawextra(game.level,game.lives); }
   else if(game.level==13)
   { game.level13();
     drawextra(game.level,game.lives); }
   else if(game.level==14)
   { game.level14();
     drawextra(game.level,game.lives); }
   else if(game.level==15)
   { game.level15();
     drawextra(game.level,game.lives); }
   game.common(); }
 if(game.level==16)
 { spawnl(P_WAIT,"winpuzzl.exe",NULL);
   cleardevice();
   exit(0); }
 closegraph();
}