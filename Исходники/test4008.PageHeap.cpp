   void extend(Rec &rec)
    {
     ulen len=random.select(rec.mem.len,rec.mem.len+rec.mem.len/2);

     if( rec.extend(heap,len) ) stat.count(OpExtendDone);

     stat.count(OpExtend);
    }