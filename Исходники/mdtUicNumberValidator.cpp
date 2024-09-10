QValidator::State mdtUicNumberValidator::validate(QString &input, int &pos) const
{
  QChar c;
  QString number;

  // Check if last char is valid
  if(pos > 0){
    c = input.at(pos-1);
    if((!c.isDigit())&&(c != ' ')&&(c != '-')){
      return QValidator::Invalid;
    }
  }

  // Try to build the number...

  //Remove unusable chars
  if(input.size() > 5){
    number = input.simplified();
    number.remove(" ");
    number.remove("-");
    // Check length:
    //  - We only know about 6 and 11 digits UIC numbers
    //  - If we have 7 or 12 digits, the control key is given
    if((number.size() == 6)||(number.size() == 7)||(number.size() == 11)||(number.size() == 12)){
      return QValidator::Acceptable;
    }
  }

  return QValidator::Intermediate;
}