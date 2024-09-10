QoreStringNode* Datasource::getConfigString() const {
   QoreStringNode* str = new QoreStringNode(priv->dsl->getName());
   str->concat(':');

   if (!priv->username.empty())
      str->concat(priv->username);
   if (!priv->password.empty())
      str->sprintf("/%s", priv->password.c_str());
   if (!priv->dbname.empty())
      str->sprintf("@%s", priv->dbname.c_str());
   if (!priv->db_encoding.empty())
      str->sprintf("(%s)", priv->db_encoding.c_str());
   if (!priv->hostname.empty())
      str->sprintf("%%%s", priv->hostname.c_str());
   if (priv->port)
      str->sprintf(":%d", priv->port);

   bool first = false;
   ReferenceHolder<QoreHashNode> opts(qore_dbi_private::get(*priv->dsl)->getOptionHash(this), 0);
   ConstHashIterator hi(*opts);
   while (hi.next()) {
      const QoreHashNode* ov = reinterpret_cast<const QoreHashNode*>(hi.getValue());
      const AbstractQoreNode* v = ov->getKeyValue("value");
      if (!v || v == &False)
	 continue;

      if (first)
	 str->concat(',');
      else {
	 str->concat('{');
	 first = true;
      }
      str->concat(hi.getKey());
      if (v == &True)
	 continue;

      QoreStringValueHelper sv(v);
      str->sprintf("=%s", sv->getBuffer());
   }
   if (first)
      str->concat('}');

   return str;
}