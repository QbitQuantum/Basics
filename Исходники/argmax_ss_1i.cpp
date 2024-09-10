void argmax_ss_1i_i::streamIdChanged(const std::string& id) {
   RH_ProvidesPortMap::iterator in_port;
   in_port = inPorts.find("short_in");
   bulkio::InFloatPort *port = dynamic_cast<   bulkio::InFloatPort * >(in_port->second);
   BULKIO::StreamSRISequence_var sris = port->activeSRIs();
   if (sris->length() > 0 ) {
     BULKIO::StreamSRI sri = sris[sris->length()-1];
     setOutputStreamSRI(sri);
   }
}