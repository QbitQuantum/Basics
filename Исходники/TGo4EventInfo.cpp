void TGo4EventInfo::WorkWithEvent(const char* itemname)
{
   EventLbl->setText(itemname);

   bool ismbs = QString(itemname).contains(defMbsEventName);

   MbsPrintBox->setEnabled(ismbs);
   TString mbsitem = Browser()->FindItemInAnalysis(defMbsEventName);
   MbsButton->setEnabled(!ismbs && (mbsitem.Length()>0));
   setFocus();
}