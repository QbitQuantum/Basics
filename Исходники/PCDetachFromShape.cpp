//************************************
// Method:    CreatePClothDetachFromShapeProto
// FullName:  CreatePClothDetachFromShapeProto
// Access:    public 
// Returns:   CKERROR
// Qualifier:
// Parameter: CKBehaviorPrototype **pproto
//************************************
CKERROR CreatePClothDetachFromShapeProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("PClothDetachFromShape");
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("In");
	proto->DeclareOutput("Out");

	/*! \page PClothDetachFromShape  

	PClothDetachFromShape is categorized in \ref Clothes

	<h3>Description</h3>
	Apply to a <A HREF="Documentation.chm::/beobjects/1_ck3dentity.html">3DEntity</A><br>
	Detaches the cloth from a shape it has been attached to before<br>

	@see pCloth::detachFromShape()

	<h3>Technical Information</h3>

	\image html PClothDetachFromShape.png

	<SPAN CLASS="in">In: </SPAN>triggers the process
	<BR>
	<SPAN CLASS="out">Out: </SPAN>is activated when the process is completed.
	<BR>
	<BR>
	
	
	<SPAN CLASS="pin">Target: </SPAN>Target cloth reference.
	<BR>
	<BR>

	<SPAN CLASS="pin">Shape Reference: </SPAN>Shape to which the cloth should be attached to.

	
	<BR>
	<BR>

	<SPAN CLASS="pin">Attachment Flags: </SPAN>One or two way interaction, tearable or non-tearable
	*/

	proto->SetBehaviorCallbackFct( PClothDetachFromShapeCB );
	proto->DeclareInParameter("Shape Reference",CKPGUID_3DENTITY);


	
	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetBehaviorFlags(CKBEHAVIOR_TARGETABLE);
	
	proto->SetFunction(PClothDetachFromShape);
	*pproto = proto;
	return CK_OK;
}