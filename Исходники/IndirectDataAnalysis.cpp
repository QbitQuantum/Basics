/**
 * Opens a directory dialog.
 */
void IndirectDataAnalysis::openDirectoryDialog() {
  MantidQt::API::ManageUserDirectories *ad =
      new MantidQt::API::ManageUserDirectories(this);
  ad->show();
  ad->setFocus();
}