void RTFDocVisitor::visitPre(DocSection *s)
{
  if (m_hide) return;
  DBG_RTF("{\\comment RTFDocVisitor::visitPre(DocSection)}\n");
  if (!m_lastIsPara) m_t << "\\par" << endl;
  m_t << "{\\bkmkstart " << rtfFormatBmkStr(s->file()+"_"+s->anchor()) << "}" << endl;
  m_t << "{\\bkmkend " << rtfFormatBmkStr(s->file()+"_"+s->anchor()) << "}" << endl;
  m_t << "{{" // start section
      << rtf_Style_Reset;
  QCString heading;
  int level = QMIN(s->level()+1,4);
  heading.sprintf("Heading%d",level);
  // set style
  m_t << rtf_Style[heading]->reference << endl;
  // make table of contents entry
  filter(s->title());
  m_t << endl << "\\par" << "}" << endl;
  m_t << "{\\tc\\tcl" << level << " \\v ";
  filter(s->title());
  m_t << "}" << endl;
  m_lastIsPara=TRUE;
}