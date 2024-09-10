bool TouchController::isParentAllVisible(TouchControllerEvent* lsTe) {
	bool bRef = true;
	// 向父类转型，以便获取地址比较对象，TouchControllerEvent 的对象必须同时直接或者简介继承 CCNode
	Node* nLsTe = dynamic_cast<Node*>(lsTe);

	Node* parent = getParent();
	do {
		// 如果遍历完毕，说明 TouchController 不再 TouchControllerEvent 之内
		if (!parent) {
			bRef = false;
			break;
		}
		// 如果 TouchController 在 TouchControllerEvent 之内，返回 true
		// 注意：如果想让TouchControllerEvent 处理 不在其 CCNode 结构之内的元素，则取消此处判断
		if (nLsTe == parent) {
			break;
		}
		if (!parent->isVisible()) {
			bRef = false;
			break;
		}
		parent = parent->getParent();
	} while (1);
	return bRef;
}