   virtual void work()
    {
     Random random;

     for(unsigned pos=0; pos<Total ;setCurrent(++pos))
       {
        if( getCancel() )
          {
           setResult("test cancelled");

           return;
          }

        unsigned sy=random.select(1,1000);
        unsigned sx=sy+random.select(10000);

        test1(sx,sy);

        test2(sx,sy,random.select(1,1000),random.select(1,1000));

        test3((uCoord)sx,(uCoord)sy);
       }

     setResult("test ok");
    }