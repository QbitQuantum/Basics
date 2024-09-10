//___________________________________________________
void KVClassFactory::WriteClassWithTemplateHeader()
{
   //Writes the header file for a class using a template file.
   //The ClassDef line in the template file will be replaced with one corresponding to the new class.

   ofstream file_h;

   file_h.open( GetHeaderFileName() );

   WriteWhoWhen(file_h);
   WritePreProc(file_h);

   ifstream file_h_template;

   //open file whose full path was stored in fTemplateH
   if (!KVBase::SearchAndOpenKVFile(fTemplateH.Data(), file_h_template)) {
      //this should never happen!
      cout <<
          "<KVClassFactory::WriteClassWithTemplateHeader>: cannot open " <<
          fTemplateH.Data() << endl;
      return;
   }

   TString headFile;
   headFile.ReadFile(file_h_template);
   file_h_template.close();

   //find ClassDef
   Ssiz_t class_ind;
   if ((class_ind = headFile.Index("ClassDef")) > -1) {

      //cut file into two parts: before ClassDef line, after ClassDef line
      TString part1 = headFile(0, class_ind - 1);
      //keep part of file from "ClassDef" onwards.
      TString subs = headFile(class_ind, headFile.Length() - 1);
      //find next newline character i.e. the end of ClassDef line
      Ssiz_t nl = subs.Index("\n");
      TString part3 = subs(nl + 1, subs.Length() - 1);
      //write ClassDef line
      TString part2 = "   ClassDef(";
      part2 += fClassName;
      part2 += ",1)//";
      part2 += fClassDesc;
      part2 += "\n";

      KVString part_add;
   //write declarations of added methods
   if( fMethods.GetSize() ){
      KVString line;
      TIter next( &fMethods ); KVClassMethod* meth;
      while( (meth = (KVClassMethod*)next()) ){
         meth->WriteDeclaration(line);
         part_add += "   ";
         part_add += line;
         part_add += "\n";
      }
   }

      //stick all parts together
      headFile = part1 + part_add + part2 + part3;
   }

   file_h << headFile.ReplaceAll(fTemplateClassName.Data(),
                                 fClassName.Data());
   file_h << "\n\n#endif" << endl;      //don't forget to close the preprocessor #if !!!
   file_h.close();

   cout << "<KVClassFactory::WriteClassWithTemplateHeader> : File " << GetHeaderFileName() << " generated." << endl;

}