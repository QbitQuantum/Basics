//************************************
// Method:    CreatePClothAttachVertexToPositionProto
// FullName:  CreatePClothAttachVertexToPositionProto
// Access:    public 
// Returns:   CKERROR
// Qualifier:
// Parameter: CKBehaviorPrototype **pproto
//************************************
CKERROR CreatePClothAttachVertexToPositionProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("PClothAttachVertexToPosition");
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("In");
	proto->DeclareOutput("Out");

	/*! \page PClothAttachVertexToPosition  

	PClothAttachVertexToPosition is categorized in \ref Clothes

	<h3>Description</h3>
	Apply to a <A HREF="Documentation.chm::/beobjects/1_ck3dentity.html">3DEntity</A><br>
	Attaches a cloth vertex to a position in world space.<br>

	@see pCloth::attachVertexToGlobalPosition()


	<h3>Technical Information</h3>

	\image html PClothAttachVertexToPosition.png

	<SPAN CLASS="in">In: </SPAN>triggers the process
	<BR>
	<SPAN CLASS="out">Out: </SPAN>is activated when the process is completed.
	<BR>
	<BR>
	
	
	<SPAN CLASS="pin">Target: </SPAN>Target cloth reference.
	<BR>
	<BR>

	<BR>
	<BR>
	<SPAN CLASS="pin">Vertex Index: </SPAN>Index of the vertex to attach.
	<BR>
	<BR>

	<SPAN CLASS="pin">Global Position: </SPAN>TThe position in world space.
	<BR>
	<BR>

	*/

	proto->SetBehaviorCallbackFct( PClothAttachVertexToPositionCB );

	proto->DeclareInParameter("Vertex Index",CKPGUID_INT);
	proto->DeclareInParameter("Global Position",CKPGUID_VECTOR);


	
	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetBehaviorFlags(CKBEHAVIOR_TARGETABLE);
	
	proto->SetFunction(PClothAttachVertexToPosition);
	*pproto = proto;
	return CK_OK;
}