//************************************
// Method:    CreateJDestroyProto
// FullName:  CreateJDestroyProto
// Access:    public 
// Returns:   CKERROR
// Qualifier:
// Parameter: CKBehaviorPrototype **pproto
//************************************
CKERROR CreateJDestroyProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("PJDestroy");
	if(!proto) return CKERR_OUTOFMEMORY;

	/*! \page PJDestroy  

	<br>
	PJDestroy is categorized in \ref Joints
	<br>
	<br>See <A HREF="PJDestroy.cmo">PJDestroy.cmo</A>.

	<h3>Description</h3>
	Apply to a <A HREF="Documentation.chm::/beobjects/1_ck3dentity.html">3DEntity</A><br>
	Deletes a joint, given by references and type.

	<br>

	<h3>Technical Information</h3>

	\image html PJDestroy.png


	<SPAN CLASS="in">In: </SPAN> triggers the process
	<BR>
	<SPAN CLASS="out">Out: </SPAN> is activated when the process is completed.
	<BR>

	<SPAN CLASS="pin">Body B: </SPAN> The second body. Leave blank to create a joint constraint with the world. 
	<BR>

	<SPAN CLASS="pin">Joint Type:</SPAN> The joint type. This helps the building block to identify a joint constraint. As usual there can be only one joint of the type x between two bodies.
	<BR>

	<b>Sleeping:</b> This call wakes the actor(s) if they are sleeping.

	Is utilizing #pRigidBody #pWorld #PhysicManager #pWorld::deleteJoint().<br>
	*/

	proto->DeclareInput("In");
	proto->DeclareOutput("Out");

	proto->SetBehaviorCallbackFct( JDestroyCB );
	
	proto->DeclareInParameter("Body B",CKPGUID_3DENTITY,"ball2");
	proto->DeclareInParameter("Type",VTE_JOINT_TYPE,"");

	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetBehaviorFlags(CKBEHAVIOR_TARGETABLE);

	proto->SetFunction(JDestroy);
	*pproto = proto;
	return CK_OK;
}