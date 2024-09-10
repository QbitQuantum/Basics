void test2()
 {
  Random random;
  
  for(ulen cnt=Count; cnt ;cnt--)
    {
     UInt hi=random.next_uint<UInt>();
     UInt lo=random.next_uint<UInt>();
     UInt den=random.next_uint<UInt>();
     
     if( den==0 ) den=1;
     
     hi%=den;
     
     typename UIntFunc<UInt>::DivMod res(hi,lo,den);
     
     if( res.div!=UIntDiv(hi,lo,den) )
       {
        Printf(Exception,"Fail 2");
       }
     
     if( res.mod!=UIntMod(hi,lo,den) )
       {
        Printf(Exception,"Fail 3");
       }
     
     typename UIntFunc<UInt>::Mul mul(den,res.div);
     
     mul.hi+=UIntAdd(mul.lo,res.mod);
     
     if( mul.hi!=hi || mul.lo!=lo )
       {
        Printf(Exception,"Fail 4");
       }
    }
 }