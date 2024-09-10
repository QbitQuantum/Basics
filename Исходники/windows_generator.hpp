 uuid operator()()
 {
     UUID u_;
     UuidCreate(&u_);
     char *p = reinterpret_cast<char*>(&u_);
     uuid u;
     u.assign(p, p + sizeof(UUID));
     return u;
 }