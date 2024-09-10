QoreHashNode* qore_httpclient_priv::send_internal(ExceptionSink* xsink, const char* mname, const char* meth, const char* mpath, const QoreHashNode* headers, const void* data, unsigned size, const ResolvedCallReferenceNode* send_callback, bool getbody, QoreHashNode* info, int timeout_ms, const ResolvedCallReferenceNode* recv_callback, QoreObject* obj) {
   assert(!(data && send_callback));

   // check if method is valid
   method_map_t::const_iterator i = method_map.find(meth);
   if (i == method_map.end()) {
       i = additional_methods_map.find(meth);
       if (i == additional_methods_map.end()) {
          xsink->raiseException("HTTP-CLIENT-METHOD-ERROR", "HTTP method (%s) not recognized.", meth);
          return 0;
       }
   }

   // make sure the capitalized version is used
   meth = i->first.c_str();
   bool bodyp = i->second;

   // use the default timeout value if a zero value is given in the call
   if (!timeout_ms)
      timeout_ms = timeout;

   SafeLocker sl(msock->m);
   Queue* cb_queue = msock->socket->getQueue();

   ReferenceHolder<QoreHashNode> nh(new QoreHashNode, xsink);
   bool keep_alive = true;

   bool transfer_encoding = false;

   if (headers) {
      ConstHashIterator hi(headers);
      while (hi.next()) {
	 // if one of the mandatory headers is found, then ignore it
	 strcase_set_t::iterator si = header_ignore.find(hi.getKey());
	 if (si != header_ignore.end())
	    continue;

	 // otherwise set the value in the hash
	 const AbstractQoreNode* n = hi.getValue();
	 if (!is_nothing(n)) {
	    if (!strcasecmp(hi.getKey(), "transfer-encoding"))
	       transfer_encoding = true;

	    nh->setKeyValue(hi.getKey(), n->refSelf(), xsink);

	    if (!strcasecmp(hi.getKey(), "connection") || (proxy_connection.has_url() && !strcasecmp(hi.getKey(), "proxy-connection"))) {
	       const char* conn = get_string_header(xsink, **nh, hi.getKey(), true);
	       if (*xsink) {
		  disconnect_unlocked();
		  return 0;
	       }
	       if (conn && !strcasecmp(conn, "close"))
		  keep_alive = false;
	    }
	 }
      }
   }

   // add default headers if they weren't overridden
   for (header_map_t::const_iterator hdri = default_headers.begin(), e = default_headers.end(); hdri != e; ++hdri) {
      // look in original headers to see if the key was already given
      if (headers) {
	 bool skip = false;
	 ConstHashIterator hi(headers);
	 while (hi.next()) {
	    if (!strcasecmp(hi.getKey(), hdri->first.c_str())) {
	       skip = true;
	       break;
	    }
	 }
	 if (skip)
	    continue;
      }
      // if there is no message body then do not send the "content-type" header
      if (!data && !send_callback && !strcmp(hdri->first.c_str(), "Content-Type"))
	 continue;
      nh->setKeyValue(hdri->first.c_str(), new QoreStringNode(hdri->second.c_str()), xsink);
   }

   // set Transfer-Encoding: chunked if used with a send callback
   if (send_callback && !transfer_encoding)
      nh->setKeyValue("Transfer-Encoding", new QoreStringNode("chunked"), xsink);

   if (!connection.username.empty()) {
      // check for "Authorization" header
      bool auth_found = false;
      if (headers) {
	 ConstHashIterator hi(headers);
	 while (hi.next()) {
	    if (!strcasecmp(hi.getKey(), "Authorization")) {
	       auth_found = true;
	       break;
	    }
	 }
      }

      if (!auth_found) {
	 QoreString tmp;
	 tmp.sprintf("%s:%s", connection.username.c_str(), connection.password.c_str());
	 QoreStringNode* auth_str = new QoreStringNode("Basic ");
	 auth_str->concatBase64(&tmp);
	 nh->setKeyValue("Authorization", auth_str, xsink);
      }
   }

   // save original HTTP method in case we have to issue a CONNECT request to a proxy for an HTTPS connection
   const char* meth_orig = meth;

   bool use_proxy_connect = false;
   const char* proxy_path = 0;
   ReferenceHolder<QoreHashNode> proxy_headers(xsink);
   QoreString hostport;
   if (!proxy_connected && proxy_connection.has_url()) {
      // use CONNECT if we need to make an HTTPS connection from the proxy
      if (!proxy_connection.ssl && connection.ssl) {
	 meth = "CONNECT";
	 use_proxy_connect = true;
	 hostport.concat(connection.host);
	 if (connection.port)
	    hostport.sprintf(":%d", connection.port);
	 proxy_path = hostport.getBuffer();
	 proxy_headers = new QoreHashNode;
	 proxy_headers->setKeyValue("Host", new QoreStringNode(hostport), xsink);

	 addProxyAuthorization(headers, **proxy_headers, xsink);
      }
      else
	 addProxyAuthorization(headers, **nh, xsink);
   }

   bool host_override = headers ? (bool)headers->getKeyValue("Host") : false;

   int code;
   ReferenceHolder<QoreHashNode> ans(xsink);
   int redirect_count = 0;
   const char* location = 0;

   // flag for aborted chunked sends
   bool send_aborted = false;

   while (true) {
      // set host field automatically if not overridden
      if (!host_override)
	 nh->setKeyValue("Host", getHostHeaderValue(), xsink);

      if (info) {
	 info->setKeyValue("headers", nh->copy(), xsink);
	 if (*xsink)
	    return 0;
      }

      //printd(5, "qore_httpclient_priv::send_internal() meth=%s proxy_path=%s mpath=%s upc=%d\n", meth, proxy_path ? proxy_path : "n/a", mpath, use_proxy_connect);
      // send HTTP message and get response header
      if (use_proxy_connect)
	 ans = sendMessageAndGetResponse(meth, proxy_path, *(*proxy_headers), 0, 0, 0, info, true, timeout_ms, code, send_aborted, xsink);
      else
	 ans = sendMessageAndGetResponse(meth, mpath, *(*nh), data, size, send_callback, info, false, timeout_ms, code, send_aborted, xsink);
      if (!ans)
	 return 0;

      if (info) {
	 info->setKeyValue("response-headers", ans->refSelf(), xsink);
	 if (*xsink)
	    return 0;
      }

      if (code >= 300 && code < 400) {
	 disconnect_unlocked();

	 host_override = false;
	 const QoreStringNode* mess = reinterpret_cast<QoreStringNode*>(ans->getKeyValue("status_message"));

	 const QoreStringNode* loc = get_string_header_node(xsink, **ans, "location");
	 if (*xsink)
	    return 0;
	 const char* location = loc && !loc->empty() ? loc->getBuffer() : 0;
	 if (!location) {
	    sl.unlock();
	    const char* msg = mess ? mess->getBuffer() : "<no message>";
	    xsink->raiseException("HTTP-CLIENT-REDIRECT-ERROR", "no redirect location given for status code %d: message: '%s'", code, msg);
	    return 0;
	 }

	 if (cb_queue)
	    do_redirect_event(cb_queue, msock->socket->getObjectIDForEvents(), loc, mess);

	 if (++redirect_count > max_redirects)
	    break;

	 if (set_url_unlocked(location, xsink)) {
	    sl.unlock();
	    const char* msg = mess ? mess->getBuffer() : "<no message>";
	    xsink->raiseException("HTTP-CLIENT-REDIRECT-ERROR", "exception occurred while setting URL for new location '%s' (code %d: message: '%s')", location, code, msg);
	    return 0;
	 }

	 // set redirect info in info hash if present
	 if (info) {
	    QoreString tmp;
	    tmp.sprintf("redirect-%d", redirect_count);
	    info->setKeyValue(tmp.getBuffer(), loc->refSelf(), xsink);
	    if (*xsink)
	       return 0;

	    tmp.clear();
	    tmp.sprintf("redirect-message-%d", redirect_count);
	    info->setKeyValue(tmp.getBuffer(), mess ? mess->refSelf() : 0, xsink);
	 }

	 // FIXME: reset send callback and send_aborted here

	 // set mpath to NULL so that the new path will be taken
	 mpath = 0;
	 continue;
      }
      else if (use_proxy_connect) {
	 meth = meth_orig;
	 use_proxy_connect = false;
	 proxy_path = 0;
	 if (msock->socket->upgradeClientToSSL(0, 0, xsink)) {
	    disconnect_unlocked();
	    return 0;
	 }
	 proxy_connected = true;

	 // remove "Proxy-Authorization" header
	 nh->removeKey("Proxy-Authorization", xsink);
	 if (*xsink)
	    return 0;

	 // try again as if we are talking directly to the client
	 continue;
      }

      break;
   }

   if (code >= 300 && code < 400) {
      sl.unlock();
      const char* mess = get_string_header(xsink, **ans, "status_message");
      if (!mess)
	 mess = "<no message>";
      if (!location)
	 location = "<no location>";
      xsink->raiseException("HTTP-CLIENT-MAXIMUM-REDIRECTS-EXCEEDED", "maximum redirections (%d) exceeded; redirect code %d to '%s' ignored (message: '%s')", max_redirects, code, location, mess);
      return 0;
   }

   // process content-type
   const QoreStringNode* v = get_string_header_node(xsink, **ans, "content-type");
   if (*xsink) {
      disconnect_unlocked();
      return 0;
   }
   //ans->getKeyValue("content-type");   

   // see if there is a character set specification in the content-type header
   if (v) {
      // save original content-type header before processing
      ans->setKeyValue("_qore_orig_content_type", v->refSelf(), xsink);

      const char* str = v->getBuffer();
      const char* p = strstr(str, "charset=");
      if (p && (p == str || *(p - 1) == ';' || *(p - 1) == ' ')) {
	 // move p to start of encoding
	 const char* c = p + 8;
	 char quote = '\0';
	 if (*c == '\'' || *c == '"') {
	    quote = *c;
	    ++c;
	 }
	 QoreString enc;
	 while (*c && *c != ';' && *c != ' ' && *c != quote)
	    enc.concat(*(c++));
	 
	 if (quote && *c == quote)
	    ++c;

	 printd(5, "QoreHttpClientObject::send_intern() setting encoding to '%s' from content-type header: '%s' (cs=%p c=%p %d)\n", enc.getBuffer(), str, p + 8, c);

	 // set new encoding
	 msock->socket->setEncoding(QEM.findCreate(&enc));
	 // strip from content-type
	 QoreStringNode* nc = new QoreStringNode();
	 // skip any spaces before the charset=
	 while (p != str && (*(p - 1) == ' ' || *(p - 1) == ';'))
	    p--;
	 if (p != str)
	    nc->concat(str, p - str);
	 if (*c)
	    nc->concat(c);
	 ans->setKeyValue("content-type", nc, xsink);
	 str = nc->getBuffer();
      }
      // split into a list if ";" characters are present
      p = strchr(str, ';');
      if (p) {
	 bool multipart = false;
	 QoreListNode* l = new QoreListNode();
	 do {
	    // skip whitespace
	    while (*str == ' ') str++;
	    if (str != p) {
	       int len = p - str;
	       check_headers(str, len, multipart, *(*ans), msock->socket->getEncoding(), xsink);
	       l->push(new QoreStringNode(str, len, msock->socket->getEncoding()));
	    }
	    str = p + 1;
	 } while ((p = strchr(str, ';')));
	 // skip whitespace
	 while (*str == ' ') str++;
	 // add last field
	 if (*str) {
	    check_headers(str, strlen(str), multipart, *(*ans), msock->socket->getEncoding(), xsink);
	    l->push(new QoreStringNode(str, msock->socket->getEncoding()));
	 }
	 ans->setKeyValue("content-type", l, xsink);
      }
   }

   // send headers to recv_callback
   if (recv_callback && msock->socket->priv->runHeaderCallback(xsink, mname, *recv_callback, &msock->m, *ans, send_aborted, obj))
      return 0;

   AbstractQoreNode* body = 0;
   const char* content_encoding = 0;

   // do not read any message body for messages that cannot have one
   // rfc 2616 4.4 p1 (http://tools.ietf.org/html/rfc2616#section-4.4)
   /*
     1.Any response message which "MUST NOT" include a message-body (such
     as the 1xx, 204, and 304 responses and any response to a HEAD
     request) is always terminated by the first empty line after the
     header fields, regardless of the entity-header fields present in
     the message.
    */
   //printd(5, "qore_httpclient_priv::send_internal() this: %p bodyp: %d code: %d\n", this, bodyp, code);

   qore_uncompress_to_string_t dec = 0;

   // code >= 300 && < 400 is already handled above
   if (bodyp && (code < 100 || code >= 200) && code != 204) {
      // see if we should do a binary or string read
      content_encoding = get_string_header(xsink, **ans, "content-encoding");
      if (*xsink) {
	 disconnect_unlocked();
	 return 0;
      }

      if (content_encoding) {
	 // check for misuse (? not sure: check RFCs again) of this field by including a character encoding value
	 if (!strncasecmp(content_encoding, "iso", 3) || !strncasecmp(content_encoding, "utf-", 4)) {
	    msock->socket->setEncoding(QEM.findCreate(content_encoding));
	    content_encoding = 0;
	 }
	 else if (!recv_callback) {
	    // only decode message bodies automatically if there is no receive callback
	    if (!strcasecmp(content_encoding, "deflate") || !strcasecmp(content_encoding, "x-deflate"))
	       dec = qore_inflate_to_string;
	    else if (!strcasecmp(content_encoding, "gzip") || !strcasecmp(content_encoding, "x-gzip"))
	       dec = qore_gunzip_to_string;
	    else if (!strcasecmp(content_encoding, "bzip2") || !strcasecmp(content_encoding, "x-bzip2"))
	       dec = qore_bunzip2_to_string;
	 }
      }

      const char* te = get_string_header(xsink, **ans, "transfer-encoding");
      if (*xsink) {
	 disconnect_unlocked();
	 return 0;
      }
   
      // get response body, if any
      const char* cl = get_string_header(xsink, **ans, "content-length");
      if (*xsink) {
	 disconnect_unlocked();
	 return 0;
      }
      int len = cl ? atoi(cl) : 0;
      
      if (cl && cb_queue)
	 do_content_length_event(cb_queue, msock->socket->getObjectIDForEvents(), len);

      if (te && !strcasecmp(te, "chunked")) { // check for chunked response body
	 if (cb_queue)
	    do_event(cb_queue, msock->socket->getObjectIDForEvents(), QORE_EVENT_HTTP_CHUNKED_START);
	 ReferenceHolder<QoreHashNode> nah(xsink);
	 if (recv_callback) {
	    if (content_encoding)
	       msock->socket->priv->readHttpChunkedBodyBinary(timeout_ms, xsink, QORE_SOURCE_HTTPCLIENT, recv_callback, &msock->m, obj);
	    else
	       msock->socket->priv->readHttpChunkedBody(timeout_ms, xsink, QORE_SOURCE_HTTPCLIENT, recv_callback, &msock->m, obj);
	 }
	 else {
	    if (content_encoding)
	       nah = msock->socket->priv->readHttpChunkedBodyBinary(timeout_ms, xsink, QORE_SOURCE_HTTPCLIENT);
	    else
	       nah = msock->socket->priv->readHttpChunkedBody(timeout_ms, xsink, QORE_SOURCE_HTTPCLIENT);
	 }
	 if (cb_queue)
	    do_event(cb_queue, msock->socket->getObjectIDForEvents(), QORE_EVENT_HTTP_CHUNKED_END);
	 
	 if (!nah && !recv_callback) {
	    if (!msock->socket->isOpen())
	       disconnect_unlocked();
	    return 0;
	 }

	 if (info) {
	    info->setKeyValue("chunked", &True, xsink);
	    if (*xsink)
	       return 0;
	 }
	 
	 if (!recv_callback) {
	    body = nah->takeKeyValue("body");
	    ans->merge(*nah, xsink);
	 }
      }
      else if (getbody || len) {
	 if (content_encoding) {
	    SimpleRefHolder<BinaryNode> bobj(msock->socket->recvBinary(len, timeout_ms, xsink));
	    if (!(*xsink) && bobj)
	       body = bobj.release();
	 }
	 else {
	    QoreStringNodeHolder bstr(msock->socket->recv(len, timeout_ms, xsink));
	    if (!(*xsink) && bstr)
	       body = bstr.release();
	 }
	 
	 if (*xsink && !msock->socket->isOpen())
	    disconnect_unlocked();
	 //printf("body=%p\n", body);
      }  
   }

   // check for connection: close header
   if (!keep_alive)
      disconnect_unlocked();
   else {
      const char* conn = get_string_header(xsink, **ans, "connection", true);
      if (*xsink) {
	 disconnect_unlocked();
	 return 0;
      }
      if (conn && !strcasecmp(conn, "close"))
	 disconnect_unlocked();
   }

   sl.unlock();

   // for content-encoding processing we can run unlocked

   // add body to result hash and process content encoding if necessary
   if (body) {
      if (content_encoding) {
	 if (!dec) {
	    if (!recv_callback) {
	       xsink->raiseException("HTTP-CLIENT-RECEIVE-ERROR", "don't know how to handle content-encoding '%s'", content_encoding);
	       ans = 0;
	    }
	 }
	 else {
	    BinaryNode* bobj = reinterpret_cast<BinaryNode*>(body);
	    QoreStringNode* str = dec(bobj, msock->socket->getEncoding(), xsink);
	    bobj->deref();
	    body = str;
	 }
      }

      if (body) {
	 // send data to recv_callback (already unlocked)
	 if (recv_callback) {
	    ReferenceHolder<> bh(body, xsink);
	    if (msock->socket->priv->runDataCallback(xsink, mname, *recv_callback, 0, body, false)
		|| msock->socket->priv->runHeaderCallback(xsink, mname, *recv_callback, 0, 0, send_aborted, obj))
	       return 0;
	 }
	 else
	    ans->setKeyValue("body", body, xsink);
      }
   }

   // do not throw an exception if a receive callback is used
   if (!recv_callback && !*xsink && (code < 100 || code >= 300)) {
      const char* mess = get_string_header(xsink, **ans, "status_message");
      if (!mess)
	 mess = "<no message>";
      assert(!*xsink);

      xsink->raiseExceptionArg("HTTP-CLIENT-RECEIVE-ERROR", ans.release(), "HTTP status code %d received: message: %s", code, mess);
      return 0;
   }

   return *xsink || recv_callback ? 0 : ans.release();
}