 void toJSON(JsonBuffer &buf) const
 {
     buf.String("term");
     buf.StartObject();
     buf.String(_field);
     _val.Accept(buf);
     buf.EndObject();
 }