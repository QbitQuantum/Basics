// DragTo
void
DragCornerState::DragTo(BPoint current, uint32 modifiers)
{
	BRect oldBox = fParent->Box();
	if (oldBox.Width() == 0.0 || oldBox.Height() == 0.0)
		return;

	// TODO: some of this can be combined into less steps
	BRect newBox = oldBox;

	fOldTransform.InverseTransform(&current);
	
	switch (fCorner) {
		case LEFT_TOP_CORNER:
			newBox.left = current.x - fOffsetFromCorner.x;
			newBox.top = current.y - fOffsetFromCorner.y;
			break;
		case RIGHT_TOP_CORNER:
			newBox.right = current.x - fOffsetFromCorner.x;
			newBox.top = current.y - fOffsetFromCorner.y;
			break;
		case LEFT_BOTTOM_CORNER:
			newBox.left = current.x - fOffsetFromCorner.x;
			newBox.bottom = current.y - fOffsetFromCorner.y;
			break;
		case RIGHT_BOTTOM_CORNER:
			newBox.right = current.x - fOffsetFromCorner.x;
			newBox.bottom = current.y - fOffsetFromCorner.y;
			break;
	}

	if (!(modifiers & B_SHIFT_KEY)) {
		// keep the x and y scale the same
		double xScale = newBox.Width() / oldBox.Width();
		double yScale = newBox.Height() / oldBox.Height();
	
		if (modifiers & B_COMMAND_KEY) {
			xScale = snap_scale(xScale);
			yScale = snap_scale(yScale);
		}

		if (fabs(xScale) > fabs(yScale))
			yScale = yScale > 0.0 ? fabs(xScale) : -fabs(xScale);
		else
			xScale = xScale > 0.0 ? fabs(yScale) : -fabs(yScale);

		switch (fCorner) {
			case LEFT_TOP_CORNER:
				newBox.left = oldBox.right - oldBox.Width() * xScale;
				newBox.top = oldBox.bottom - oldBox.Height() * yScale;
				break;
			case RIGHT_TOP_CORNER:
				newBox.right = oldBox.left + oldBox.Width() * xScale;
				newBox.top = oldBox.bottom - oldBox.Height() * yScale;
				break;
			case LEFT_BOTTOM_CORNER:
				newBox.left = oldBox.right - oldBox.Width() * xScale;
				newBox.bottom = oldBox.top + oldBox.Height() * yScale;
				break;
			case RIGHT_BOTTOM_CORNER:
				newBox.right = oldBox.left + oldBox.Width() * xScale;
				newBox.bottom = oldBox.top + oldBox.Height() * yScale;
				break;
		}
	}

	// build a matrix that performs just the
	// distortion of the box with the opposite
	// corner of the one being dragged staying fixed
	AffineTransform s;
	s.rect_to_rect(oldBox.left, oldBox.top, oldBox.right, oldBox.bottom,
				   newBox.left, newBox.top, newBox.right, newBox.bottom);

	// construct a transformation that
	// * excludes the effect of the fParant->Pivot()
	// * includes the effect of the changed scaling and translation
	AffineTransform t;
	BPoint pivot(fParent->Pivot());
	t.TranslateBy(pivot.x, pivot.y);
	t.Multiply(s);
		// at this point, the matrix is
		// similar/compatible to the original
		// matrix (fOldTransform), and also
		// contains the pivot
	t.Multiply(fOldTransform);
		// here both matrices are "merged"
		// -> in effect this means that the
		// scale and the translation to
		// keep the object fixed at the corner
		// opposite to the one being dragged
		// were transfered to the parent matrix
	t.TranslateBy(-pivot.x, -pivot.y);
		// and now the pivot is removed
		// (see AdvancedTransform::_UpdateMatrix()
		// for how the pivot is applied)

	// get the translation
	double translationX;
	double translationY;
	t.translation(&translationX, &translationY);

	// get the scale
	double newScaleX;
	double newScaleY;
	t.scaling(&newScaleX, &newScaleY);

	// operating on just the affine parameters is much more precise
	fParent->SetTranslationAndScale(BPoint(translationX, translationY),
		newScaleX, newScaleY);
}