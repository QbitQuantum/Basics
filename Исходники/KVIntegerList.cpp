//___________________________________________________________________________________________
void KVIntegerList::SetPartition(const Char_t* par)
{
//protected method, utilisée par le Streamer qui utilise le champ fName de la classe TNamed
//voir également KVIntegerList::DeducePartitionFromTNamed
   KVString st(par);
   st.Begin(" ");
   TObjArray* toks = 0;
   while (!st.End()) {
      KVString tamp = st.Next();
      Int_t val;
      Int_t freq;
      if (tamp.Contains("(")) {
         if (!tamp.Contains(")")) {
            Warning("SetPartition", "%s ->pb de coherence dans les parentheses", tamp.Data());
            return;
         } else {
            toks = tamp.Tokenize("(");
            val = ((TObjString*)toks->At(0))->GetString().Atoi();
            freq = ((TObjString*)toks->At(1))->GetString().Atoi();
            delete toks;
         }
      } else {
         val = tamp.Atoi();
         freq = 1;
      }
      Add(val, freq);
   }

}