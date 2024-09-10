QList<Operators>  Operators::search_operator(const QString &operatorID, const QString &adminID)
{
     QList<Operators> operator_list;
     TSqlQuery query;
     query.exec("SELECT * FROM operators join connection on operators.operatorID = connection.operatorID WHERE connection.adminID = '"+adminID+"' AND connection.operatorID LIKE '%"+operatorID+"%'");
     while(query.next()){
         Operators a;  //建立一个对象a
         a.setOperatorID(query.value(0).toString());
         a.setOperatorName(query.value(1).toString());
         a.setOperatorNickname(query.value(2).toString());
         a.setOperatorPassword(query.value(3).toString());
        // a.setOperatorNumber(query.value(4).toString());
         a.setOperatorPhone(query.value(4).toString());
         a.setId(query.value(5).toString());
         a.setOperatorRole(query.value(6).toString());
         a.setOperatorStatus(query.value(7).toString());  //设置对象a中的相关值

         operator_list.append(a); //将a插入链表中
     }
         query.exec("SELECT * FROM operators join connection on operators.operatorID = connection.operatorID WHERE connection.adminID = '"+adminID+"' AND operators.operatorNickname LIKE '%"+operatorID+"%'");
         while(query.next()){
             Operators a;  //建立一个对象a
             a.setOperatorID(query.value(0).toString());
             a.setOperatorName(query.value(1).toString());
             a.setOperatorNickname(query.value(2).toString());
             a.setOperatorPassword(query.value(3).toString());
             a.setOperatorPhone(query.value(4).toString());
             a.setId(query.value(5).toString());
             a.setOperatorRole(query.value(6).toString());
             a.setOperatorStatus(query.value(7).toString());  //设置对象a中的相关值
             int j = 0;
             for(const auto &i : operator_list){
                if(i.operatorID() == a.operatorID()){
                 break;
                }else{
                    j = j +1;
                }
             }
             if(j == operator_list.length()){
                 operator_list.append(a); //将a插入链表中
         }//遍历链表，查找该对象是否已经存在，如果存在则不再插入链表，否则插入
     }
         query.exec("SELECT * FROM operators join connection on operators.operatorID = connection.operatorID WHERE connection.adminID = '"+adminID+"' AND operators.operatorStatus LIKE '%"+operatorID+"%'");
         while(query.next()){
             Operators a;  //建立一个对象a
             a.setOperatorID(query.value(0).toString());
             a.setOperatorName(query.value(1).toString());
             a.setOperatorNickname(query.value(2).toString());
             a.setOperatorPassword(query.value(3).toString());
             a.setOperatorPhone(query.value(4).toString());
             a.setId(query.value(5).toString());
             a.setOperatorRole(query.value(6).toString());
             a.setOperatorStatus(query.value(7).toString());  //设置对象a中的相关值
             int j = 0;
             for(const auto &i : operator_list){
                if(i.operatorID() == a.operatorID()){
                 break;
                }else{
                    j = j +1;
                }
             }
             if(j == operator_list.length()){
                 operator_list.append(a); //将a插入链表中
         }
     }
     return operator_list;
}