/*
 * Returns false on error
 *         true  on OK, with full_path set to where config file should be
 */
bool CONFIG::find_config_path(POOL_MEM &full_path)
{
   bool found = false;
   POOL_MEM config_dir;
   POOL_MEM config_path_file;

   if (!m_cf) {
      /*
       * No path is given, so use the defaults.
       */
      found = get_config_file(full_path, get_default_configdir(), m_config_default_filename);
      if (!found) {
         config_path_file.strcpy(full_path);
         found = get_config_include_path(full_path, get_default_configdir());
      }
      if (!found) {
         Jmsg2(NULL, M_ERROR, 0,
               _("Failed to read config file at the default locations "
                 "\"%s\" (config file path) and \"%s\" (config include directory).\n"),
               config_path_file.c_str(), full_path.c_str());
      }
   } else if (path_exists(m_cf)) {
      /*
       * Path is given and exists.
       */
      if (path_is_directory(m_cf)) {
         found = get_config_file(full_path, m_cf, m_config_default_filename);
         if (!found) {
            config_path_file.strcpy(full_path);
            found = get_config_include_path(full_path, m_cf);
         }
         if (!found) {
            Jmsg3(NULL, M_ERROR, 0,
                  _("Failed to find configuration files under directory \"%s\". "
                  "Did look for \"%s\" (config file path) and \"%s\" (config include directory).\n"),
                  m_cf, config_path_file.c_str(), full_path.c_str());
         }
      } else {
         full_path.strcpy(m_cf);
         path_get_directory(config_dir, full_path);
         m_config_dir = bstrdup(config_dir.c_str());
         found = true;
      }
   } else if (!m_config_default_filename) {
      /*
       * Compatibility with older versions.
       * If m_config_default_filename is not set,
       * m_cf may contain what is expected in m_config_default_filename.
       */
      found = get_config_file(full_path, get_default_configdir(), m_cf);
      if (!found) {
         Jmsg2(NULL, M_ERROR, 0,
               _("Failed to find configuration files at \"%s\" and \"%s\".\n"),
               m_cf, full_path.c_str());
      }
   } else {
      Jmsg1(NULL, M_ERROR, 0, _("Failed to read config file \"%s\"\n"), m_cf);
   }

   if (found) {
      set_env("BAREOS_CFGDIR", m_config_dir);
   }

   return found;
}