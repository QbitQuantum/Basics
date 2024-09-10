void
SATGroup::_EnsureGroupIsOnScreen(SATGroup* group)
{
	STRACE_SAT("SATGroup::_EnsureGroupIsOnScreen\n");
	if (!group)
		return;

	if (group->CountItems() < 1)
		return;

	SATWindow* window = group->WindowAt(0);
	Desktop* desktop = window->GetWindow()->Desktop();
	if (!desktop)
		return;

	const float kBigDistance = 1E+10;

	float minLeftDistance = kBigDistance;
	BRect leftRect;
	float minTopDistance = kBigDistance;
	BRect topRect;
	float minRightDistance = kBigDistance;
	BRect rightRect;
	float minBottomDistance = kBigDistance;
	BRect bottomRect;

	BRect screen = window->GetWindow()->Screen()->Frame();
	BRect reducedScreen = screen;
	reducedScreen.InsetBy(kMinOverlap, kMinOverlap);

	for (int i = 0; i < group->CountItems(); i++) {
		SATWindow* window = group->WindowAt(i);
		BRect frame = window->CompleteWindowFrame();
		if (reducedScreen.Intersects(frame))
			return;

		if (frame.right < screen.left + kMinOverlap) {
			float dist = fabs(screen.left - frame.right);
			if (dist < minLeftDistance) {
				minLeftDistance = dist;
				leftRect = frame;
			}
			else if (dist == minLeftDistance)
				leftRect = leftRect | frame;
		}
		if (frame.top > screen.bottom - kMinOverlap) {
			float dist = fabs(frame.top - screen.bottom);
			if (dist < minBottomDistance) {
				minBottomDistance = dist;
				bottomRect = frame;
			}
			else if (dist == minBottomDistance)
				bottomRect = bottomRect | frame;
		}
		if (frame.left > screen.right - kMinOverlap) {
			float dist = fabs(frame.left - screen.right);
			if (dist < minRightDistance) {
				minRightDistance = dist;
				rightRect = frame;
			}
			else if (dist == minRightDistance)
				rightRect = rightRect | frame;
		}
		if (frame.bottom < screen.top + kMinOverlap) {
			float dist = fabs(frame.bottom - screen.top);
			if (dist < minTopDistance) {
				minTopDistance = dist;
				topRect = frame;
			}
			else if (dist == minTopDistance)
				topRect = topRect | frame;
		}
	}

	BPoint offset;
	if (minLeftDistance < kBigDistance) {
		offset.x = screen.left - leftRect.right + kMoveToScreen;
		_CallculateYOffset(offset, leftRect, screen);
	}
	else if (minTopDistance < kBigDistance) {
		offset.y = screen.top - topRect.bottom + kMoveToScreen;
		_CallculateXOffset(offset, topRect, screen);
	}
	else if (minRightDistance < kBigDistance) {
		offset.x = screen.right - rightRect.left - kMoveToScreen;
		_CallculateYOffset(offset, rightRect, screen);
	}
	else if (minBottomDistance < kBigDistance) {
		offset.y = screen.bottom - bottomRect.top - kMoveToScreen;
		_CallculateXOffset(offset, bottomRect, screen);
	}

	if (offset.x == 0. && offset.y == 0.)
		return;
	STRACE_SAT("move group back to screen: offset x: %f offset y: %f\n",
		offset.x, offset.y);

	desktop->MoveWindowBy(window->GetWindow(), offset.x, offset.y);
	window->DoGroupLayout();
}