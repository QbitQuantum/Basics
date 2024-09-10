void MiniPS::Dict::getNext (char const*const*& key, slen_t &keylen, VALUE *&val, bool &touched) {
  val+=2;
  if (len+(VALUE*)ptr==(VALUE*)val-1) { key=(char const*const*)NULLP; return; }
  Ename *skey=RENAME(val[-1]&~1);
  // assert(MiniPS::getType((VALUE)skey)==T_ENAME);
  key=(char**)&skey->ptr;
  keylen=skey->len;
  touched=(val[-1]&1)!=0;
}