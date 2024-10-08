/*
* Document-method: initialize
*
* call-seq: initialize(args)
*
* +args+ should be a Hash and is required
*  This Hash should at least contain +:url+ and +:method+ keys.
*  You may also provide the following optional keys:
*    +:headers+ - should be a Hash of name/value pairs
*    +:response_header_handler+ - can be a string or object that responds to #call
*      If an object was passed, it's #call method will be called and passed the current chunk of data
*    +:response_body_handler+ - can be a string or object that responds to #call
*      If an object was passed, it's #call method will be called and passed the current chunk of data
*    +:payload+ - If +:method+ is either +:post+ or +:put+ this will be used as the request body
*
*/
static VALUE rb_streamly_init(int argc, VALUE * argv, VALUE self) {
  struct curl_instance * instance;
  VALUE args, url, payload, headers, username, password, credentials;

  GetInstance(self, instance);
  instance->handle = curl_easy_init();
  instance->request_headers = NULL;
  instance->request_method = Qnil;
  instance->request_payload_handler = Qnil;
  instance->response_header_handler = Qnil;
  instance->response_body_handler = Qnil;
  instance->options = Qnil;

  rb_scan_args(argc, argv, "10", &args);

    // Ensure our args parameter is a hash
  Check_Type(args, T_HASH);

  instance->request_method = rb_hash_aref(args, sym_method);
  url = rb_hash_aref(args, sym_url);
  payload = rb_hash_aref(args, sym_payload);
  headers = rb_hash_aref(args, sym_headers);
  username = rb_hash_aref(args, sym_username);
  password = rb_hash_aref(args, sym_password);
  instance->response_header_handler = rb_hash_aref(args, sym_response_header_handler);
  instance->response_body_handler = rb_hash_aref(args, sym_response_body_handler);

    // First lets verify we have a :method key
  if (NIL_P(instance->request_method)) {
    rb_raise(eStreamlyError, "You must specify a :method");
  } else {
        // OK, a :method was specified, but if it's POST or PUT we require a :payload
    if (instance->request_method == sym_post || instance->request_method == sym_put) {
      if (NIL_P(payload)) {
        rb_raise(eStreamlyError, "You must specify a :payload for POST and PUT requests");
      }
    }
  }

    // Now verify a :url was provided
  if (NIL_P(url)) {
    rb_raise(eStreamlyError, "You must specify a :url to request");
  }

  if (NIL_P(instance->response_header_handler)) {
    instance->response_header_handler = rb_str_new2("");
#ifdef HAVE_RUBY_ENCODING_H
    rb_encoding *default_internal_enc = rb_default_internal_encoding();
    if (default_internal_enc) {
      instance->response_header_handler = rb_str_export_to_enc(instance->response_header_handler, default_internal_enc);
    } else {
      instance->response_header_handler = rb_str_export_to_enc(instance->response_header_handler, utf8Encoding);
    }
#endif
  }
  if (instance->request_method != sym_head && NIL_P(instance->response_body_handler)) {
    instance->response_body_handler = rb_str_new2("");
#ifdef HAVE_RUBY_ENCODING_H
    rb_encoding *default_internal_enc = rb_default_internal_encoding();
    if (default_internal_enc) {
      instance->response_body_handler = rb_str_export_to_enc(instance->response_body_handler, default_internal_enc);
    } else {
      instance->response_body_handler = rb_str_export_to_enc(instance->response_body_handler, utf8Encoding);
    }
#endif
  }

  if (!NIL_P(headers)) {
    Check_Type(headers, T_HASH);
    rb_iterate(rb_each, headers, each_http_header, self);
    curl_easy_setopt(instance->handle, CURLOPT_HTTPHEADER, instance->request_headers);
  }

    // So far so good, lets start setting up our request

    // Set the type of request
  if (instance->request_method == sym_head) {
    curl_easy_setopt(instance->handle, CURLOPT_NOBODY, 1);
  } else if (instance->request_method == sym_get) {
    curl_easy_setopt(instance->handle, CURLOPT_HTTPGET, 1);
  } else if (instance->request_method == sym_post) {
    curl_easy_setopt(instance->handle, CURLOPT_POST, 1);
    curl_easy_setopt(instance->handle, CURLOPT_POSTFIELDS, RSTRING_PTR(payload));
    curl_easy_setopt(instance->handle, CURLOPT_POSTFIELDSIZE, RSTRING_LEN(payload));

    // (multipart)
    // curl_easy_setopt(instance->handle, CURLOPT_HTTPPOST, 1);

    // TODO: get streaming upload working
    // curl_easy_setopt(instance->handle, CURLOPT_READFUNCTION, &upload_data_handler);
    // curl_easy_setopt(instance->handle, CURLOPT_READDATA, &instance->upload_stream);
    // curl_easy_setopt(instance->handle, CURLOPT_INFILESIZE, len);
  } else if (instance->request_method == sym_put) {
    curl_easy_setopt(instance->handle, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(instance->handle, CURLOPT_POSTFIELDS, RSTRING_PTR(payload));
    curl_easy_setopt(instance->handle, CURLOPT_POSTFIELDSIZE, RSTRING_LEN(payload));

    // TODO: get streaming upload working
    // curl_easy_setopt(instance->handle, CURLOPT_UPLOAD, 1);
    // curl_easy_setopt(instance->handle, CURLOPT_READFUNCTION, &upload_data_handler);
    // curl_easy_setopt(instance->handle, CURLOPT_READDATA, &instance->upload_stream);
    // curl_easy_setopt(instance->handle, CURLOPT_INFILESIZE, len);
  } else if (instance->request_method == sym_delete) {
    curl_easy_setopt(instance->handle, CURLOPT_CUSTOMREQUEST, "DELETE");
  }

  // Other common options
  curl_easy_setopt(instance->handle, CURLOPT_URL, RSTRING_PTR(url));
  curl_easy_setopt(instance->handle, CURLOPT_FOLLOWLOCATION, 1);
  curl_easy_setopt(instance->handle, CURLOPT_MAXREDIRS, 3);

  // Response header handling
  curl_easy_setopt(instance->handle, CURLOPT_HEADERFUNCTION, &header_handler);
  curl_easy_setopt(instance->handle, CURLOPT_HEADERDATA, instance->response_header_handler);

  // Response body handling
  if (instance->request_method != sym_head) {
    curl_easy_setopt(instance->handle, CURLOPT_ENCODING, "identity, deflate, gzip");
    curl_easy_setopt(instance->handle, CURLOPT_WRITEFUNCTION, &data_handler);
    curl_easy_setopt(instance->handle, CURLOPT_WRITEDATA, instance->response_body_handler);
  }

  if (!NIL_P(username) || !NIL_P(password)) {
    credentials = rb_str_new2("");
    if (!NIL_P(username)) {
      rb_str_buf_cat(credentials, RSTRING_PTR(username), RSTRING_LEN(username));
    }
    rb_str_buf_cat(credentials, ":", 1);
    if (!NIL_P(password)) {
      rb_str_buf_cat(credentials, RSTRING_PTR(password), RSTRING_LEN(password));
    }
    curl_easy_setopt(instance->handle, CURLOPT_HTTPAUTH, CURLAUTH_BASIC | CURLAUTH_DIGEST);
    curl_easy_setopt(instance->handle, CURLOPT_USERPWD, RSTRING_PTR(credentials));
    rb_gc_mark(credentials);
  }

  curl_easy_setopt(instance->handle, CURLOPT_SSL_VERIFYPEER, 0);
  curl_easy_setopt(instance->handle, CURLOPT_SSL_VERIFYHOST, 0);

  curl_easy_setopt(instance->handle, CURLOPT_ERRORBUFFER, instance->error_buffer);

  return self;
}