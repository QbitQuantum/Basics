		virtual	void Visit( IqParseNode& node)
		{
			IqParseNode* child = static_cast<IqParseNode*>(
					node.GetInterface(ParseNode_Base))->pChild();
			while(child != NULL)
			{
				child->Accept(*this);
				child = child->pNextSibling();
			}
		}