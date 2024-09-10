void SGMExporter::ExportStaticPos(IGameNode *gNode, BinaryWriter *bw)
{
	/*INode *node = gNode ->GetMaxNode();
	assert(node != NULL);

	Control *tmCtrl = node ->GetTMController();
	assert(tmCtrl != NULL);

	Control *ctrl = tmCtrl ->GetPositionController();
	assert(ctrl != NULL);

	Interval i(0, 0);
	Point3 pos;
	ctrl ->GetValue(0, &pos, i, CTRL_ABSOLUTE);*/

	Point3 pos;
	GMatrix m = gNode ->GetLocalTM();
	pos = m.Translation();

	bw ->Write(pos.x);
	bw ->Write(pos.y);
	bw ->Write(pos.z);
}