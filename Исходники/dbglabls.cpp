void MON_LABELS::notify_user_labels()
{
   if (hNewUserLabels == INVALID_HANDLE_VALUE) return;
   // load labels at first check
   if (!hNewUserLabels) { start_watching_labels(); import_file(); return; }

   if (WaitForSingleObject(hNewUserLabels, 0) != WAIT_OBJECT_0) return;

   import_file();
   FindNextChangeNotification(hNewUserLabels);
}