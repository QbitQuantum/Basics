//============================================================
// <T>将尾部项存入文件。</T>
//
// @param out 输出文件流。
//============================================================
void FCsvFooters::Store(TDataOutput& out){
   FDictionary<FCsvFooter*>::TIteratorC it = _pFooters->IteratorC();
   TString foot = TC("@footer.name\n");
   TBool showLabel = EFalse;
   TBool showDescription = EFalse;
   TInt count = 0;
   TInt lastFooterIndex = _pFooters->Count() - 1;
   while(it.Next()){
      FCsvFooter* pFoot = it.Value();
      foot.Append(pFoot->Name());
      if(count != lastFooterIndex){
         foot.Append(',');
      }else{
         foot.Append('\n');
      }

      TInt labelLength = RString::Length(pFoot->Label());
      if(labelLength){
         showLabel = ETrue;
      }
      TInt desLength = RString::Length(pFoot->Description());
      if(desLength){
         showDescription= ETrue;
      }
      ++count;
   }
   if(showLabel){
      foot.Append(TC("@footer.label\n"));
      count = 0;
      it.Reset();
      while(it.Next()){
         FCsvFooter* pFoot = it.Value();
         foot.Append(pFoot->Label());
         if(count != lastFooterIndex){
            foot.Append(',');
         }else{
            foot.Append('\n');
         }
      }
   }
   if(showDescription){
      foot.Append(TC("@head.description\n"));
      count = 0;
      it.Reset();
      while(it.Next()){
         FCsvFooter* pFoot = it.Value();
         foot.Append(pFoot->Description());
         if(count != lastFooterIndex){
            foot.Append(',');
         }else{
            foot.Append('\n');
         }
      }
   }
   out.Write((TCharC*)foot, foot.Length());
}