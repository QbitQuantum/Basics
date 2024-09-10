bool CTextureDatabase::UpdateOldVersion(int version)
{
  BeginTransaction();
  try
  {
    if (version < 7)
    { // update all old thumb://foo urls to image://foo?size=thumb
      m_pDS->query("select id,texture from path where texture like 'thumb://%'");
      while (!m_pDS->eof())
      {
        unsigned int id = m_pDS->fv(0).get_asInt();
        CURL url(m_pDS->fv(1).get_asString());
        m_pDS2->exec(PrepareSQL("update path set texture='image://%s?size=thumb' where id=%u", url.GetHostName().c_str(), id));
        m_pDS->next();
      }
      m_pDS->query("select id, url from texture where url like 'thumb://%'");
      while (!m_pDS->eof())
      {
        unsigned int id = m_pDS->fv(0).get_asInt();
        CURL url(m_pDS->fv(1).get_asString());
        m_pDS2->exec(PrepareSQL("update texture set url='image://%s?size=thumb', urlhash=0 where id=%u", url.GetHostName().c_str(), id));
        m_pDS->next();
      }
      m_pDS->close();
    }
    if (version < 8)
    { // get rid of old cached thumbs as they were previously set to the cached thumb name instead of the source thumb
      m_pDS->exec("delete from path");
    }
    if (version < 9)
    { // get rid of the old path table and add the type column
      m_pDS->dropIndex("path", "idxPath");
      m_pDS->exec("DROP TABLE path");
      m_pDS->exec("CREATE TABLE path (id integer primary key, urlhash integer, url text, type text, texture text)\n");
      m_pDS->exec("CREATE INDEX idxPath ON path(urlhash, type)");
    }
    if (version < 10)
    { // get rid of urlhash in both tables...
      m_pDS->dropIndex("path", "idxPath");
      m_pDS->exec("DROP TABLE path");
      m_pDS->exec("CREATE TABLE path (id integer primary key, url text, type text, texture text)\n");
      m_pDS->exec("CREATE INDEX idxPath ON path(url, type)");

      m_pDS->dropIndex("texture", "idxTexture");
      m_pDS->exec("CREATE TEMPORARY TABLE texture_backup(id,url,cachedurl,usecount,lastusetime,imagehash,lasthashcheck)");
      m_pDS->exec("INSERT INTO texture_backup SELECT id,url,cachedurl,usecount,lastusetime,imagehash,lasthashcheck FROM texture");
      m_pDS->exec("DROP TABLE texture");
      m_pDS->exec("CREATE TABLE texture (id integer primary key, url text, cachedurl text, usecount integer, lastusetime text, imagehash text, lasthashcheck text)");
      m_pDS->exec("CREATE INDEX idxTexture ON texture(url)");
      m_pDS->exec("INSERT INTO texture SELECT * FROM texture_backup");
      m_pDS->exec("DROP TABLE texture_backup");
    }
    if (version < 11)
    { // get rid of cached URLs that don't have the correct extension
      m_pDS->exec("DELETE FROM texture WHERE SUBSTR(cachedUrl,-4,4) NOT IN ('.jpg', '.png')");
    }
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s(%d) failed", __FUNCTION__, version);
    RollbackTransaction();
    return false;
  }
  CommitTransaction();
  return true;
}