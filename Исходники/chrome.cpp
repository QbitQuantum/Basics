// decrypt any entries found in database
void list_entries(std::string login_db) {
  sqlite3 *db;
  std::string::size_type mx_realm, mx_name, mx_pw;
  std::vector<entry*> entries;

  mx_realm = mx_name = mx_pw = 15;
  
  // open database
  if (sqlite3_open(login_db.c_str(), &db) == SQLITE_OK) {
    sqlite3_stmt *stmt;
    std::string query = "SELECT username_value, password_value, signon_realm"
                        " FROM logins";
    // execute SQL statement
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0) == SQLITE_OK) {
      while (sqlite3_step(stmt) == SQLITE_ROW) {
        DATA_BLOB in, out;
        std::string realm, name, passw;
          
        name = (char*)sqlite3_column_text(stmt, 0);
        realm = (char*)sqlite3_column_text(stmt, 2);

        in.pbData = (LPBYTE) sqlite3_column_blob(stmt, 1);
        in.cbData = sqlite3_column_bytes(stmt, 1);
            
        // decrypt using DPAPI
        if (CryptUnprotectData(&in, NULL, NULL, NULL, NULL, 1, &out)) {
          passw = (char*)out.pbData;
          passw[out.cbData] = 0;
            
          LocalFree(out.pbData);
        } else {
          passw = "<decryption failed>";
        }
        mx_realm = std::max(realm.length(), mx_realm);
        mx_name  = std::max(name.length(), mx_name);
        mx_pw    = std::max(passw.length(), mx_pw);
  
        entries.push_back(new entry(realm, name, passw));
      }
      sqlite3_finalize(stmt);
    } else {
      printf("\n  sqlite3_prepare_v2(\"%s\") : %s\n", 
        login_db.c_str(), sqlite3_errmsg(db));
    }
    sqlite3_close(db);
  } else {
    printf("\n  sqlite3_open(\"%s\") : %s\n", 
      login_db.c_str(), sqlite3_errmsg(db));
  }
  if (entries.size() > 0) {
    printf("  %-*s  %-*s  %-*s\n", 
      mx_name,  "Username", 
      mx_pw,    "Password", 
      mx_realm, "Realm");
          
    printf("  %s  %s  %s\n", 
      std::string(mx_name, '*').c_str(),
      std::string(mx_pw, '*').c_str(),
      std::string(mx_realm, '*').c_str());
    
    std::vector<entry*>::iterator it;
    for (it = entries.begin();it != entries.end();it++) {
      entry *e = *it;
      printf("  %-*s  %-*s  %-*s\n", 
        mx_name, e->name.c_str(),
        mx_pw, e->passw.c_str(), 
        mx_realm, e->realm.c_str());
    }
    entries.clear();
  } else {
    printf("\n  No entries found in \"%s\"", login_db.c_str());
  }
}