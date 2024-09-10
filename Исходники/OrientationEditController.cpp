/**
 @brief setting control diagramnode
 @date 2014-03-02
*/
void COrientationEditController::SetControlDiagram(CGenotypeNode *node)
{
	RemoveGenotypeTree(m_sample, m_rootNode);
	m_nodes.clear();
	m_rootNode = NULL;

	vector<CGenotypeNode*> nodes;
	m_genotypeController.GetDiagramsLinkto(node, nodes);
	if (nodes.empty())
		return;

	// Create Phenotype Node
	CGenotypeNode *parentNode = nodes[ 0];
	map<const genotype_parser::SExpr*, CGenotypeNode*> symbols;
	const PxTransform identTm = PxTransform::createIdentity();
	m_rootNode = CreatePhenotypeDiagram(identTm,identTm,identTm, parentNode->m_expr, symbols);

	// Camera Setting
	const PxVec3 parentPos = parentNode->GetWorldTransform().p;
	PxVec3 dir = parentPos - node->GetWorldTransform().p;
	dir.normalize();

	PxVec3 left = PxVec3(0,1,0).cross(dir);
	left.normalize();
	PxVec3 camPos = node->GetWorldTransform().p + (left*3.f) + PxVec3(0,2.5f,0);
	PxVec3 camDir = parentPos - camPos;
	camDir.normalize();
	camPos -= (camDir * .5f);

	m_sample.getCamera().lookAt(camPos, parentPos);
	const PxTransform viewTm = m_sample.getCamera().getViewMatrix();
	m_camera->init(viewTm);

	// select Orientation Control node
	if (CGenotypeNode *selectNode = m_rootNode->GetConnectNode(node->m_name))
	{
		selectNode->SetHighLight(true);
		SelectNode(selectNode);
	}
}