void
InsertionIntoEmptyArea::MaximizeEmptyArea(area_ref& ref, BRect target, BRect ignore)
{
	BALMLayout* layout = fView->Layout();
	BRegion takenSpace = fView->fTakenSpace;
	takenSpace.Exclude(ignore);
	area_info areaInfo(ref, layout);
	// try to match the target

	XTab* left = ref.left;
	while (left->Value() > target.left) {
		left = layout->XTabAt(areaInfo.left - 1, true);
		if (left == NULL)
			break;
		area_ref newRef = ref;
		newRef.left = left;
		BRect frame = newRef.Frame();
		frame.InsetBy(1, 1);
		if (takenSpace.Intersects(frame))
			break;
		areaInfo.left -= 1;
		ref.left = left;
	}
	XTab* right = ref.right;
	while (right->Value() < target.right) {
		right = layout->XTabAt(areaInfo.right + 1, true);
		if (right == NULL)
			break;
		area_ref newRef = ref;
		newRef.right = right;
		BRect frame = newRef.Frame();
		frame.InsetBy(1, 1);
		if (takenSpace.Intersects(frame))
			break;
		areaInfo.right += 1;
		ref.right = right;
	}
	YTab* top = ref.top;
	while (top->Value() > target.top) {
		top = layout->YTabAt(areaInfo.top - 1, true);
		if (top == NULL)
			break;
		area_ref newRef = ref;
		newRef.top = top;
		BRect frame = newRef.Frame();
		frame.InsetBy(1, 1);
		if (takenSpace.Intersects(frame))
			break;
		areaInfo.top -= 1;
		ref.top = top;
	}
	YTab* bottom = ref.bottom;
	while (bottom->Value() < target.bottom) {
		bottom = layout->YTabAt(areaInfo.bottom + 1, true);
		if (bottom == NULL)
			break;
		area_ref newRef = ref;
		newRef.bottom = bottom;
		BRect frame = newRef.Frame();
		frame.InsetBy(1, 1);
		if (takenSpace.Intersects(frame))
			break;
		areaInfo.bottom += 1;
		ref.bottom = bottom;
	}

	// maximize further
	while (true) {
		BRect previousFrame = ref.Frame();
		
		left = layout->XTabAt(areaInfo.left - 1, true);
		right = layout->XTabAt(areaInfo.right + 1, true);
		top = layout->YTabAt(areaInfo.top - 1, true);
		bottom = layout->YTabAt(areaInfo.bottom + 1, true);

		float leftDelta = -1;
		if (left != NULL) {
			BRect newFrame(previousFrame);
			newFrame.left = left->Value();
			newFrame.InsetBy(1, 1);
			if (!takenSpace.Intersects(newFrame)) {
				leftDelta = previousFrame.Height()
					* (previousFrame.left - left->Value());
			}
		}
		float rightDelta = -1;
		if (right != NULL) {
			BRect newFrame(previousFrame);
			newFrame.right = right->Value();
			newFrame.InsetBy(1, 1);
			if (!takenSpace.Intersects(newFrame)) {
				rightDelta = previousFrame.Height()
					* (right->Value() - previousFrame.right);
			}
		}
		float topDelta = -1;
		if (top != NULL) {
			BRect newFrame(previousFrame);
			newFrame.top = top->Value();
			newFrame.InsetBy(1, 1);
			if (!takenSpace.Intersects(newFrame)) {
				topDelta = previousFrame.Width()
					* (previousFrame.top - top->Value());
			}
		}
		float bottomDelta = -1;
		if (bottom != NULL) {
			BRect newFrame(previousFrame);
			newFrame.bottom = bottom->Value();
			newFrame.InsetBy(1, 1);
			if (!takenSpace.Intersects(newFrame)) {
				bottomDelta = previousFrame.Width()
					* (bottom->Value() - previousFrame.bottom);
			}
		}
		if (leftDelta > 0 && leftDelta > rightDelta && leftDelta > topDelta
			&& leftDelta > bottomDelta) {
			ref.left = left;
			areaInfo.left = layout->IndexOf(left, true);
		} else if (rightDelta > 0 && rightDelta > topDelta
			&& rightDelta > bottomDelta) {
			ref.right = right;
			areaInfo.right = layout->IndexOf(right, true);
		} else if (topDelta > 0 && topDelta > bottomDelta) {
			ref.top = top;
			areaInfo.top = layout->IndexOf(top, true);
		} else if (bottomDelta > 0) {
			ref.bottom = bottom;
			areaInfo.bottom = layout->IndexOf(bottom, true);
		}

		BRect newFrame = ref.Frame();
		if (fuzzy_equal(previousFrame.Width(), newFrame.Width())
			&& fuzzy_equal(previousFrame.Height(), newFrame.Height()))
			break;
	}
}