void HTMLEnhancer::postEnhanceNode(DOM::Node domNode)
{
	DOM::Node textNode;
	kNodeAttrs *props;
	QTag *qTag;
	bool isInline;

	if(domNode.isNull())
		return;

	//If domNode is a Block and there is no text around, and if domNode's parent can handle
	//text or a P tag, add an empty text DOM::Node
	// so that the user can access this area.
	qTag = QuantaCommon::tagFromDTD(m_wkafkapart->getCurrentDoc()->defaultDTD(),
		domNode.nodeName().string());
	isInline = kafkaCommon::isInline(domNode.nodeName().string());
	if(domNode.nodeType() == DOM::Node::ELEMENT_NODE &&
		(!isInline || (isInline && qTag && qTag->isSingle())))
	{
		qTag = QuantaCommon::tagFromDTD(m_wkafkapart->getNode(domNode.parentNode()));

		if((domNode.nextSibling().isNull() ||
			(!domNode.nextSibling().isNull() &&
			domNode.nextSibling().nodeType() == DOM::Node::ELEMENT_NODE &&
			!kafkaCommon::isInline(domNode.nextSibling().nodeName().string())))
			&& qTag && (qTag->isChild("#text", false) || qTag->isChild("p", false)) &&
			domNode.nodeName().string().lower() != "p")
		{
			textNode = kafkaCommon::createTextDomNode("",
				m_wkafkapart->getKafkaWidget()->document());
			props = m_wkafkapart->connectDomNodeToQuantaNode(textNode, 0L);
			props->setIsLinkedToNode(false);
			props->setSpecialBehavior(kNodeAttrs::emptyTextSurroundingBlockElementAtTheRight);
			kafkaCommon::insertDomNode(textNode, domNode.parentNode(),
				domNode.nextSibling());
		}

		if((domNode.previousSibling().isNull() || (!domNode.previousSibling().isNull() &&
			domNode.previousSibling().nodeType() == DOM::Node::ELEMENT_NODE &&
			!kafkaCommon::isInline(domNode.previousSibling().nodeName().string())))
			&& qTag && (qTag->isChild("#text", false) || qTag->isChild("p", false)) &&
			domNode.nodeName().string().lower() != "p")
		{
			textNode = kafkaCommon::createTextDomNode("",
				m_wkafkapart->getKafkaWidget()->document());
			props = m_wkafkapart->connectDomNodeToQuantaNode(textNode, 0L);
			props->setIsLinkedToNode(false);
			props->setSpecialBehavior(kNodeAttrs::emptyTextSurroundingBlockElementAtTheLeft);
			kafkaCommon::insertDomNode(textNode, domNode.parentNode(),
				domNode);
		}
	}

	//If domNode is an childless element, and if it can handle Text or a P tag,
	//add an empty text DOM::Node so that the
	//user can access this area.
	qTag = QuantaCommon::tagFromDTD(m_wkafkapart->getNode(domNode));
	if(domNode.nodeType() == DOM::Node::ELEMENT_NODE &&
		!domNode.hasChildNodes() && qTag && (qTag->isChild("#text", false) ||
		qTag->isChild("p", false)))
	{
		textNode = kafkaCommon::createTextDomNode("",
			m_wkafkapart->getKafkaWidget()->document());
		props = m_wkafkapart->connectDomNodeToQuantaNode(textNode, 0L);
		props->setIsLinkedToNode(false);
		props->setSpecialBehavior(kNodeAttrs::emptyTextAsChildOfAChildlessElement);
		kafkaCommon::insertDomNode(textNode, domNode);
	}
}