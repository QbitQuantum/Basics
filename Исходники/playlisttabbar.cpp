void PlaylistTabBar::RenameInline() {
  emit Rename(tabData(menu_index_).toInt(), rename_editor_->text());
  HideEditor();
}