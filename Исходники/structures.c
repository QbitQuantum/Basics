void print_message (int level, const struct message *msg) {
  begin_line ();
  print_spaces (level);
  struct user *user = 0;
  if (!disable_sql) {
    user = vk_db_lookup_user (msg->uid);
    if (!user) {
      aio_profiles_get (1, &msg->uid, 1);
    }
  }
  static char buf[1001];
  int len;
  /*
  if (!user) {  
    len = snprintf (buf, 1000, "Message #%d %s user %d", msg->id, msg->out ? "to" : "from", msg->uid);
  } else {
    len = snprintf (buf, 1000, "Message #%d %s user %d (%s %s)", msg->id, msg->out ? "to" : "from", msg->uid, user->first_name, user->last_name);
  }*/
  if (msg->out) {
    len = snprintf (buf, 1000, COLOR_RED);
  } else {
    len = snprintf (buf, 1000, COLOR_GREEN);
  }
  if (msg->chat_id) {
    len += snprintf (buf + len, 1000 - len, "Chat %s: ", msg->title);
    if (len >= 1000) { len = 1000; }
  }
  if (!user) {
    len += snprintf (buf + len, 1000 - len, "id%d ", msg->uid);
  } else {
    len += snprintf (buf + len, 1000 - len, "%s %s ", user->first_name, user->last_name);
  }
  add_string_line (buf, len);
  //end_line ();
  //begin_line ();

  int now = time (0);

  long _t = msg->date;
  struct tm *lctime = localtime ((void *)&_t);
  print_spaces (level + 1);

  if (now - msg->date <= 60 * 60 * 12) {
    len = snprintf (buf, 1000, "%02d:%02d ", lctime->tm_hour, lctime->tm_min);
  } else if (now - msg->date <= 60 * 60 * 24 * 30) {
    len = snprintf (buf, 1000, "%02d-%02d %02d:%02d ", lctime->tm_mon + 1, lctime->tm_mday, lctime->tm_hour, lctime->tm_min);
  } else {
    len = snprintf (buf, 1000, "%04d-%02d-%02d %02d:%02d ", lctime->tm_year + 1900, lctime->tm_mon + 1, lctime->tm_mday, lctime->tm_hour, lctime->tm_min);
  }
  /*len = snprintf (buf, 1000, "Created at [%04d-%02d-%02d %02d:%02d:%02d], state %s", 
    lctime->tm_year + 1900, lctime->tm_mon + 1, lctime->tm_mday, 
    lctime->tm_hour, lctime->tm_min, lctime->tm_sec,
    msg->deleted ? "deleted" : msg->read_state ? "read" : "unread");*/
  add_string_line (buf, len);
  
  len = snprintf (buf, 1000, "%s " COLOR_NORMAL, msg->out ? "<<<" : ">>>");
  add_string_line (buf, len);
  if (message_has_line_break (msg->body)) {
    end_line ();
    begin_line ();
    print_message_text (level + 1, msg->body ? msg->body : "<none>");
  } else {
    print_message_text (-1, msg->body ? msg->body : "<none>");
    if (line_pos) {
      end_line ();
    }
  }
  /*begin_line ();
  print_spaces (level + 1);
  if (msg->chat_id <= 0) {
    len = snprintf (buf, 1000, "No chat");
  } else {
    len = snprintf (buf, 1000, "Chat_id %d", msg->chat_id);
  }
  add_string_line (buf, len);
  end_line ();*/
}