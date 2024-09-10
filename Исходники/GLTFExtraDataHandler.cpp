 shared_ptr <JSONObject> ExtraDataHandler::getExtras(COLLADAFW::UniqueId uniqueId)
 {
     std::string id = uniqueId.toAscii();
     
     if (!this->_allExtras->contains(id)) {
         this->_allExtras->setValue(id, shared_ptr<JSONObject> (new JSONObject()));
     }
     
     return static_pointer_cast<JSONObject>(this->_allExtras->getValue(id));
 }