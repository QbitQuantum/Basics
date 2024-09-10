//============================================================
void FCsvLine::SinglePairRefer(TCharC* pValue, TString& result){
   TString refer = pValue;
   TInt length = refer.Length();
   TInt pos = 0;
   while(pos < length){
      TChar cur = refer[pos];
      if(cur == '"' && pos < length - 1){
         if(refer[pos + 1] == '"'){
            ++pos;
         }
      }
      result.Append(cur);
      ++pos;
   }
}