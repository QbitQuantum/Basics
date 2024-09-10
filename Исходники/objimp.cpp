int
OBJImport::DoImport(const TCHAR *filename,ImpInterface *i,Interface *gi, BOOL suppressPrompts) {
	TriObject *object = CreateNewTriObject();
	if(!object)
		return 0;
	if(objFileRead(filename, &object->GetMesh())) {
		ImpNode *node = i->CreateNode();
		if(!node) {
			delete object;
			return 0;
			}
		Matrix3 tm;
		tm.IdentityMatrix();
		node->Reference(object);
		node->SetTransform(0,tm);
		i->AddNodeToScene(node);
		node->SetName(GetString(IDS_TH_WAVE_OBJ_NAME));
		i->RedrawViews();
		return 1;
		}
	return 0;
	}