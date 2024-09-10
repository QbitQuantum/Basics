void ProjectSettings::_translation_delete(Object *p_item,int p_column, int p_button) {

	TreeItem *ti = p_item->cast_to<TreeItem>();
	ERR_FAIL_COND(!ti);

	int idx=ti->get_metadata(0);

	StringArray translations = Globals::get_singleton()->get("locale/translations");

	ERR_FAIL_INDEX(idx,translations.size());

	translations.remove(idx);

	undo_redo->create_action("Remove Translation");
	undo_redo->add_do_property(Globals::get_singleton(),"locale/translations",translations);
	undo_redo->add_undo_property(Globals::get_singleton(),"locale/translations",Globals::get_singleton()->get("locale/translations"));	
	undo_redo->add_do_method(this,"_update_translations");
	undo_redo->add_undo_method(this,"_update_translations");
	undo_redo->add_do_method(this,"_settings_changed");
	undo_redo->add_undo_method(this,"_settings_changed");
	undo_redo->commit_action();


}