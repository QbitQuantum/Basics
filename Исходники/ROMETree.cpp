//______________________________________________________________________________
Long64_t ROMETree::AutoSave(Option_t *option)
{
   Long64_t ret = 0;
   if (fAutoSaveSize > 0 && isWrite() && fTree && fTree->GetCurrentFile()) {
      ret = fTree->AutoSave(option);
#if (ROOT_VERSION_CODE > ROOT_VERSION(4,4,2))
      fLastSaveSize = fTree->GetCurrentFile()->GetBytesWritten();
#else
      fLastSaveSize = static_cast<Long64_t>(fTree->GetCurrentFile()->GetBytesWritten());
#endif
      TString opt = option;
      opt.ToLower();
   }
   return ret;
}