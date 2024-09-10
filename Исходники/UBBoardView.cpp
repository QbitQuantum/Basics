void
UBBoardView::setToolCursor (int tool)
{
  QWidget *controlViewport = viewport ();
  switch (tool)
    {
    case UBStylusTool::Pen:
      controlViewport->setCursor (UBResources::resources ()->penCursor);
      break;
    case UBStylusTool::Eraser:
      controlViewport->setCursor (UBResources::resources ()->eraserCursor);
      break;
    case UBStylusTool::Marker:
      controlViewport->setCursor (UBResources::resources ()->markerCursor);
      break;
    case UBStylusTool::Pointer:
      controlViewport->setCursor (UBResources::resources ()->pointerCursor);
      break;
    case UBStylusTool::Hand:
      controlViewport->setCursor (UBResources::resources ()->handCursor);
      break;
    case UBStylusTool::ZoomIn:
      controlViewport->setCursor (UBResources::resources ()->zoomInCursor);
      break;
    case UBStylusTool::ZoomOut:
      controlViewport->setCursor (UBResources::resources ()->zoomOutCursor);
      break;
    case UBStylusTool::Selector:
      controlViewport->setCursor (UBResources::resources ()->arrowCursor);
      break;
    case UBStylusTool::Line:
      controlViewport->setCursor (UBResources::resources ()->penCursor);
      break;
    case UBStylusTool::Text:
      controlViewport->setCursor (UBResources::resources ()->textCursor);
      break;
    case UBStylusTool::Capture:
      controlViewport->setCursor (UBResources::resources ()->penCursor);
      break;
    default:
      Q_ASSERT (false);
      //failsafe
      controlViewport->setCursor (UBResources::resources ()->penCursor);
    }
}