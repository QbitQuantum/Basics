already_AddRefed<TouchList> TouchEvent::CopyTouches(
    const Sequence<OwningNonNull<Touch>>& aTouches) {
  RefPtr<TouchList> list = new TouchList(GetParentObject());
  size_t len = aTouches.Length();
  for (size_t i = 0; i < len; ++i) {
    list->Append(aTouches[i]);
  }
  return list.forget();
}