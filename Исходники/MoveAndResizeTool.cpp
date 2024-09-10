void MoveAndResizeTool::continueDraw( int x, int y, DWORD flags ) {

	if ( currentElement_ && draggedBoundary_.bt!= btNone ) {
		POINT* elementBasePoint = 0;
		if ( draggedBoundary_.gpt == MovableElement::gptStartPoint ) {
			elementBasePoint = &currentElement_->startPoint_;
		} else if ( draggedBoundary_.gpt == MovableElement::gptEndPoint ) {
			elementBasePoint = &currentElement_->endPoint_;
		}
		int elWidth  = 0;
		int elHeight = 0;
		int elX = 0;
		int elY  = 0;
		if ( elementBasePoint ) {
			elementBasePoint->x = x;
			elementBasePoint->y = y;
			elWidth = currentElement_->getWidth();
			elHeight = currentElement_->getHeight();
			elX = currentElement_->getX();
			elY  = currentElement_->getY();
		} else {
			elWidth = currentElement_->getWidth();
			elHeight = currentElement_->getHeight();
			elX = currentElement_->getX();
			elY  = currentElement_->getY();
			switch ( draggedBoundary_.bt ) {
				case btBottomRight:
					elWidth = x - elX+1;
					elHeight = y - elY+1;
					break;
				case btBottom:
					elHeight = y - elY+1;
					break;
				case btRight:
					elWidth = x - elX+1;
					break;
				case btTopLeft:
					
					elWidth =  elX - x + elWidth;
					elHeight = elY - y + elHeight;
					elX = x;
					elY = y;
				case btLeft:
					
					elWidth = elX - x + elWidth;
					elX = x;
					break;
				case btTop:
					elHeight =  elY - y + elHeight;
					elY = y;
					break;
				case btBottomLeft:
					
					elWidth = elX - x + elWidth;
					elHeight = y - elY+1;
					elX = x;
					break;
				case btTopRight:
					
					elWidth =  x - elX+1;
					elHeight = elY - y + elHeight;
					elY = y;

					//currentElement_->setEndPoint()
			}
			//LOG(INFO) << "Resizing object to " << elX  << " "<< elY << " " << elWidth << " "<<elHeight;
			currentElement_->resize( elWidth,elHeight);
			currentElement_->setX(elX);
			currentElement_->setY(elY);
		}
		
		if ( currentElement_ && currentElement_->getType() == etCrop && canvas_->onCropChanged ) {
			canvas_->onCropChanged(currentElement_->getX(), currentElement_->getY(), currentElement_->getWidth(), currentElement_->getHeight());
		}
		RECT paintBoundingRect = currentElement_->getPaintBoundingRect();
		RECT updateRect;
		UnionRect(&updateRect, &paintBoundingRect, &prevPaintBoundingRect_);

		canvas_->updateView(updateRect);
		prevPaintBoundingRect_ = paintBoundingRect;

		return;
	}
	
	if ( isMoving_ && currentElement_ ) {
		int newX = currentElement_->getX() + x - startPoint_.x;
		int newY  = currentElement_->getY() + y - startPoint_.y;
		//LOG(INFO) << "Moving object to new position " << newX << " "<<newY;
		currentElement_->setX(newX);
		currentElement_->setY(newY);
		startPoint_.x = x;
		startPoint_.y = y;
		
		RECT paintBoundingRect = currentElement_->getPaintBoundingRect();
		RECT updateRect;
		UnionRect(&updateRect, &paintBoundingRect, &prevPaintBoundingRect_);
		canvas_->updateView(updateRect);
		if ( currentElement_ && currentElement_->getType() == etCrop && canvas_->onCropChanged ) {
			canvas_->onCropChanged(currentElement_->getX(), currentElement_->getY(), currentElement_->getWidth(), currentElement_->getHeight());
		}
		prevPaintBoundingRect_ = currentElement_->getPaintBoundingRect();

		return;
	}

	if ( currentElement_ ) {
		POINT pt = { x, y };
		currentElement_->setEndPoint( pt );
		/*if ( currentElement_ && currentElement_->getType() == etCrop && canvas_->onCropChanged ) {
			//LOG(INFO) << "onCropChanged";
			canvas_->onCropChanged(currentElement_->getX(), currentElement_->getY(), currentElement_->getWidth(), currentElement_->getHeight());
		}*/
		RECT paintBoundingRect = currentElement_->getPaintBoundingRect();
		RECT updateRect;
		UnionRect(&updateRect, &paintBoundingRect, &prevPaintBoundingRect_);
		
		canvas_->updateView(updateRect);
		prevPaintBoundingRect_ = currentElement_->getPaintBoundingRect();
	}
}