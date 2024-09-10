void DocbookDocVisitor::visit(DocVerbatim *s)
{
  if (m_hide) return;
  SrcLangExt langExt = getLanguageFromFileName(m_langExt);
  switch(s->type())
  {
    case DocVerbatim::Code: // fall though
      m_t << "<literallayout><computeroutput>";
      Doxygen::parserManager->getParser(m_langExt)
        ->parseCode(m_ci,s->context(),s->text(),langExt,
            s->isExample(),s->exampleFile());
      m_t << "</computeroutput></literallayout>";
      break;
    case DocVerbatim::Verbatim:
      m_t << "<literallayout>";
      filter(s->text());
      m_t << "</literallayout>";
      break;
    case DocVerbatim::HtmlOnly:    
      break;
    case DocVerbatim::RtfOnly:     
      break;
    case DocVerbatim::ManOnly:     
      break;
    case DocVerbatim::LatexOnly:   
      break;
    case DocVerbatim::XmlOnly:     
      break;
    case DocVerbatim::DocbookOnly: 
      break;
      m_t << s->text();
      break;
    case DocVerbatim::Dot:
      {
        static int dotindex = 1;
        QCString baseName(4096);
        QCString name;
        QCString stext = s->text();
        m_t << "<para>" << endl;
        name.sprintf("%s%d", "dot_inline_dotgraph_", dotindex);
        baseName.sprintf("%s%d",
            (Config_getString("DOCBOOK_OUTPUT")+"/inline_dotgraph_").data(),
            dotindex++
            );
        QFile file(baseName+".dot");
        if (!file.open(IO_WriteOnly))
        {
          err("Could not open file %s.msc for writing\n",baseName.data());
        }
        file.writeBlock( stext, stext.length() );
        file.close();
        m_t << "    <figure>" << endl;
        m_t << "        <title>" << name << "</title>" << endl;
        m_t << "        <mediaobject>" << endl;
        m_t << "            <imageobject>" << endl;
        writeDotFile(baseName);
        m_t << "            </imageobject>" << endl;
        m_t << "       </mediaobject>" << endl;
        m_t << "    </figure>" << endl;
        m_t << "</para>" << endl;
      }
      break;
    case DocVerbatim::Msc:
      static int mscindex = 1;
      QCString baseName(4096);
      QCString name;
      QCString stext = s->text();
      m_t << "<para>" << endl;
      name.sprintf("%s%d", "msc_inline_mscgraph_", mscindex);
      baseName.sprintf("%s%d",
          (Config_getString("DOCBOOK_OUTPUT")+"/inline_mscgraph_").data(),
          mscindex++
          );
      QFile file(baseName+".msc");
      if (!file.open(IO_WriteOnly))
      {
        err("Could not open file %s.msc for writing\n",baseName.data());
      }
      QCString text = "msc {";
      text+=stext;
      text+="}";
      file.writeBlock( text, text.length() );
      file.close();
      m_t << "    <figure>" << endl;
      m_t << "        <title>" << name << "</title>" << endl;
      m_t << "        <mediaobject>" << endl;
      m_t << "            <imageobject>" << endl;
      writeMscFile(baseName);
      m_t << "            </imageobject>" << endl;
      m_t << "       </mediaobject>" << endl;
      m_t << "    </figure>" << endl;
      m_t << "</para>" << endl;
      break;
  }
}