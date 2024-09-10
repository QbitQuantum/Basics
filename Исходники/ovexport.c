boolean OvExportCmd::Export (const char* pathname) {
    Editor* editor = GetEditor();
    Selection* s = editor->GetSelection();
    OverlayIdrawComp* real_top = (OverlayIdrawComp*)editor->GetComponent();
    boolean ok = false;
    
    boolean empty = s->IsEmpty();

    OverlayIdrawComp* false_top = new OverlayIdrawComp();
    Iterator i;
    empty ? real_top->First(i) : s->First(i);
    while (empty ? !real_top->Done(i) : !s->Done(i)) {
      if (chooser_->idraw_format() || chooser_->postscript_format()) {
	OverlayComp* oc = empty 
	  ? new OverlayComp(real_top->GetComp(i)->GetGraphic()->Copy())
	  : new OverlayComp(s->GetView(i)->GetGraphicComp()->GetGraphic()->Copy());
	false_top->Append(oc);
      } else {
	OverlayComp* oc = empty 
	  ? (OverlayComp*)real_top->GetComp(i)->Copy()
	  : (OverlayComp*)s->GetView(i)->GetGraphicComp()->Copy();
	false_top->Append(oc);
      }
      empty ? real_top->Next(i) : s->Next(i);
    }
     
    OverlayPS* ovpsv;
    if (chooser_->idraw_format() || chooser_->postscript_format())
      ovpsv = (OverlayPS*) false_top->Create(POSTSCRIPT_VIEW);
    else
      ovpsv = (OverlayPS*) false_top->Create(SCRIPT_VIEW);
    if (ovpsv != nil) {
      
      filebuf fbuf;
      char* tmpfilename;
      
      if (chooser_->to_printer()) {
	tmpfilename = tmpnam(nil);
	false_top->SetPathName(tmpfilename);
	ok = fbuf.open(tmpfilename, output) != 0;
      } else {
	ok = fbuf.open(pathname, output) != 0;
      }
      
      if (ok) {
	ostream out(&fbuf);
	false_top->Attach(ovpsv);
	ovpsv->SetCommand(this);
	if (!chooser_->idraw_format() && !chooser_->postscript_format())
	  ((OverlayIdrawScript*)ovpsv)->SetByPathnameFlag(chooser_->by_pathname_flag());
	ovpsv->Update();
	ok = ovpsv->Emit(out);
	fbuf.close();
	
	if (chooser_->to_printer()) {
	  char cmd[CHARBUFSIZE];
	  if (strstr(pathname, "%s")) {
	    char buf[CHARBUFSIZE];
	    sprintf(buf, pathname, tmpfilename);    
	    sprintf(cmd, "(%s;rm %s)&", buf, tmpfilename);
	  } else
	    sprintf(cmd, "(%s %s;rm %s)&", pathname, tmpfilename, tmpfilename);
	  ok = system(cmd) == 0;
	}
      } 
      delete ovpsv;        
    }
    
    delete false_top;
    return ok;
}