// ------------------------------------------------------------------------------- RHTML_text_view - KeyDown -
void RHTMLtextview::KeyDown(const char *bytes, int32 numBytes)
{
	pushmenu = false;
	int32 c,d;
	GetSelection(&c, &d);
	BString *oldtext = new BString(Text());
	BString *newtext = 0;
	switch(bytes[0])
	{
		case B_ESCAPE:			// - ESC
		{
		}
		break;
		case B_ENTER:				// - ENTER
		{
			fTarget->SetModify(true);
			BString tmp = "";
			if (d - OffsetAt(CurrentLine()) > 0)
			{
				for (int i = OffsetAt(CurrentLine()); i < d; i++)
				{
					if (Text()[i] == B_SPACE || Text()[i] == B_TAB)
					{
						tmp << Text()[i];
					} else
						break;
				}
			}
			BTextView::KeyDown(bytes, numBytes);
			Insert(tmp.String());

			fFileTypes->SetFontAndColor(oldtext, newtext = new BString(Text()), 0, c);
   
			if (fUpdateTimer->IsActive())
				fUpdateTimer->ResetTimer();
			else
				fUpdateTimer->StartTimer(fOptions->ReakcioIdo);
   
			if (PointAt(TextLength() - 1).y + 50 > fTarget->fNumView->Bounds().bottom) fTarget->fNumView->ResizeTo(fTarget->fNumView->Bounds().right, PointAt(TextLength() - 1).y + 50);
		}
		break;
		case '>':					// - >
		{
			fTagMenu->Stop();
   fTarget->SetModify(true);
   BTextView::KeyDown(bytes,numBytes);
   fFileTypes->SetFontAndColor(oldtext, newtext = new BString(Text()),0,c);

   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);

   if (PointAt(TextLength()-1).y+50>fTarget->fNumView->Bounds().bottom) fTarget->fNumView->ResizeTo(fTarget->fNumView->Bounds().right,PointAt(TextLength()-1).y+50);
  }
  break;
  case '<':					// - <
  {
   BTextView::KeyDown(bytes,numBytes);
   fTarget->SetModify(true);
   pushmenu=true;
   ScrollToSelection();
   fFileTypes->SetFontAndColor(oldtext, newtext = new BString(Text()),0,c);

   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);

   if (PointAt(TextLength()-1).y+50>fTarget->fNumView->Bounds().bottom) fTarget->fNumView->ResizeTo(fTarget->fNumView->Bounds().right,PointAt(TextLength()-1).y+50);
   mode=1;
   fTimer->StartTimer(fOptions->ReakcioIdoTM);
  }
  break;
  case B_SPACE:				// - SPACE
  {
   fTarget->SetModify(true);
   BTextView::KeyDown(bytes,numBytes);
   fFileTypes->SetFontAndColor(oldtext, newtext = new BString(Text()),0,c);

   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);

   if (PointAt(TextLength()-1).y+50>fTarget->fNumView->Bounds().bottom) fTarget->fNumView->ResizeTo(fTarget->fNumView->Bounds().right,PointAt(TextLength()-1).y+50);
   buf1 = "";
   int32 o;
   
   for (int i=c;i>=0;i--)
   {
    if (Text()[i]=='>') break;
    if (Text()[i]=='<')
    {
     for (o=i+1;o<=c+1;o++)
     {
      if (Text()[o]=='>') break;
      if (Text()[o]=='<') break;

      if (Text()[o]==' ')
      {
       pushmenu=true;
       mode=2;
       fTimer->StartTimer(fOptions->ReakcioIdoTM);
       break;
       i=-1;
      }
      buf1 << Text()[o];
     }
    }
   }
   
   BString str(Text());
   int32 a,b;
   tags.clear();

   a=str.FindLast('<',c);

   if (a>str.FindLast('>',c))
   {
    b=str.FindFirst('>',c);
    int32 e=str.FindFirst('<',c);
    if (b>=0 && ((b<e && e>=0) || (e<0)))
    {
     while (str[a]!=' ')
      a++;
     a++;
     int32 i=a;
     while (i<b)
     {
      if (str[i]==' ')
      {
       BString tmp;
       str.CopyInto(tmp,a,i-a);
       tmp.ToLower();
       if (tmp!=" " && tmp!="")
        tags.push_back(tmp);
       a=i+1;
      }

      if (str[i]=='=')
      {
       BString tmp;
       str.CopyInto(tmp,a,i-a);
       tmp.ToLower();
       tags.push_back(tmp);
       if (str[i+1]=='"')
       {
        a=str.FindFirst('"',i+2)+1;
        i=a-1;
       }
       else
        a=i=str.FindFirst(' ',i+1);
      }

      i++;
     }
    }   
   }
  }
  break;
  case B_UP_ARROW:			// - UP
  {
   BTextView::KeyDown(bytes,numBytes);
   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);
  }
  break;
  case B_DOWN_ARROW:		// - DOWN
  {
   BTextView::KeyDown(bytes,numBytes);
   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);
  }
  break;
  case B_LEFT_ARROW:		// - LEFT
  {
   BTextView::KeyDown(bytes,numBytes);
   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);
  }
  break;
  case B_RIGHT_ARROW:		// - RIGHT
  {
   BTextView::KeyDown(bytes,numBytes);
   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);
  }
  break;
  case B_PAGE_UP:			// - PUP
  {
   BTextView::KeyDown(bytes,numBytes);
   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);
  }
  break;
  case B_PAGE_DOWN:			// - PDOWN
  {
   BTextView::KeyDown(bytes,numBytes);
   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);
  }
  break;
  case B_HOME:				// - HOME
  {
   BTextView::KeyDown(bytes,numBytes);
   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);
  }
  break;
  case B_END:				// - END
  {
   BTextView::KeyDown(bytes,numBytes);
   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);
  }
  break;
  case B_BACKSPACE:			// - BackSpace
  {
   fTarget->SetModify(true);
   BTextView::KeyDown(bytes,numBytes);
   fFileTypes->SetFontAndColor(oldtext, newtext = new BString(Text()),0,c-1);

   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);

   if (PointAt(TextLength()-1).y+50>fTarget->fNumView->Bounds().bottom) fTarget->fNumView->ResizeTo(fTarget->fNumView->Bounds().right,PointAt(TextLength()-1).y+50);
  }
  break;
  default:
  {
   fTarget->SetModify(true);
   BTextView::KeyDown(bytes,numBytes);
   fFileTypes->SetFontAndColor(oldtext, newtext = new BString(Text()),0,c);

   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);

   if (PointAt(TextLength()-1).y+50>fTarget->fNumView->Bounds().bottom) fTarget->fNumView->ResizeTo(fTarget->fNumView->Bounds().right,PointAt(TextLength()-1).y+50);

   if (fUpdateTimer->IsActive())
    fUpdateTimer->ResetTimer();
   else
    fUpdateTimer->StartTimer(fOptions->ReakcioIdo);

   if (PointAt(TextLength()-1).y+50>fTarget->fNumView->Bounds().bottom) fTarget->fNumView->ResizeTo(fTarget->fNumView->Bounds().right,PointAt(TextLength()-1).y+50);
  }
 }
	if (oldtext)
 		delete oldtext;
	if (newtext)
 		delete newtext;
// ScrollToSelection();
}