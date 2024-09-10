void PPFile::Parse(Stream& in)
{
	LTIMING("PPFile::Parse");
	for(int i = 0; i < ppmacro.GetCount(); i++)
		sAllMacros.Unlink(ppmacro[i]);
	ppmacro.Clear();
	item.Clear();
	includes.Clear();
	bool was_using = false;
	bool was_namespace = false;
	int  level = 0;
	bool incomment = false;
	Vector<int> namespace_block;
	bool next_segment = true;
	Index<int> local_segments;
	keywords.Clear();
	int linei = 0;
	Md5Stream md5;
	while(!in.IsEof()) {
		String l = in.GetLine();
		while(*l.Last() == '\\' && !in.IsEof()) {
			l.Trim(l.GetLength() - 1);
			l.Cat(in.GetLine());
		}
		RemoveComments(l, incomment);
		try {
			CParser p(l);
			if(p.Char('#')) {
				if(p.Id("define")) {
					if(next_segment) {
						PPItem& m = item.Add();
						m.type = PP_DEFINES;
						m.segment_id = ++sPPserial;
						next_segment = false;
						local_segments.Add(sPPserial);
					}
					CppMacro def;
					String   id = def.Define(p.GetPtr());
					if(id.GetCount()) {
						PPMacro m;
						m.segment_id = sPPserial;
						m.line = linei;
						m.macro = def;
						ppmacro.Add(sAllMacros.Put(id, m));
						md5.Put("#", 1);
						md5.Put(id);
						md5.Put(0);
						md5.Put(m.macro.md5, 16);
					}
				}
				else
				if(p.Id("undef")) {
					if(p.IsId()) {
						String id = p.ReadId();
						md5.Put("#", 1);
						md5.Put(id);
						md5.Put(1);
						int segmenti = -1;
						PPMacro *um = FindPPMacro(id, local_segments, segmenti);
						if(um && segmenti) { // heuristic: only local undefs are allowed
							PPItem& m = item.Add();
							m.type = PP_DEFINES;
							m.segment_id = ++sPPserial;
							um->undef_segment_id = m.segment_id;
							next_segment = true;
							local_segments.Add(sPPserial);
							if(id.GetCount()) {
								PPMacro m;
								m.segment_id = sPPserial;
								m.line = linei;
								m.macro.SetUndef();
								ppmacro.Add(sAllMacros.Put(id, m));
							}
						}
					}
				}
				else
				if(p.Id("include")) {
					PPItem& m = item.Add();
					next_segment = true;
					m.type = PP_INCLUDE;
					m.text = TrimBoth(p.GetPtr());
					if(IsNull(m.text))
						item.Drop();
					else
						includes.FindAdd(m.text);
					md5.Put('@');
					md5.Put(m.text);
				}
			}
			else {
				while(!p.IsEof()) {
					if(was_namespace) {
						int type = was_using ? PP_USING : PP_NAMESPACE;
						String id;
						while(p.Char2(':', ':'))
							id = "::";
						if(p.IsId()) {
							id << p.ReadId();
							while(p.Char2(':', ':') && p.IsId())
								id << "::" << p.ReadId();
							if(!was_using)
								namespace_block.Add(level);
							if(!was_using || level == 0) {
								PPItem& m = item.Add();
								next_segment = true;
								m.type = type;
								m.text = id;
							}
							md5.Put('$');
							md5.Put(type);
							md5.Put(id);
						}
						was_namespace = was_using = false;
					}
					else
					if(p.Id("using"))
						was_using = true;
					else
					if(p.Id("namespace"))
						was_namespace = true;
					else {
						was_using = was_namespace = false;
						if(p.IsId()) {
							static const VectorMap<String, String>& namespace_macro = GetNamespaceMacros();
							static const Index<String>& namespace_end_macro = GetNamespaceEndMacros();

							String id = p.ReadId();
							int q = namespace_macro.Find(id);
							if(q > 0) {
								PPItem& m = item.Add();
								next_segment = true;
								m.type = PP_NAMESPACE;
								m.text = namespace_macro[q];
								namespace_block.Add(level);
								level++;
								md5.Put('%');
								md5.Put(id);
							}
							else {
								q = namespace_end_macro.Find(id);
								if(q >= 0) {
									level--;
									CheckEndNamespace(namespace_block, level, md5);
								}
							}
							keywords.Add(id);
						}
						else
						if(p.Char('}')) {
							if(level > 0) {
								level--;
								CheckEndNamespace(namespace_block, level, md5);
							}
						}
						else
						if(p.Char('{'))
							level++;
						else
							p.SkipTerm();
					}
				}
			}
		}
		catch(...) {}
		linei++;
	}
	md5sum = md5.FinishString();
	Sort(keywords);
	Vector<int> remove;
	int i = 0;
	while(i < keywords.GetCount()) { // Remove identical items
		int ii = i;
		i++;
		while(i < keywords.GetCount() && keywords[ii] == keywords[i])
			remove.Add(i++);
	}
	keywords.Remove(remove);
}