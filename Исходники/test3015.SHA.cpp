void testCData()
 {
  Random random;
  typename T::Func hash;
  uint8 digest[T::Func::DigestLen];

  uint8 input[100];

  Range(input).set(T::Ch);

  for(ulen len=T::Len; len ;)
    {
     ulen delta=random.select(1,Min(len,DimOf(input)));

     hash.add(input,delta);

     len-=delta;
    }

  hash.finish(digest);

  //Printf(Con,"\n#;\n",PrintDump(Range(digest)));

  if( !Range(digest).equal(T::Digest) )
    {
     Printf(Exception,"#; failed",T::Func::GetName());
    }
 }