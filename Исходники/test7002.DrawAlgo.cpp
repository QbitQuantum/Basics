   virtual void work()
    {
     Random random;

     unsigned delta=0;

     for(unsigned pos=0; pos<Total ;setCurrent(++pos))
       {
        if( getCancel() )
          {
           setResult("test cancelled");

           return;
          }

        unsigned sy=random.select(1,10000);
        unsigned sx=sy+random.select(10000);

        Replace_max(delta,test1(sx,sy));
       }

     char temp[TextBufLen];
     PrintBuf out(Range(temp));

     Printf(out,"delta = #;",delta);

     setResult(out.close());
    }