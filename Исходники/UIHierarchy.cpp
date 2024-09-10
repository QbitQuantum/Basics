void UIHierarchy::DragInput(UIEvent *input)
{
    switch (input->phase)
    {
    case UIEvent::PHASE_BEGAN:
    {
        lockTouch = true;
        mainTouch = input->tid;

        if(InputSystem::Instance()->GetKeyboard()->IsKeyPressed(DVKEY_CTRL))
        {
            dragMode = DRAG_CHANGE_PARENT;
        }
        if(InputSystem::Instance()->GetKeyboard()->IsKeyPressed(DVKEY_SHIFT))
        {
            dragMode = DRAG_CHANGE_ORDER;
        }

        UIHierarchyCell *draggedCell = FindVisibleCellForPoint(input->point);
        if(draggedCell && draggedCell->GetNode())
        {
            draggedData = draggedCell->GetNode()->GetUserNode();
        }
        break;
    }
    case UIEvent::PHASE_DRAG:
    {
        if(cellUnderDrag)
        {
            cellUnderDrag->SetDebugDraw(false, false);
        }

        cellUnderDrag = FindVisibleCellForPoint(input->point);

        if(cellUnderDrag)
        {
            cellUnderDrag->SetDebugDraw(true, false);
        }

        Vector2 topOffset = input->point - GetPosition(true);
        Vector2 bottomOffset = input->point - (GetPosition(true) + GetSize());

        if(topOffset.y < 0)
        {
            float32 scrollPos = scroll->GetPosition();
            if(scrollPos < 0)
            {
                scroll->SetPosition(scrollPos - topOffset.y);
            }
        }
        else if(0 < bottomOffset.y)
        {
            float32 scrollPos = scroll->GetPosition();
            float32 viewSize = scroll->GetViewSize();
            float32 elementsSize = scroll->GetElementSize();

            if(scrollPos + viewSize < elementsSize)
            {
                float32 newPos = scrollPos - bottomOffset.y;
                newPos = Max(newPos, viewSize-elementsSize);

                scroll->SetPosition(newPos);
            }
        }
        break;
    }
    case UIEvent::PHASE_ENDED:
    {
        if(draggedData)
        {
            UIHierarchyCell *targetCell = FindVisibleCellForPoint(input->point);
            void *targetData = NULL;
            if(targetCell && targetCell->GetNode())
            {
                targetData = targetCell->GetNode()->GetUserNode();
            }

            if(delegate && (draggedData != targetData))
            {
                delegate->DragAndDrop(draggedData, targetData, dragMode);
            }
        }
        //break; not needed!
    }
    case UIEvent::PHASE_CANCELLED:
    {
        lockTouch = false;
        mainTouch = 0;

        dragMode = DRAG_NONE;

        if(cellUnderDrag)
        {
            cellUnderDrag->SetDebugDraw(false, false);
            cellUnderDrag = NULL;
        }

        draggedData = NULL;

        break;
    }

    default:
    {
        break;
    }
    }
}