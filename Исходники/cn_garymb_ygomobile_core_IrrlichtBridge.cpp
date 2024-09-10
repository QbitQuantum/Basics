 */JNIEXPORT void JNICALL Java_cn_garymb_ygomobile_core_IrrlichtBridge_nativeSetCheckBoxesSelection(
		JNIEnv* env, jclass clazz, jint handle, jint idx) {
	if (handle) {
		IrrlichtDevice* device = (IrrlichtDevice*) handle;
		IGUIEnvironment* irrenv = device->getGUIEnvironment();
		IGUIElement* element = irrenv->getFocus();
		if (element) {
			IGUIWindow* window = (IGUIWindow*) (element);
			core::list<IGUIElement*> children = window->getChildren();
			core::list<IGUIElement*>::Iterator current = children.begin();
			int i = 0;
			do {
				if ((*current)->getType() == EGUIET_CHECK_BOX && i++ == idx) {
					break;
				}
				current++;
			} while (current != children.end());
			if (current == children.end()) {
				return;
			}
			IGUICheckBox* checkbox = (IGUICheckBox*) *current;
			checkbox->setChecked(true);
			SEvent e;
			e.EventType = EET_GUI_EVENT;
			e.GUIEvent.Caller = checkbox;
			e.GUIEvent.Element = 0;
			e.GUIEvent.EventType = EGET_CHECKBOX_CHANGED;
			window->OnEvent(e);
			irrenv->setFocus(window);
		}
	}
}