    void test(ulen len,ulen rep)
    {
        H hash;
        uint8 buf[100];
        uint8 digest[H::DigestLen];

        SecTimer timer;

        for(ulen cnt=rep; cnt ; cnt--)
        {
            for(ulen cnt=len; cnt ;)
            {
                ulen delta=random.select(1,Min(cnt,DimOf(buf)));

                auto r=Range(buf,delta);

                random.fill(r);
                hash.add(Range_const(r));

                cnt-=delta;
            }

            hash.finish(digest);
        }

        auto t=timer.get();

        if( !t ) t=1;

        uint64 s=uint64(len)*rep;
        uint8 sum=Sum(Range_const(digest));

        Printf(Con,"#; len = #; byte time = #; sec speed = #; Mbips\n",H::GetName(),s,t,((s*8)/t)/1000000,sum);
    }