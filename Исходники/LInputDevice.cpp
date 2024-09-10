QString LInputDevice::variantToString(QVariant value){
  if( value.canConvert< QList<QVariant> >() ){
    //List of variants
    QStringList out;
    QList<QVariant> list = value.toList();
    for(int i=0; i<list.length(); i++){ out << variantToString(list[i]); }
    return out.join(", ");
  }else{
    //Single value
    if(value.canConvert<double>() ){
      return QString::number(value.toDouble());
    }else if(value.canConvert<int>() ){
     return QString::number(value.toInt());
    }else if( value.canConvert<QString>() ){
      //See if this is an atom first
      QString val = value.toString();
      if(val.contains("(")){ val = val.section("(",1,-1).section(")",0,0); }
      return val;
    }
  }
  return ""; //nothing to return
}