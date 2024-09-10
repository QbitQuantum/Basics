void Ctrl::CtrlPaint(SystemDraw& w, const Rect& clip) {
	GuiLock __;
	LEVELCHECK(w, this);
	LTIMING("CtrlPaint");
	
	Rect rect = GetRect().GetSize();
	Rect orect = rect.Inflated(overpaint);
	if(!IsShown() || orect.IsEmpty() || clip.IsEmpty() || !clip.Intersects(orect))
		return;
	
	w.PushContext();
	//glPushMatrix();
	ApplyTransform(TS_BEFORE_CTRL_PAINT);
		
	Ctrl *q;
	Rect view = rect;
	for(int i = 0; i < frame.GetCount(); i++) {
		LEVELCHECK(w, NULL);
		frame[i].frame->FramePaint(w, view);
		view = frame[i].view;
	}
	Rect oview = view.Inflated(overpaint);
	bool hasviewctrls = false;
	bool viewexcluded = false;
	
	for(q = firstchild; q; q = q->next)
		if(q->IsShown())
			if(q->InFrame()) {
				if(!viewexcluded && IsTransparent() && q->GetRect().Intersects(view)) {
					w.Begin();
					w.ExcludeClip(view);
					viewexcluded = true;
				}
				LEVELCHECK(w, q);
				Point off = q->GetRect().TopLeft();
				w.Offset(off);
				q->CtrlPaint(w, clip - off);
				w.End();
			}
			else
				hasviewctrls = true;

	if(viewexcluded)
		w.End();
	//DOLEVELCHECK;

	if(!oview.IsEmpty() && oview.Intersects(clip)) {
		LEVELCHECK(w, this);
		if(cliptobounds)
			w.Clip(overpaint ? oview : view);
		w.Offset(view.left, view.top);
		Paint(w);
		PaintCaret(w);		
		w.End();
		
		if(hasviewctrls && !view.IsEmpty()) {
			Rect cl = clip & view;
			for(q = firstchild; q; q = q->next)
				if(q->IsShown() && q->InView()) {
					Rect rr(q->popup ? clip : cl);
					LEVELCHECK(w, q);
					Rect qr = q->GetRect();
					Point off = qr.TopLeft() + view.TopLeft();
					Rect ocl = cl - off;
					if(ocl.Intersects(Rect(qr.GetSize()).Inflated(overpaint))) {
						w.Offset(off);
						q->CtrlPaint(w, rr - off);
						w.End();
					}
				}
		}

		if(cliptobounds)
			w.End();
	}
	
	ApplyTransform(TS_AFTER_CTRL_PAINT);
	//glPopMatrix();
	w.PopContext();
}