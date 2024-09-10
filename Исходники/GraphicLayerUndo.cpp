void GroupUngroupGraphicObjects::ungroup()
{
   GraphicLayer* pLayer = dynamic_cast<GraphicLayer*>(getSessionItem());
   if ((pLayer != NULL) && (mGroupId.empty() == false))
   {
      string viewId;

      View* pView = pLayer->getView();
      if (pView != NULL)
      {
         viewId = pView->getId();
      }

      GraphicGroup* pGroup = dynamic_cast<GraphicGroup*>(GraphicUndoUtilities::getObject(viewId,
         pLayer->getId(), mGroupId));
      if (pGroup != NULL)
      {
         list<GraphicObject*> selectedObjects;
         pLayer->getSelectedObjects(selectedObjects);

         pLayer->deselectAllObjects();
         pLayer->selectObject(pGroup);
         pLayer->ungroupSelection();

         list<GraphicObject*> objects;
         pLayer->getSelectedObjects(objects);

         mObjectIds.clear();
         for (list<GraphicObject*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
         {
            GraphicObject* pObject = *iter;
            if (pObject != NULL)
            {
               string objectId = pObject->getId();
               if (objectId.empty() == false)
               {
                  mObjectIds.push_back(objectId);
               }
            }
         }

         for (list<GraphicObject*>::iterator iter = selectedObjects.begin(); iter != selectedObjects.end(); ++iter)
         {
            GraphicObject* pObject = *iter;
            if ((pObject != NULL) && (pObject != pGroup))
            {
               pLayer->selectObject(pObject);
            }
         }
      }
   }
}