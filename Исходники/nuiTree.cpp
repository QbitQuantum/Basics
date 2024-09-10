bool nuiTreeBase::DelChild(nuiTreePtr pChild)
{
  for (uint32 i = 0; i < mpChildren.size(); i++)
  {
    if (mpChildren[i] == pChild && pChild)
    {
      ChildDeleted(this, pChild);
      
      mTreeNodeEventSink.DisconnectSource(pChild->Changed);
      mTreeNodeEventSink.DisconnectSource(pChild->ChildAdded);
      mTreeNodeEventSink.DisconnectSource(pChild->ChildDeleted);
      mTreeNodeEventSink.DisconnectSource(pChild->Deleted);

      pChild->SetParent(NULL);
      mpChildren[i]->Release();
      mpChildren.erase(mpChildren.begin()+i);
      
      Changed();
      return true;
    }
  }

  return false;
}