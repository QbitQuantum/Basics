// @pymethod (SuccessfulAuditedRights,FailedAuditRights)|PyACL|GetAuditedPermissionsFromAcl|Return types of access for which ACL will generate an audit event for specified trustee
// @comm This function is known to return the success and failure access masks in the the wrong order
//       on Windows 2000 service pack 4.  Problem has been reported to Microsoft.
PyObject *PyACL::PyGetAuditedPermissionsFromAcl(PyObject *self, PyObject *args)
{
	DWORD err=0;
	ACCESS_MASK success_mask=0,fail_mask=0;
	PyACL *This = (PyACL *)self;
	ACL *pacl=This->GetACL();
	PyObject *ret=NULL, *obTrustee=NULL;
	TRUSTEE_W trustee;
	// @pyparm <o PyTRUSTEE>|trustee||Dictionary representing a TRUSTEE structure
	if (!PyArg_ParseTuple(args, "O:GetAuditedPermissionsFromAcl", &obTrustee))
		return NULL;
	if (!PyWinObject_AsTRUSTEE(obTrustee, &trustee))
		return NULL;
	// ???? SDK docs say the success mask is first, but on Win2k sp4 they're returned in the opposite order ????
	err=GetAuditedPermissionsFromAclW(This->GetACL(), &trustee, &success_mask, &fail_mask);
	if (err!=ERROR_SUCCESS)
		PyWin_SetAPIError("GetAuditedPermissionsFromAcl",err);
	else
		ret=Py_BuildValue("ll",success_mask,fail_mask);
	PyWinObject_FreeTRUSTEE(&trustee);
	return ret;
}