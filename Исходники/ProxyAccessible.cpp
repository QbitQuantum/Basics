void ProxyAccessible::SelectedItems(
    nsTArray<ProxyAccessible*>* aSelectedItems) {
  AutoTArray<uint64_t, 10> itemIDs;
  Unused << mDoc->SendSelectedItems(mID, &itemIDs);
  aSelectedItems->SetCapacity(itemIDs.Length());
  for (size_t i = 0; i < itemIDs.Length(); ++i) {
    aSelectedItems->AppendElement(mDoc->GetAccessible(itemIDs[i]));
  }
}