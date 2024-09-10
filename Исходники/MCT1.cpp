//---------------------------------------------------------------------------
void __fastcall TForm1::BewegingstimerTimer(TObject *Sender)
{

//Neerzetten met double buffering:
   //achtergrond
   ImageCanvas->Picture=BackgroundImage->Picture;

   //musica
   Beep(random(500),500);

   //staff laten bewegen als barman
   if (b==0)
        {
           StaffImage->Left=StaffImage->Left+random(50)-25;
                if (StaffImage->Left<600) StaffImage->Left=600;
                if (StaffImage->Left>700) StaffImage->Left=700;
                ImageCanvas->Canvas->Draw(StaffImage->Left,StaffImage->Top,StaffImage->Picture->Graphic);
                ImageCanvas->Canvas->Draw(ItemImage->Left,ItemImage->Top,ItemImage->Picture->Graphic);
        }
   else   //het dwijlorkest
        {
           switch (dwijlorkest)
                {
                case 0:
                  ImageCanvas->Canvas->Draw(524,100,OrkestImage1->Picture->Graphic);
                  dwijlorkest=1;
                  break;
                case 1:
                  ImageCanvas->Canvas->Draw(525,100,OrkestImage2->Picture->Graphic);
                  dwijlorkest=0;
                  break;
                }
        }

   //dienblad:
   ImageCanvas->Canvas->Draw(10,140,ArrowImage->Picture->Graphic);
   ImageCanvas->Canvas->Draw(8,80,DienbladImage->Picture->Graphic);
   for (int t=0; t<aantalglazen+1; t++)
        {
         switch (t)
                {
                 case 0:
                   break;
                 case 1:
                   ImageCanvas->Canvas->Draw(48,80,GlasImage->Picture->Graphic);
                   break;
                 case 2:
                   ImageCanvas->Canvas->Draw(63,82,GlasImage->Picture->Graphic);
                   break;
                 case 3:
                   ImageCanvas->Canvas->Draw(28,84,GlasImage->Picture->Graphic);
                   break;
                 case 4:
                   ImageCanvas->Canvas->Draw(14,94,GlasImage->Picture->Graphic);
                   break;
                 case 5:
                   ImageCanvas->Canvas->Draw(30,94,GlasImage->Picture->Graphic);
                   break;
                 case 6:
                   ImageCanvas->Canvas->Draw(47,89,GlasImage->Picture->Graphic);
                   break;
                 case 7:
                   ImageCanvas->Canvas->Draw(61,90,GlasImage->Picture->Graphic);
                   break;
                 case 8:
                   ImageCanvas->Canvas->Draw(56,96,GlasImage->Picture->Graphic);
                   break;
                 case 9:
                   ImageCanvas->Canvas->Draw(88,88,GlasImage->Picture->Graphic);
                   break;
                 case 10:
                   ImageCanvas->Canvas->Draw(90,95,GlasImage->Picture->Graphic);
                   break;
                 case 11:
                   ImageCanvas->Canvas->Draw(74,95,GlasImage->Picture->Graphic);
                   break;
                }
        }


   //de glazen vullen:
   if(random(3)==1) c[random(10)][1]=1;     //kans 1op30;

   //de glazen tekenen als de bar er is:
   if (b==0)
        {
           for (int we=0; we<10; we++)
                {
                switch (c[we][1])
                        {
                        case 0:
                           break;
                        case 1:
                           ImageCanvas->Canvas->Draw(c[we][0],360,GlasImage->Picture->Graphic);
                           break;
                        }
                }
        }//end glazenifstatement

   //Linker Aliens
   for (int we=0; we<12; we++)  //waar tekent hij ze?
       {
       switch (a[we][2+b])        //wat doen ze? +b=voor veld 2
          {
          case 0: //leeg
            break;
          case 1: //geen glas -snik-
            ImageCanvas->Canvas->Draw(a[we][0],a[we][1],L0Image->Picture->Graphic);
            break;
          case 2: //wel glas, al dan niet drinken
            switch (random(2))
                {
                case 0:
                ImageCanvas->Canvas->Draw(a[we][0],a[we][1],L2Image->Picture->Graphic);
                break;
                case 1:
                ImageCanvas->Canvas->Draw(a[we][0],a[we][1],L1Image->Picture->Graphic);
                break;
                }
            break;
          }
       }
   //Rechter Aliens
   for (int we=12; we<24; we++)  //waar tekent hij ze?
       {
       switch (a[we][2+b])        //wat doen ze?   //b voor veld 2
          {
          case 0: //leeg
            break;
          case 1: //geen glas -snik-
            ImageCanvas->Canvas->Draw(a[we][0],a[we][1],R0Image->Picture->Graphic);
            break;
          case 2: //wel glas, al dan niet drinken
            switch (random(2))
                {
                case 0:
                ImageCanvas->Canvas->Draw(a[we][0],a[we][1],R2Image->Picture->Graphic);
                break;
                case 1:
                ImageCanvas->Canvas->Draw(a[we][0],a[we][1],R1Image->Picture->Graphic);
                break;
                }
            break;
          }
       }


//de muur:
ImageCanvas->Canvas->Draw(673,124,WallImage->Picture->Graphic);

//klaar
Form1->Canvas->Draw(0,0,ImageCanvas->Picture->Graphic);
}