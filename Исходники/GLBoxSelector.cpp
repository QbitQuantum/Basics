void GLBoxSelector::processMouse(QMouseEvent *me)
{
#define GRAB_POS_INVALID() (grabPos.x < 0.0f)
#define GRAB_POS_INVALIDATE() (grabPos.x = grabPos.y = -1.f)
	const bool leftButIsDown = me->buttons()&Qt::LeftButton;
	const float thresh = wc2gl(Vec2i(10,viewport.v4)).magnitude();
	Vec2f c1(box.x,box.y), c2(box.v3,box.y), c3(box.v3,box.v4), c4(box.x,box.v4);
	Vec2f pos = wc2gl(Vec2i(me->x(),me->y()));
	const bool movingBox = leftButIsDown && !GRAB_POS_INVALID() && glw->cursor().shape() == Qt::ClosedHandCursor;
	if (!leftButIsDown) GRAB_POS_INVALIDATE(), grabCorners = 0;
	glw->unsetCursor();
	if (!movingBox && !grabCorners) {
		if (pos.distance(c2) <= thresh) // bottom right
			glw->setCursor(Qt::SizeFDiagCursor), grabCorners = 1<<2;
		else if (pos.distance(c4) <= thresh) // top left 
			glw->setCursor(Qt::SizeFDiagCursor), grabCorners = 1<<4; 
		else if (pos.distance(c1) <= thresh) // bottom left
			glw->setCursor(Qt::SizeBDiagCursor), grabCorners = 1<<1;
		else if (pos.distance(c3) <= thresh) // top right corner
			glw->setCursor(Qt::SizeBDiagCursor), grabCorners = 1<<3;
		else if (pos.x >= c1.x && pos.x <= c2.x) {
			if (fabsf(pos.y-c1.y) <= thresh) // bottom side of box
				glw->setCursor(Qt::SizeVerCursor), grabCorners = (1<<1)|(1<<2);
			else if (fabsf(pos.y-c3.y) <= thresh)  // top side of box
				glw->setCursor(Qt::SizeVerCursor), grabCorners = (1<<3)|(1<<4);
		}
		if (!grabCorners && pos.y >= c1.y && pos.y <= c3.y) {
			if (fabsf(pos.x-c1.x) <= thresh)  // left side of box
				glw->setCursor(Qt::SizeHorCursor), grabCorners = (1<<1)|(1<<4);
			else if (fabsf(pos.x-c3.x) <= thresh) // right side of box
				glw->setCursor(Qt::SizeHorCursor), grabCorners = (1<<2)|(1<<3);
		} 
		if (!grabCorners && !(pos.x <= c1.x) && !(pos.x >= c3.x) && !(pos.y <= c1.y) && !(pos.y >= c3.y)) {
			glw->setCursor(leftButIsDown ? Qt::ClosedHandCursor : Qt::OpenHandCursor);
			if (leftButIsDown) grabPos = pos;
		}
		if (!leftButIsDown) grabCorners = 0;
	} else if (movingBox && !grabCorners) { // movingBox!
		glw->setCursor(Qt::ClosedHandCursor);
		if (leftButIsDown && !GRAB_POS_INVALID()) {
			Vec2f movvec = pos-grabPos;
			grabPos = grabPos + movvec;
			box.v1 += movvec.x;
			box.v2 += movvec.y;
			box.v3 += movvec.x;
			box.v4 += movvec.y;
		}
		if(box.v1 < 0.f) box.v3 += -box.v1, box.v1=0.f;
		else if (box.v3 > 1.f) box.v1 -= box.v3-1.f, box.v3 = 1.f;
		else if (box.v2 < 0.f) box.v4 += -box.v2, box.v2 = 0.f;
		else if (box.v4 > 1.f) box.v2 -= box.v4-1.f, box.v4 = 1.f;
	} else if (!movingBox && grabCorners) {
		const bool movc1 = (grabCorners&(1<<1)), movc2 = (grabCorners&(1<<2)),	 movc3 = (grabCorners&(1<<3)), movc4 = (grabCorners&(1<<4));
		if (movc1 && movc2) {
			// dragging bottom side of box
			glw->setCursor(Qt::SizeVerCursor);
			c1.y = c2.y = pos.y;
			if (c1.y > 1.f) c1.y = c2.y = 1.f;
			if (c1.y < 0.f) c1.y = c2.y = 0.f;
			if (c1.y >= c3.y) grabCorners = (1<<3)|(1<<4);
		} else if (movc4 && movc3) { // top line of box is dragging
			glw->setCursor(Qt::SizeVerCursor);
			c4.y = c3.y = pos.y;
			if (c4.y > 1.f) c4.y = c3.y = 1.f;
			if (c4.y < 0.f) c4.y = c3.y = 0.f;					
			if (c4.y <= c1.y) grabCorners = (1<<1)|(1<<2);
		} else if (movc2 && movc3) { // right side of box is dragging
			glw->setCursor(Qt::SizeHorCursor);
			c2.x = c3.x = pos.x;
			if (c3.x > 1.f) c3.x = c2.x = 1.f;
			if (c3.x < 0.f) c3.x = c2.x = 0.f;
			if (c3.x <= c1.x) grabCorners = (1<<1)|(1<<4);
		} else if (movc1 && movc4) { // left side of box is dragging
			glw->setCursor(Qt::SizeHorCursor);
			c1.x = c4.x = pos.x;
			if (c1.x > 1.f) c1.x = c4.x = 1.f;
			if (c1.x < 0.f) c1.x = c4.x = 0.f;
			if (c1.x >= c2.x) grabCorners = (1<<2)|(1<<3);
		} else if (movc1) {
			glw->setCursor(Qt::SizeBDiagCursor);
			c1 = pos;
			if (c1.x < 0) c1.x = 0;
			if (c1.y < 0) c1.y = 0;
			if (c1.x > 1.f) c1.x = 1.f;
			if (c1.y > 1.f) c1.y = 1.f;
			c4.x = c1.x;
			c2.y = c1.y;
			if (c1.x >= c3.x && c1.y >= c3.y) grabCorners = (1<<3);
			else if (c1.x >= c2.x) grabCorners = (1<<2);
			else if (c1.y >= c4.y) grabCorners = (1<<4);
		} else if (movc3) {
			glw->setCursor(Qt::SizeBDiagCursor);
			c3 = pos;
			if (c3.x < 0) c3.x = 0;
			if (c3.y < 0) c3.y = 0;
			if (c3.x > 1.f) c3.x = 1.f;
			if (c3.y > 1.f) c3.y = 1.f;
			c4.y = c3.y;
			c2.x = c3.x;
			if (c1.x >= c3.x && c1.y >= c3.y) grabCorners = (1<<1);
			else if (c3.x <= c4.x) grabCorners = (1<<4);
			else if (c3.y <= c2.y) grabCorners = (1<<2);
		} else if (movc2) {
			glw->setCursor(Qt::SizeFDiagCursor);
			c2 = pos;
			if (c2.x < 0) c2.x = 0;
			if (c2.y < 0) c2.y = 0;
			if (c2.x > 1.f) c2.x = 1.f;
			if (c2.y > 1.f) c2.y = 1.f;
			c1.y = c2.y;
			c3.x = c2.x;
			if (c2.x >= c4.x && c2.y >= c4.y) grabCorners = (1<<4);
			else if (c1.x >= c2.x) grabCorners = (1<<1);
			else if (c3.y <= c2.y) grabCorners = (1<<3);
		} else if (movc4) {
			glw->setCursor(Qt::SizeFDiagCursor);
			c4 = pos;
			if (c4.x < 0) c4.x = 0;
			if (c4.y < 0) c4.y = 0;
			if (c4.x > 1.f) c4.x = 1.f;
			if (c4.y > 1.f) c4.y = 1.f;
			c1.x = c4.x;
			c3.y = c4.y;
			if (c2.x >= c4.x && c2.y >= c4.y) grabCorners = (1<<2);
			else if (c3.x <= c4.x) grabCorners = (1<<3);
			else if (c1.y >= c4.y) grabCorners = (1<<1);
		}
		box = Vec4f ( MIN(MIN(c1.x,c2.x),MIN(c3.x,c4.x)),
					 MIN(MIN(c1.y,c2.y),MIN(c3.y,c4.y)),
					 MAX(MAX(c1.x,c2.x),MAX(c3.x,c4.x)),
					 MAX(MAX(c1.y,c2.y),MAX(c3.y,c4.y)) );
	}
	chkBoxSanity();
}