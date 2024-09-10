Error ResourceInteractiveLoaderText::rename_dependencies(FileAccess *p_f, const String &p_path,const Map<String,String>& p_map) {




#if 0
	open(p_f);
	ERR_FAIL_COND_V(error!=OK,error);

	//FileAccess

	bool old_format=false;

	FileAccess *fw = NULL;

	String base_path=local_path.get_base_dir();

	while(true) {
		bool exit;
		List<String> order;

		Tag *tag = parse_tag(&exit,true,&order);

		bool done=false;

		if (!tag) {
			if (fw) {
				memdelete(fw);
			}
			error=ERR_FILE_CORRUPT;
			ERR_FAIL_COND_V(!exit,error);
			error=ERR_FILE_EOF;

			return error;
		}

		if (tag->name=="ext_resource") {

			if (!tag->args.has("index") || !tag->args.has("path") || !tag->args.has("type")) {
				old_format=true;
				break;
			}

			if (!fw) {

				fw=FileAccess::open(p_path+".depren",FileAccess::WRITE);
				fw->store_line("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"); //no escape
				fw->store_line("<resource_file type=\""+resource_type+"\" subresource_count=\""+itos(resources_total)+"\" version=\""+itos(VERSION_MAJOR)+"."+itos(VERSION_MINOR)+"\" version_name=\""+VERSION_FULL_NAME+"\">");

			}

			String path = tag->args["path"];
			String index = tag->args["index"];
			String type = tag->args["type"];


			bool relative=false;
			if (!path.begins_with("res://")) {
				path=base_path.plus_file(path).simplify_path();
				relative=true;
			}


			if (p_map.has(path)) {
				String np=p_map[path];
				path=np;
			}

			if (relative) {
				//restore relative
				path=base_path.path_to_file(path);
			}

			tag->args["path"]=path;
			tag->args["index"]=index;
			tag->args["type"]=type;

		} else {

			done=true;
		}

		String tagt="\t<";
		if (exit)
			tagt+="/";
		tagt+=tag->name;

		for(List<String>::Element *E=order.front();E;E=E->next()) {
			tagt+=" "+E->get()+"=\""+tag->args[E->get()]+"\"";
		}
		tagt+=">";
		fw->store_line(tagt);
		if (done)
			break;
		close_tag("ext_resource");
		fw->store_line("\t</ext_resource>");

	}


	if (old_format) {
		if (fw)
			memdelete(fw);

		DirAccess *da = DirAccess::create(DirAccess::ACCESS_FILESYSTEM);
		da->remove(p_path+".depren");
		memdelete(da);
		//f**k it, use the old approach;

		WARN_PRINT(("This file is old, so it can't refactor dependencies, opening and resaving: "+p_path).utf8().get_data());

		Error err;
		FileAccess *f2 = FileAccess::open(p_path,FileAccess::READ,&err);
		if (err!=OK) {
			ERR_FAIL_COND_V(err!=OK,ERR_FILE_CANT_OPEN);
		}

		Ref<ResourceInteractiveLoaderText> ria = memnew( ResourceInteractiveLoaderText );
		ria->local_path=Globals::get_singleton()->localize_path(p_path);
		ria->res_path=ria->local_path;
		ria->remaps=p_map;
	//	ria->set_local_path( Globals::get_singleton()->localize_path(p_path) );
		ria->open(f2);

		err = ria->poll();

		while(err==OK) {
			err=ria->poll();
		}

		ERR_FAIL_COND_V(err!=ERR_FILE_EOF,ERR_FILE_CORRUPT);
		RES res = ria->get_resource();
		ERR_FAIL_COND_V(!res.is_valid(),ERR_FILE_CORRUPT);

		return ResourceFormatSaverText::singleton->save(p_path,res);
	}

	if (!fw) {

		return OK; //nothing to rename, do nothing
	}

	uint8_t c=f->get_8();
	while(!f->eof_reached()) {
		fw->store_8(c);
		c=f->get_8();
	}

	bool all_ok = fw->get_error()==OK;

	memdelete(fw);

	if (!all_ok) {
		return ERR_CANT_CREATE;
	}

	DirAccess *da = DirAccess::create(DirAccess::ACCESS_RESOURCES);
	da->remove(p_path);
	da->rename(p_path+".depren",p_path);
	memdelete(da);
#endif
	return OK;

}