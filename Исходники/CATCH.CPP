void game(int mx,int my)
{
        cleardevice();
        int x,y,cl=0,i,j,ctr=0,points=0,lives=3,dt=100;
        int *ycoord,*bomby;
        int delaytime[20];
        int randomcolor;

        int *xcoord,*bombx,numctr=0,playtime=0;
        int nob=0,bombctr=0,temp,selbomb;

        callmouse();
        setlimits(23,mx-23,23,my-23);
        delay(100);

        // ASSIGN THE SPEED
        for(i=0;i<10;i++){delaytime[i]=i+10;}

        // ALOCATE MEMORY FOR COORDINATES

        if((ycoord=(int *)malloc(10))==NULL||(xcoord=(int *)malloc(10))==NULL||(bomby=(int *)malloc(10))==NULL||(bombx=(int *)malloc(10))==NULL)
        {
                cout<<"\nMEMORY ALLOCATION ERROR!";
                getch();
                exit(0);

        }

        randomize();
        outline(mx,my);

//THE GAME BEGINS

        int start=clock(),end;
        for(i=0;i<lives;i++)
        {
                setcolor(WHITE);
                circle((mx-200)+(i*20),my-10,6);
                setfillstyle(SOLID_FILL,RED);
                floodfill((mx-200)+(i*20),my-10,WHITE);
        }

        for(;;)
        {



        //      ASSIGN COORDINATES TO BOMBS
                selbomb=random(10);
                if( (selbomb%7)==0 && nob<=3)
                {
                        *(bombx+bombctr)=50;
                        *(bomby+bombctr)=random(my-100)+50;
                        bombctr++;
                        nob++;
                }


        //      ASSIGN COORDINATES TO BUBLES
                if(numctr<3)
                {
                        *(xcoord+ctr)=48;
                        *(ycoord+ctr)=random(my-100)+48;
                        numctr++;
                        ctr++;
                }
        //      DROP THE BOMBS
                for(i=0;i<nob;i++)
                {
                        setcolor(WHITE);
                        circle(*(bombx+i),*(bomby+i),22);
                }

        //      CREATE BUBLES
                for(i=0;i<numctr;i++)
                {
                        randomcolor=random(5)+1;
                        setcolor(randomcolor);
                        circle(*(xcoord+i),*(ycoord+i),20);

                }
       //       MOUSE
                altermouse(x,y,cl);
                delay(dt);

       //       CHECK WHAT HAPPENED WITH BUBLES
                temp=numctr;
                for(i=0;i<temp;i++)
                {
                //      CHECK IF BUBLES WERE HIT
                        if(x < *(xcoord+i)+20 && x > *(xcoord+i)-20 && y< *(ycoord+i)+20 && y>*(ycoord+i)-20)
                        {
                                points+=10;
                                numctr--;
                                ctr=i;
                                cleardevice();
                                outline(mx,my);
                                for(j=0;j<lives;j++)
                                {
                                        setcolor(WHITE);
                                        circle((mx-200)+(j*20),my-10,6);
                                        setfillstyle(SOLID_FILL,RED);
                                        floodfill((mx-200)+(j*20),my-10,WHITE);
                                }

                        }
                //      DE-CREATE THE BUBLES
                        setcolor(BLACK);
                        circle(*(xcoord+i),*(ycoord+i),20);

                //      LET THE BUBLES MOVE
                        *(xcoord+i)+=delaytime[i];

                //      CHECK FOR PLAYER'S DEATH
                        if(xcoord[i]>=mx-48)
                        {
                                numctr--;
                                lives--;

                                if(lives==0){goto again;}
                                for(j=0;j<lives+1;j++)
                                {
                                        setcolor(BLUE);
                                        circle((mx-200)+(i*20),my-10,6);
                                        setfillstyle(SOLID_FILL,BLUE);
                                        floodfill((mx-200)+(j*20),my-10,BLUE);
                                }
                                for(j=0;j<lives;j++)
                                {
                                        setcolor(WHITE);
                                        circle((mx-200)+(j*20),my-10,6);
                                        setfillstyle(SOLID_FILL,RED);
                                        floodfill((mx-200)+(j*20),my-10,WHITE);
                                }
                                ctr=i;
                        }


                }

       //       CHECK WHAT HAPPENED WITH THE BOMB
                temp=nob;
                for(i=0;i<temp;i++)
                {
                //      CHECK FOR PLAYERS DEATH AND THE END OF GAME
                        if(x < *(bombx+i)+22 && x > *(bombx+i)-22 && y< *(bomby+i)+22 && y>*(bomby+i)-22)
                        {
                                goto again;

                        }
                //      DE-CREATE THE BOMBS
                        setcolor(BLACK);
                        circle(*(bombx+i),*(bomby+i),22);
                //      LET THE BOMBS MOVE
                        *(bombx+i)+=delaytime[i];
                //      CHECK FOR THE BOMBS DEATH
                        if(*(bombx+i)>=mx-45)
                        {
                                bombctr=i;
                                nob--;
                                *(bombx+bombctr)=48;
                                *(bomby+bombctr)=random(my-100)+50;
                                nob++;
                        }

                }
                end=clock();
                playtime=ceill((end-start)/CLK_TCK);
                if(playtime>10)
                {
                        dt-=10;
                        start=clock();
                }

        }
//      THIS IS THE END :

        again:
        cleardevice();
        outline(mx,my);
        endgame(points,mx,my);
        readscore(points);
        hidemouse();
        delete ycoord,xcoord;
        menu(mx,my);
}