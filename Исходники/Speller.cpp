bool SpellWordRaw(const WString& wrd, int lang, Vector<String> *withdia)
{
	Speller *f = sGetSpeller(lang);
	if(!f)
		return true;
	if(f->data.GetCount())
		return f->CheckOld(wrd);
	String awrd = ToUpper(ToAscii(wrd).ToString());
	String t1 = ToUtf8(wrd);
	String t2 = ToUtf8(ToLower(wrd));
	for(int i = 0;; i++) {
		if(i + 1 >= f->block.GetCount() || awrd <= f->block[i + 1].first) {
			for(;;) {
				if(i >= f->block.GetCount())
					return f->user.Find(wrd) >= 0;;
				LLOG("Spell block " << i << ": " << f->block[i].first);
				const SpellBlock& b = f->block[i++];
				if(b.first > awrd) {
					LLOG("  --- end");
					return f->user.Find(wrd) >= 0;;
				}
				FileIn in(f->path);
				String ctrl = sZet(in, b.offset, b.ctrl_len);
				String text = sZet(in, b.offset + b.ctrl_len, b.text_len);
				in.Close();
				String w;
				const char *s = ctrl;
				const char *e = ctrl.End();
				const char *t = text;
				const char *te = text.End();
				while(s < e && t < te) {
					w.Trim(*s++);
					while(*t)
						w.Cat(*t++);
					if(w == t1 || w == t2)
						return true;
					if(withdia && t2 == ToLower(ToAscii(w.ToWString()).ToString()))
						withdia->Add(w);
					t++;
				}
			}
		}
	}
	return f->user.Find(wrd) >= 0;;
}