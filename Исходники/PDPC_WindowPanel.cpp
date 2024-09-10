int PDPC_WindowPanel::AddProperty(bool editable,char *name,char* type,char* value){
	int length;
	if(m_properitesNum>=m_allocatedMem)
		AllocatePropertySet(m_allocatedMem*2);
	PropertyDesc*desc=(PropertyDesc*) malloc (sizeof(PropertyDesc));
	m_content[m_properitesNum]=desc;
	m_content[m_properitesNum]->m_editable=editable;
	length=min(PROPETY_NAME_MAX_L-1,strlen(name)+1);
	StringCchCopyA(m_content[m_properitesNum]->m_name,length,name);
	m_content[m_properitesNum]->m_name[PROPETY_NAME_MAX_L-1]='\0';

	length=min(PROPETY_TYPE_MAX_L-1,strlen(type)+1);
	StringCchCopyA(m_content[m_properitesNum]->m_type,length,type);
	m_content[m_properitesNum]->m_type[PROPETY_TYPE_MAX_L-1]='\0';

	length=min(PROPETY_VALUE_MAX_L-1,strlen(value)+1);
	StringCchCopyA(m_content[m_properitesNum]->m_value,length,value);
	m_content[m_properitesNum]->m_value[PROPETY_VALUE_MAX_L-1]='\0';
	m_properitesNum++;
	return 0;
}