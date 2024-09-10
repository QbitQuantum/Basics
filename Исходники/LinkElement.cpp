			LinkElement::LinkElement(const ref_ptr<Element>& parent) :
				Element(parent),
				state(LinkState::INACTIVE)
			{
				setRect(vector4f());
			}