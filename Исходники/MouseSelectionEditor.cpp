//========================================================================================
bool MouseSelectionEditor::eventFilter(QObject *widget, QEvent *e) {
  QMouseEvent *qMouseEv = static_cast<QMouseEvent *>(e);
  GlMainWidget *glMainWidget = static_cast<GlMainWidget *>(widget);

  if (e->type() == QEvent::MouseButtonPress) {

    initProxies(glMainWidget);
    computeFFD(glMainWidget);

    int H;
    H = glMainWidget->height();
    editCenter = centerRect.getCenter();
    editCenter[2] = 0;
    editCenter[1] = glMainWidget->screenToViewport(H) - editCenter[1];
    // editCenter[0] = W - editCenter[0];
    editPosition[0] = qMouseEv->x();
    editPosition[1] = qMouseEv->y();
    editPosition[2] = 0;
    editLayoutCenter = _layoutCenter;

    vector<SelectedEntity> select;

    switch (qMouseEv->buttons()) {
    case Qt::LeftButton: {
      // first ensure that something is selected
      bool hasSelection = _selection->hasNonDefaultValuatedNodes(_graph) ||
                          _selection->hasNonDefaultValuatedEdges(_graph);

      if (!hasSelection ||
          (!glMainWidget->pickGlEntities(int(editPosition[0]) - 3, int(editPosition[1]) - 3, 6, 6,
                                         select, layer))) {
        // event occurs outside the selection rectangle
        // so from now we delegate the job to a MouseSelector object
        // which should intercept the event
        operation = NONE;
        glMainWidget->setCursor(QCursor(Qt::CrossCursor));

        return false;
      }

      glMainWidget->setCursor(QCursor(Qt::PointingHandCursor));

      int shapeId = -1;
      bool advShape = false;

      for (unsigned int i = 0; (i < select.size()) && (shapeId == -1); ++i) {
        for (int j = 0; j < 8; ++j) {
          if (select[i].getSimpleEntity() == &_controls[j]) {
            shapeId = i;
          }
        }

        for (int j = 0; j < 6; ++j) {
          if (select[i].getSimpleEntity() == &_advControls[j]) {
            advShape = true;
            shapeId = i;
          }
        }
      }

      if (shapeId != -1) {
        if (!advShape) {
          static_cast<GlCircle *>(select[shapeId].getSimpleEntity())
              ->setFillColor(Color(40, 255, 40, 200));
          static_cast<GlCircle *>(select[shapeId].getSimpleEntity())
              ->setOutlineColor(Color(20, 128, 20, 200));
        }

        getOperation(select[shapeId].getSimpleEntity());

        switch (operation) {
        case ALIGN_TOP:
        case ALIGN_BOTTOM:
        case ALIGN_LEFT:
        case ALIGN_RIGHT:
        case ALIGN_VERTICALLY:
        case ALIGN_HORIZONTALLY:
          mAlign(operation, glMainWidget);
          return true;

        case ROTATE_Z:
        case ROTATE_XY:
        case NONE:
        case STRETCH_X:
        case STRETCH_Y:
        case STRETCH_XY:
        case TRANSLATE:
        default:
          break;
        }
      } else {
        if (qMouseEv->modifiers() &
#if defined(__APPLE__)
            Qt::AltModifier
#else
            Qt::ControlModifier
#endif
        ) {
          operation = ROTATE_XY;
          glMainWidget->setCursor(QCursor(Qt::PointingHandCursor));
        } else {
          operation = TRANSLATE;
          glMainWidget->setCursor(QCursor(Qt::SizeAllCursor));
        }
      }

      mode = COORD_AND_SIZE;

      if (qMouseEv->modifiers() & Qt::ShiftModifier)
        mode = COORD;

      if (qMouseEv->modifiers() &
#if defined(__APPLE__)
          Qt::AltModifier
#else
          Qt::ControlModifier
#endif
      )
        mode = SIZE;

      initEdition();
      break;
    }

    case Qt::MidButton:
      undoEdition();
      glMainWidget->setCursor(QCursor(Qt::ArrowCursor));
      break;

    default:
      return false;
    }

    glMainWidget->redraw();
    return true;
  }

  if (e->type() == QEvent::MouseButtonRelease && qMouseEv->button() == Qt::LeftButton &&
      operation != NONE) {
    stopEdition();

    // restore colors
    for (unsigned int i = 0; i < 8; ++i) {
      _controls[i].setFillColor(Color(255, 40, 40, 200));
      _controls[i].setOutlineColor(Color(128, 20, 20, 200));
    }

    glMainWidget->setCursor(QCursor(Qt::ArrowCursor));
    glMainWidget->draw();
    return true;
  }

  if (e->type() == QEvent::KeyPress) {
    // first ensure that something is selected
    bool hasSelection = _selection->hasNonDefaultValuatedNodes(_graph) ||
                        _selection->hasNonDefaultValuatedEdges(_graph);

    if (hasSelection) {
      switch (static_cast<QKeyEvent *>(e)->key()) {
      case Qt::Key_Left:
        mMouseTranslate(editPosition[0] - 1, editPosition[1], glMainWidget);
        break;

      case Qt::Key_Right:
        mMouseTranslate(editPosition[0] + 1, editPosition[1], glMainWidget);
        break;

      case Qt::Key_Up:
        mMouseTranslate(editPosition[0], editPosition[1] - 1, glMainWidget);
        break;

      case Qt::Key_Down:
        mMouseTranslate(editPosition[0], editPosition[1] + 1, glMainWidget);
        break;
      }
    }
  }

  if (e->type() == QEvent::MouseMove && qMouseEv->buttons() & Qt::LeftButton && operation != NONE) {
    int newX = qMouseEv->x();
    int newY = qMouseEv->y();

    switch (operation) {
    case STRETCH_X:
    case STRETCH_Y:
    case STRETCH_XY:
      mMouseStretchAxis(newX, newY, glMainWidget);
      return true;

    case ROTATE_Z:
    case ROTATE_XY:
      mMouseRotate(newX, newY, glMainWidget);
      return true;

    case TRANSLATE:
      mMouseTranslate(newX, newY, glMainWidget);
      return true;

    case NONE:
    case ALIGN_TOP:
    case ALIGN_BOTTOM:
    case ALIGN_LEFT:
    case ALIGN_RIGHT:
    case ALIGN_VERTICALLY:
    case ALIGN_HORIZONTALLY:
    default:
      qWarning() << "[Error] : " << __FUNCTION__ << " should not have been called" << endl;
      break;
    }
  }

  return false;
}