void WebServer::EvaluateRequest(const RestInputStruct &REQ){
  RestOutputStruct out;
  if(REQ.VERB != "GET"){
    //Non-supported request (at the moment) - return an error message
    out.CODE = RestOutputStruct::BADREQUEST;
  }else{
    //GET request
    //Now check the body of the message and do what it needs
    QJsonDocument doc = QJsonDocument::fromJson(REQ.Body.toUtf8());
    if(doc.isNull()){ qWarning() << "Empty JSON Message Body!!" << REQ.Body.toUtf8(); }
    //Define the output structures
    QJsonDocument ret; //return message
    //parse the message and do something
    //Objects contain other key/value pairs - this is 99% of cases
    if(doc.isObject()){
      QJsonObject obj;
      QStringList keys = doc.object().keys();
      if(REQ.URI.toLower()=="/syscache"){
        QStringList reqs = keys.filter("request",Qt::CaseInsensitive);
        if(!reqs.isEmpty()){
	  qDebug() << "Parsing Inputs:" << reqs;
	  for(int r=0; r<reqs.length(); r++){
	    QString req =  JsonValueToString(doc.object().value(reqs[r]));
	    qDebug() << "  ["+reqs[r]+"]="+req;
	    QStringList values = SysCacheClient::parseInputs( QStringList() << req ); 
	    values.removeAll("");
	    //Quick check if a list of outputs was returned
	    if(values.length()==1){
	      values = values[0].split(SCLISTDELIM); //split up the return list (if necessary)
	      values.removeAll("");
	    }
	    qDebug() << " - Returns:" << values;
	    keys.removeAll(reqs[r]); //this key was already processed
	    if(values.length()<2){
	      obj.insert(reqs[r],values.join(""));
	    }else{
	      //This is an array of outputs
	      QJsonArray arr;
              for(int i=0; i<values.length(); i++){ arr.append(values[i]); }
	      obj.insert(reqs[r],arr);
            }
          }
        } //end of special "request" objects
      
      }else{
        qDebug() << "Object Variables:" << keys;
        for(int i=0; i<keys.length(); i++){
          qDebug() << keys[i]+"="+JsonValueToString(doc.object().value(keys[i]) );
        }	  
      }
      ret.setObject(obj);
    //Special case for a single syscache input (array of strings)
    }else if(doc.isArray() && REQ.URI.toLower()=="/syscache"){
        QStringList inputs = JsonArrayToStringList(doc.array());
        qDebug() << " syscache inputs:" << inputs;
        QJsonObject obj;
        QStringList values = SysCacheClient::parseInputs(inputs );
        for(int i=0; i<values.length(); i++){
	  if(values[i].contains(SCLISTDELIM)){
	    //This is an array of values
	    QStringList vals = values[i].split(SCLISTDELIM);
	    vals.removeAll("");
	    QJsonArray arr;
                for(int j=0; j<vals.length(); j++){ arr.append(vals[j]); }
	      obj.insert("Value"+QString::number(i),arr);
	  }else{
            obj.insert("Value"+QString::number(i),values[i]);
	  }
        }
      ret.setObject(obj);
    }
    //Assemble the outputs for this "GET" request
    out.CODE = RestOutputStruct::OK;
    out.Body = ret.toJson();
    out.Header << "Content-Type: text/json; charset=utf-8";
  }
  //Return any information
  csock->sendTextMessage(out.assembleMessage());
}