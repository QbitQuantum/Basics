/////////////////////////////////////////////////////////
// textMess
//
/////////////////////////////////////////////////////////
void TextBase :: breakLine(wstring line)
{
  // split the string wherever there is a '\n'
  while(line.length()>0){
    size_t pos=line.find('\n');
    
    // if not found, we're done
    if(wstring::npos == pos)break;
    wstring lin=line.substr(0,pos);

    m_theText.push_back(gem::string::getVisualLine(lin));
    line=line.erase(0,pos+1);
  }

  // if there is still a text append it
  if(line.length()) {
    //m_theText.push_back(line);
    m_theText.push_back(gem::string::getVisualLine(line));
  }
  makeLineDist();
  setModified();
}