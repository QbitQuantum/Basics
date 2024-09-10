 void IntegerMutation::mutate(QVariantMap &map, QString key){
     int newValue = this->mutate(map.value(key).toInt());
     map.remove(key);
     map.insert(key,QVariant((int)newValue));
 }