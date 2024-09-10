void Desktopwidget::renameDir ()
   {
   QString path = _dir->menuGetPath ();
   QString fullPath;
   bool ok;
   QString oldName = _dir->menuGetName ();
   QModelIndex index;

   index = _dir->menuGetModelIndex ();
   if (_model->findIndex (index) != -1)
      {
      QMessageBox::warning (0, "Maxview", "You cannot rename a root directory");
      return;
      }
   QString text = QInputDialog::getText(
            this, "Maxview", "Enter new directory name:", QLineEdit::Normal,
            oldName, &ok);
   if ( ok && !text.isEmpty() && text != oldName)
      {
      QDir dir;

      QModelIndex index = _dir->menuGetModelIndex ();
      QModelIndex parent = _model->parent (index);

//       if (!_model->setData (index, QVariant (text)))
      path.truncate (path.length () - oldName.length () - 1);
      fullPath = path + "/" + text;
      if (dir.rename (path + "/" + oldName, fullPath))
         _model->refresh (parent);
//          _dir->refreshItemRename (text);  // indicates current item has new children
      else
         QMessageBox::warning (0, "Maxview", "Could not rename directory");
      }
   }