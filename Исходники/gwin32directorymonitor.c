static GObject *
g_win32_directory_monitor_constructor (GType                  type,
				       guint                  n_construct_properties,
				       GObjectConstructParam *construct_properties) {
  GObject *obj;
  GWin32DirectoryMonitorClass *klass;
  GObjectClass *parent_class;
  GWin32DirectoryMonitor *self;
  wchar_t *wdirname;
  gboolean result;

  klass = G_WIN32_DIRECTORY_MONITOR_CLASS (g_type_class_peek (G_TYPE_WIN32_DIRECTORY_MONITOR));
  parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
  obj = parent_class->constructor (type, n_construct_properties, construct_properties);
  self = G_WIN32_DIRECTORY_MONITOR (obj);
  wdirname = g_utf8_to_utf16 (G_LOCAL_DIRECTORY_MONITOR (obj)->dirname, -1, NULL, NULL, NULL);

  self->priv->hDirectory = CreateFileW (wdirname,
					FILE_LIST_DIRECTORY,
					FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 

					NULL,
					OPEN_EXISTING,
					FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
					NULL); 
  g_free (wdirname);
  if (self->priv->hDirectory == INVALID_HANDLE_VALUE)
    {
      /* Ignore errors */
      return obj;
    }

  result = ReadDirectoryChangesW (self->priv->hDirectory,
				  (gpointer)self->priv->file_notify_buffer,
				  self->priv->buffer_allocated_bytes,
				  FALSE, 
				  FILE_NOTIFY_CHANGE_FILE_NAME |
				  FILE_NOTIFY_CHANGE_DIR_NAME |
				  FILE_NOTIFY_CHANGE_ATTRIBUTES |
				  FILE_NOTIFY_CHANGE_SIZE,
				  &self->priv->buffer_filled_bytes,
				  &self->priv->overlapped,
				  g_win32_directory_monitor_callback);
  /* Ignore errors */

  return obj;
}