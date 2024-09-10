static void
dup_parent_class(struct ZObjClass *self)
{
	if(self->parent == NULL)
		return;
	struct ZObjClass *new_parent = malloc(sizeof(struct ZObjClass));
	assert(new_parent != NULL);
	memset(new_parent, 0, sizeof(struct ZObjClass));
	new_parent->class_name = self->parent->class_name;
	new_parent->parent = self->parent->parent;
	new_parent->constructor = self->parent->constructor;
	new_parent->destructor = self->parent->destructor;
	new_parent->interfaces = makeMem(getMemIndex(self->parent->interfaces));
	new_parent->class_body = makeMem(getMemIndex(self->parent->class_body));
	memCpy(&new_parent->class_body, getMemPtr(&self->parent->class_body, 0, 0),
			getMemIndex(self->parent->class_body));
	for(int i = 0; i < GET_ITEM_NUM(self->parent->interfaces, struct ZObjInterface); ++i) {
		struct InterfaceInfo *info = find_interface(GET_TYPE_MEM(&self->parent->interfaces, 
							struct ZObjInterface, i)->interface_name);
		if(info == NULL) {
			printf("CRITICAL: can't find interface %s when dup_parent_class\n", 
				GET_TYPE_MEM(&self->parent->interfaces,struct ZObjInterface, i)->interface_name);
			continue;
		}
		void *body = malloc(info->struct_size);
		assert(body != NULL);
		if(GET_TYPE_MEM(&self->parent->interfaces, struct ZObjInterface, i)->interface_body)
		memcpy(body, 
			GET_TYPE_MEM(&self->parent->interfaces, struct ZObjInterface, i)->interface_body,
			info->struct_size);
		ADD_ITEM(&new_parent->interfaces, struct ZObjInterface, 
			((struct ZObjInterface){ 
				GET_TYPE_MEM(&self->parent->interfaces,struct ZObjInterface, i)->interface_name,
				body }));