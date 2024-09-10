void KVDMSDataRepository::DeleteFile(KVDataSet*ds,
                                  const Char_t * datatype,
                                  const Char_t * filename, Bool_t confirm)
{
   //Delete repository file [datasetdir]/[datatypedir]/[filename]
   //
   //By default (confirm=kTRUE) we ask for confirmation before deleting.
   //Set confirm=kFALSE to delete without confirmation (DANGER!!!)

   TString path, tmp;
   AssignAndDelete(path,
                   gSystem->ConcatFileName(fAccessroot.Data(), ds->GetDataPathSubdir()));
   AssignAndDelete(tmp, gSystem->ConcatFileName(path.Data(), ds->GetDataTypeSubdir(datatype)));
   AssignAndDelete(path, gSystem->ConcatFileName(tmp.Data(), filename));
   TString cmd;
   cout << "Deleting file from repository: " << filename << endl;
   if (confirm) {
      cout <<
          "Are you sure you want to delete this file permanently ? (y/n)"
          << endl;
      TString answer;
      cin >> answer;
      answer.ToUpper();
      if (!answer.BeginsWith("Y")) {
         cout << "File not deleted" << endl;
         return;
      }
   }
   fDMS->forcedelete(path.Data());
}