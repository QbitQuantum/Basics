void WikiParser::parseDoxygen(String &Line)
{
	String Tmp;
	Array matches;
	Line.pregReplace("/\\\\p\\s([a-z_A-Z_0-9]+)/","<b style=\"color: #005000;\">$1</b>");
	Line.pregReplace("/\\\\b\\s([^\\s]+)/","<b>$1</b>");
	Line.pregReplace("/^\\\\brief\\s(.*)$/","$1<br>");
	if (Line.pregMatch("/^\\\\desc(.*)$/i", matches)) {
		doxygenChapter(Line,"Beschreibung:",matches);
	}
	if (Line.pregMatch("/^\\\\return(.*)$/i",matches)) {
		doxygenChapter(Line,"Rückgabe:",matches);
	}
	if (Line.pregMatch("/^\\\\example(.*)$/i",matches)) {
		doxygenChapter(Line,"Beispiel:",matches);
	}
	if (Line.pregMatch("/^\\\\history(.*)$/i",matches)) {
		doxygenChapter(Line,"Historie:",matches);
	}

	if (Line.pregMatch("/^\\\\sourcecode(.*)$/i",matches)) {
		doxygenChapter(Line,"Quellcode:",matches);
	}

	if (Line.pregMatch("/^\\\\note(.*)$/i",matches)) {
		doxygenChapter(Line,"Hinweis:",matches);
	}
	if (Line.pregMatch("/^\\\\attention(.*)$/i",matches)) {
		doxygenChapter(Line,"Achtung:",matches);
	}

	if (Line.pregMatch("/^\\\\par$/i")) {
		Line="";
		for (int i=indentlevel;i>0;i--) Line+="</div>";
		indentlevel=0;
		Line+="<div style=\"margin-left: 30px;\">";
		indentlevel++;
	}
	if (Line.pregMatch("/^\\\\syntax\\s+(.*)$/i",matches)) {
		Line="";
		for (int i=indentlevel;i>0;i--) Line+="</div>";
		indentlevel=0;
		Line+="<b>Syntax:</b><div style=\"margin-left: 30px;\">";
		String s=matches[1];
		if (s.pregMatch("/^(.+)\\s+(.+)\\s*\\((.*)\\)$/",matches)) {
			Line.appendf("<span style=\"color: #400000;\">%s</span> <b>%s</b>(",
					matches.getPtr(1), matches.getPtr(2));
			Array Tok;
			StrTok(Tok,matches[3],",");
			// TODO
			String tt;
			int c=0;
			for (size_t j=0;j<Tok.size();j++) {
				tt=Tok[j];
				if (tt.pregMatch("/^(.*)\\s+(.*)$/",matches)) {
					if (c) Line+=", ";
					Line.appendf("<span style=\"color: #400000;\">%s</span> <b style=\"color: #005000;\">%s</b>",
							(const char*)matches[1], (const char*)matches[2]);
					c++;
				}

			}
		}
		Line+=")</div>";
	}

	if (Line.pregMatch("/^\\\\param\\s*\\[(.+)\\]\\s{0}(.+?)\\s+(.*)$/i",matches)) {
		Line="";
		if (!doxyparamsStarted) {
			for (int i=indentlevel;i>0;i--) Line+="</div>";
			indentlevel=0;
			doxyparamsStarted=true;
			Line+="<b>Parameter:</b><div style=\"margin-left: 30px;\">\n";
			indentlevel++;
		}

		Line+="<ul><li>[";
		Line+=matches[1];
		Line+="] <b style=\"color: #005000;\">";
		Line+=matches[2];
		Line+="</b> ";
		Line+=matches[3];
		Line+="</li></ul>";
		nobr=true;
	}
	if (Line.pregMatch("/^\\\\param\\s+(.+?)\\s+(.*)$/i",matches)) {
		Line="";
		if (!doxyparamsStarted) {
			for (int i=indentlevel;i>0;i--) Line+="</div>";
			indentlevel=0;
			doxyparamsStarted=true;
			Line+="<b>Parameter:</b><div style=\"margin-left: 30px;\">\n";
			indentlevel++;
		}
		Line+="<ul><li><b style=\"color: #005000;\">";
		Line+=matches[1];
		Line+="</b> ";
		Line+=matches[2];
		Line+="</li></ul>";
	}

}