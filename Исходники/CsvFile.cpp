 void CsvFile::addRow(const StringList& list)
 {
   StringList elements = list;
   if (itemenclosed_)
   {
     for (Size i = 0; i < elements.size(); ++i)
     {
       elements[i].quote('"', String::NONE);
     }
   }
   String line;
   line.concatenate(elements.begin(), elements.end(), itemseperator_);
   addLine(line);
 }