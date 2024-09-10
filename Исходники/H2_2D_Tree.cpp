//	Obtains interpolation operator, which interpolates information from Chebyshev nodes of parent to Chebyshev nodes of children;
void H2_2D_Tree::get_Transfer_From_Parent_CNode_To_Children_CNode(const unsigned short nChebNodes, const VectorXd& cNode, const MatrixXd& TNode, MatrixXd& Transfer){
	VectorXd childcNode(2*nChebNodes);
	childcNode.segment(0,nChebNodes)		=	0.5*(cNode-VectorXd::Ones(nChebNodes));
	childcNode.segment(nChebNodes,nChebNodes)	=	0.5*(cNode+VectorXd::Ones(nChebNodes));
	get_Standard_Chebyshev_Polynomials(nChebNodes, 2*nChebNodes, childcNode, Transfer);
	Transfer	=	(2.0*Transfer*TNode.transpose()-MatrixXd::Ones(2*nChebNodes,nChebNodes))/nChebNodes;
}