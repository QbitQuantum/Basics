static PyObject *get_perms(PyObject *self, PyObject *args)
{

	PyObject *py_perms = PyDict_New();
	//get file or directory name
    char *file;

    if (!PyArg_ParseTuple(args, "s", &file))
        return NULL;

	//setup security code
	PSECURITY_DESCRIPTOR pSD;
	PACL pDACL; 
    //GetNamedSecurityInfo() will give you the DACL when you ask for
    //DACL_SECURITY_INFORMATION. At this point, you have SIDs in the ACEs contained in the DACL. 
	ULONG result = GetNamedSecurityInfo(file,SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, 
	&pDACL, NULL, &pSD);

	if (result != ERROR_SUCCESS){ return NULL;}
	if (result == ERROR_SUCCESS){
		ACL_SIZE_INFORMATION aclSize = {0};
		if(pDACL != NULL){   
			if(!GetAclInformation(pDACL, &aclSize, sizeof(aclSize),
				AclSizeInformation)){
				return NULL;
			}
		}
	
		file_perms *fp = new file_perms[aclSize.AceCount];
		acl_info(pDACL, aclSize.AceCount, fp );
		
		//Dict
		for (ULONG i=0;i




//Boilerplate functions

//3 parts 
//name of python function
//C++ function
//flags METH_VARARGS means function takes variable number of args
static PyMethodDef fileperm_methods[] = {
	{ "get_perms", get_perms, METH_VARARGS },
	{ NULL }
};



void initfileperm()
{

Py_InitModule("fileperm",fileperm_methods);

}