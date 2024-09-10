int read_recordtype_json_desc(void * root,void * record)
{

	int ret;
	void * data;
	void * struct_template;

	DB_RECORD * db_record=record;
	DB_RECORD * struct_record;
	struct struct_desc_record * struct_desc;
	struct struct_recordtype * recordtype;
	
	void * temp_node;

	if(db_record->head.type <=0)
		return -EINVAL;

	struct_template=memdb_get_template(db_record->head.type,db_record->head.subtype);
	if(struct_template==NULL)
		return -EINVAL;

	ret=Galloc0(&recordtype,sizeof(struct struct_recordtype));
	if(ret<0)
		return ret;

	temp_node=json_find_elem("uuid",root);
	if(temp_node==NULL)
		return -EINVAL;
	char * uuid_str=json_get_valuestr(temp_node);
	
	if(!Isvaliduuid(uuid_str))
	{
		struct_record=memdb_find_byname(uuid_str,DB_STRUCT_DESC,0);
		if(struct_record==NULL)
			return -EINVAL;		
		Memcpy(recordtype->uuid,struct_record->head.uuid,DIGEST_SIZE);
		ret=json_remove_node(temp_node);
	}

	ret=json_2_struct(root,recordtype,struct_template);
//	namelist->elem_no=json_get_elemno(temp_node);
	db_record->record=recordtype;

	ret=memdb_comp_uuid(db_record);
	if(ret<0)
		return ret;	
	ret=memdb_store_record(db_record);
	if(ret<0)
		return ret;
	ret=memdb_register_dynamicdb(recordtype->type,recordtype->subtype);

	return ret;	
}