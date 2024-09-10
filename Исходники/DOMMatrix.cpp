already_AddRefed<DOMMatrix>
DOMMatrix::Constructor(const GlobalObject& aGlobal, const Sequence<double>& aNumberSequence, ErrorResult& aRv)
{
  RefPtr<DOMMatrix> obj = new DOMMatrix(aGlobal.GetAsSupports());
  SetDataInMatrix(obj, aNumberSequence.Elements(), aNumberSequence.Length(), aRv);

  return obj.forget();
}