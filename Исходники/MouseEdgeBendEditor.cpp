//========================================================================================
bool MouseEdgeBendEditor::eventFilter(QObject *widget, QEvent *e) {

  QMouseEvent * qMouseEv = (QMouseEvent *) e;

  if(qMouseEv == NULL)
    return false;

  // Double click to create a new control point
  if(e->type() == QEvent::MouseButtonDblClick &&  qMouseEv->button() == Qt::LeftButton && haveSelection(glMainWidget)) {
    _operation = NEW_OP;
    mMouseCreate(qMouseEv->x(), qMouseEv->y(), glMainWidget);
    return true;
  }

  if (e->type() == QEvent::MouseButtonPress) {
    if(!glMainWidget)
      glMainWidget = (GlMainWidget *) widget;

    initProxies(glMainWidget);
    bool hasSelection = haveSelection(glMainWidget);

    editPosition[0] = qMouseEv->x();
    editPosition[1] = qMouseEv->y();
    editPosition[2] = 0;

    switch(qMouseEv->buttons()) {
    case Qt::LeftButton : {

      if (!hasSelection) {
        // event occurs outside the selection rectangle
        // so from now we delegate the job to a MouseEdgeSelector object
        // which should intercept the event
        _operation = NONE_OP;
      }
      else {

        bool entityIsSelected = glMainWidget->pickGlEntities((int)editPosition[0] - 3, (int)editPosition[1] - 3, 6, 6, select, layer);

        if(!entityIsSelected) {
          // We have click outside an entity
          _operation = NONE_OP;
        }
        else {
          selectedEntity=circleString->findKey(select[0].getSimpleEntity());

          if (qMouseEv->modifiers() &
#if defined(__APPLE__)
              Qt::AltModifier
#else
              Qt::ControlModifier
#endif
             ) {
            _operation = DELETE_OP;
            mMouseDelete();
          }
          else {
            _graph->push();
            _operation = TRANSLATE_OP;
            glMainWidget->setCursor(QCursor(Qt::SizeAllCursor));
            mode = COORD;
          }

          return true;
        }
      }

      break;
    }

    default: {
      return false;
    }
    }

    glMainWidget->redraw();
  }

  if (e->type() == QEvent::MouseButtonRelease &&
      qMouseEv->button() == Qt::LeftButton &&
      _operation != NONE_OP) {
    GlMainWidget *glMainWidget = (GlMainWidget *) widget;

    if(selectedEntity=="targetTriangle") {
      SelectedEntity selectedEntity;

      if (glMainWidget->pickNodesEdges(qMouseEv->x(), qMouseEv->y(), selectedEntity) && selectedEntity.getEntityType() == SelectedEntity::NODE_SELECTED) {
        glMainWidget->getScene()->getGlGraphComposite()->getGraph()->setEnds(mEdge,glMainWidget->getScene()->getGlGraphComposite()->getGraph()->ends(mEdge).first,node(selectedEntity.getComplexEntityId()));
      }
    }
    else if(selectedEntity=="sourceCircle") {
      SelectedEntity selectedEntity;

      if (glMainWidget->pickNodesEdges(qMouseEv->x(), qMouseEv->y(), selectedEntity) && selectedEntity.getEntityType() == SelectedEntity::NODE_SELECTED) {
        glMainWidget->getScene()->getGlGraphComposite()->getGraph()->setEnds(mEdge,node(selectedEntity.getComplexEntityId()),glMainWidget->getScene()->getGlGraphComposite()->getGraph()->ends(mEdge).second);
      }
    }

    selectedEntity="";

    _operation = NONE_OP;
    glMainWidget->setCursor(QCursor(Qt::PointingHandCursor));
    glMainWidget->redraw();
    return true;
  }

  if(e->type() == QEvent::MouseButtonPress) {
    vector<SelectedEntity> selectedEntities;
    glMainWidget->pickGlEntities(qMouseEv->x(), qMouseEv->y(), selectedEntities);

    if(!selectedEntities.empty())
      if(selectedEntities[0].getEntityType()==SelectedEntity::SIMPLE_ENTITY_SELECTED)
        if(selectedEntities[0].getSimpleEntity()==edgeEntity) {
          mouseButtonPressOnEdge=true;
          return true;
        }
  }

  if(e->type() == QEvent::MouseButtonRelease) {
    vector<SelectedEntity> selectedEntities;
    glMainWidget->pickGlEntities(qMouseEv->x(), qMouseEv->y(), selectedEntities);

    if(!selectedEntities.empty())
      if(selectedEntities[0].getEntityType()==SelectedEntity::SIMPLE_ENTITY_SELECTED)
        if(selectedEntities[0].getSimpleEntity()==edgeEntity && mouseButtonPressOnEdge) {
          mouseButtonPressOnEdge=false;
          return true;
        }

    mouseButtonPressOnEdge=false;
  }

  if  (e->type() == QEvent::MouseMove) {
    if(qMouseEv->buttons() == Qt::LeftButton &&
        _operation != NONE_OP) {
      GlMainWidget *glMainWidget = (GlMainWidget *) widget;

      switch (_operation) {
      case TRANSLATE_OP:
        mMouseTranslate(qMouseEv->x(), qMouseEv->y(), glMainWidget);
        return true;

      default:
        return false;
      }
    }
    else if(qMouseEv->buttons() == Qt::NoButton) {
      SelectedEntity selectedEntity;
      GlMainWidget *g = (GlMainWidget *) widget;

      if (g->pickNodesEdges(qMouseEv->x(), qMouseEv->y(), selectedEntity) && selectedEntity.getEntityType() == SelectedEntity::NODE_SELECTED) {
        g->setCursor(Qt::CrossCursor);
      }
      else {
        g->setCursor(Qt::ArrowCursor);
      }

      return false;
    }
  }

  return false;
}