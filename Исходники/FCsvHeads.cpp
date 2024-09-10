//============================================================
// <T>将头部存入文件。</T>
//
// @param out 文件输出流。
//============================================================
void FCsvHeads::SaveToFile(TDataOutput& out){
   FDictionary<FCsvHead*>::TIteratorC it = _pHeads->IteratorC();
   TString head = TC("@head.name\n");
   TBool showLabel = EFalse;
   TBool showDescription = EFalse;
   TInt count = 0;
   TInt headCount = _pHeads->Count() - 1;
   while(it.Next()){
      FCsvHead* pHead = it.Value();
      head.Append(pHead->Name());
      if(count != headCount){
         head.Append(',');
      }else{
         head.Append('\n');
      }
      TInt labelLength = RString::Length(pHead->Label());
      if(labelLength){
         showLabel = ETrue;
      }
      TInt desLength = RString::Length(pHead->Description());
      if(desLength){
         showDescription= ETrue;
      }
      ++count;
   }
   if(showLabel){
      head.Append(TC("@head.label\n"));
      count = 0;
      it.Reset();
      while(it.Next()){
         FCsvHead* pHead = it.Value();
         head.Append(pHead->Label());
         if(count != headCount){
            head.Append(',');
         }else{
            head.Append('\n');
         }
      }
   }
   if(showDescription){
      head.Append(TC("@head.description\n"));
      count = 0;
      it.Reset();
      while(it.Next()){
         FCsvHead* pHead = it.Value();
         head.Append(pHead->Description());
         if(count != headCount){
            head.Append(',');
         }else{
            head.Append('\n');
         }
      }
   }
   out.Write((TCharC*)head, head.Length());
}