 void set_resend_interval(socket &s, milliseconds i)
 { s.setopt(REQ, REQ_RESEND_IVL, static_cast<int>(i.count())); }