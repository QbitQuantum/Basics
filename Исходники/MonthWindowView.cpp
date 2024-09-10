void MonthWindowView::DrawMonth()
{
 Bmp->Lock();
 
 float y=yearStringView->Frame().bottom+h_cell;
 float x=0;
 
 if(NewMonth)
 {
  BmpView->SetHighColor(VIEW_COLOR);
  BmpView->FillRect(BRect(0,y+1,
                    BmpView->Bounds().right,todayStringView->Frame().top-6));
  BmpView->SetHighColor(0,0,0,0);
  NewMonth=false;
 }
 
 int byear=cyear; // base year
 if(tyear<byear) byear=tyear;
  
 int day1=0, m=0, k=byear;
 
 while(k<cyear)
 {
  day1++;

  if(k%4==0) // leap year?
   if((k%100!=0) || (k%400==0)) day1++; // yes
  
  k++;
 }
 while(++m<cmonth)
 {
  day1+=(monthDays[m-1]-28);
  if(m==2) if((cyear%4)==0) if((cyear%100!=0) || (cyear%400==0)) day1++;
 }
 day1++; // day1 is number of 1st day of chosen month in chosen year
 day1=day1%7;
 
 int day2=0;
 m=0;
 k=byear;
 while(k<tyear)
 {
  day2++;
  if((k%4)==0) if((k%100!=0) || (k%400==0)) day2++;
  k++;
 }
 while(++m<tmonth)
 {
  day2+=(monthDays[m-1]-28);
  if(m==2) if((tyear%4)==0) if((tyear%100!=0) || (tyear%400==0)) day2++;
 }
 day2+=tday; // day2 - number of today's day in today's year
 day2=day2%7;
 
 k=(twday==0) ? 6 : twday-1;
 
 k=k-day2+day1;
 while(k<0) k+=7;
 k=k%7;
 cwday1=k;
 
 x=w_cell*k+1;
 y+=h_cell;
 
 int qu_days=monthDays[cmonth-1]; // quantity of days in month
 
 if(cmonth==2) if(cyear%4==0) if((cyear%100!=0) || (cyear%400==0)) qu_days=29;
 
 BString s;
 int t=0;
 while(t<qu_days)
 {
  t++;
  
  s<<t;
  
  if(cyear==tyear) if(cmonth==tmonth) if(t==tday) BmpView->SetHighColor(200,0,0,0);
  BmpView->DrawString(s.String(),BPoint(x+(w_cell-StringWidth(s.String()))/2,y));
  if(cyear==tyear) if(cmonth==tmonth) if(t==tday) BmpView->SetHighColor(0,0,0,0);
  
  if(t==cday)
  {
   cwday=k;
   if(which_focused==2) BmpView->SetHighColor(ACTIVE_COLOR);
   else BmpView->SetHighColor(NOACTIVE_COLOR);
   cursor.Set(x,y-h_cell+5,x+w_cell-1,y+4);
   BmpView->StrokeRect(cursor);
   BmpView->SetHighColor(0,0,0,0);
  }
  
  x+=w_cell;
  k++;
  s.SetTo("");
  
  if(k==7)
  {
   k=0;
   y+=h_cell;
   x=1;
  }
 }
 
 BmpView->Sync();
 Bmp->Unlock();
 Draw(Bounds());
}