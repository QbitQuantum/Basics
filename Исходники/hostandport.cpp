 StatusWith<HostAndPort> HostAndPort::parse(const StringData& text) {
     HostAndPort result;
     Status status = result.initialize(text);
     if (!status.isOK()) {
         return StatusWith<HostAndPort>(status);
     }
     return StatusWith<HostAndPort>(result);
 }