void CqParseTreeViz::Visit(IqParseNodeShader& node)
{
	setNodeProperty(node, "label", boost::format(
			"{%s shader \\\"%s\\\" | {<args> args | <code> code } }")
			% node.strShaderType() % node.strName());
	setNodeProperty(node, "fillcolor", functionColor);
	setNodeProperty(node, "shape", "record");
	IqParseNode* code = static_cast<IqParseNode*>(
			node.GetInterface(ParseNode_Base))->pChild();
	if(code)
	{
		IqParseNode* args = code->pNextSibling();
		if(args)
		{
			makeEdge(node, *args, "args");
			args->Accept(*this);
		}
		makeEdge(node, *code, "code");
		code->Accept(*this);
	}
}