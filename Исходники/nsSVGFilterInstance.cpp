nsresult
nsSVGFilterInstance::BuildPrimitives(nsTArray<FilterPrimitiveDescription>& aPrimitiveDescrs,
                                     nsTArray<RefPtr<SourceSurface>>& aInputImages)
{
  mSourceGraphicIndex = GetLastResultIndex(aPrimitiveDescrs);

  // Clip previous filter's output to this filter's filter region.
  if (mSourceGraphicIndex >= 0) {
    FilterPrimitiveDescription& sourceDescr = aPrimitiveDescrs[mSourceGraphicIndex];
    sourceDescr.SetPrimitiveSubregion(sourceDescr.PrimitiveSubregion().Intersect(mFilterSpaceBounds));
  }

  // Get the filter primitive elements.
  nsTArray<RefPtr<nsSVGFE> > primitives;
  for (nsIContent* child = mFilterElement->nsINode::GetFirstChild();
       child;
       child = child->GetNextSibling()) {
    RefPtr<nsSVGFE> primitive;
    CallQueryInterface(child, (nsSVGFE**)getter_AddRefs(primitive));
    if (primitive) {
      primitives.AppendElement(primitive);
    }
  }

  // Maps source image name to source index.
  nsDataHashtable<nsStringHashKey, int32_t> imageTable(8);

  // The principal that we check principals of any loaded images against.
  nsCOMPtr<nsIPrincipal> principal = mTargetContent->NodePrincipal();

  bool filterInputIsTainted = IsFilterInputTainted(mTargetContent);

  for (uint32_t primitiveElementIndex = 0;
       primitiveElementIndex < primitives.Length();
       ++primitiveElementIndex) {
    nsSVGFE* filter = primitives[primitiveElementIndex];

    AutoTArray<int32_t,2> sourceIndices;
    nsresult rv = GetSourceIndices(filter, aPrimitiveDescrs, imageTable, sourceIndices);
    if (NS_FAILED(rv)) {
      return rv;
    }

    IntRect primitiveSubregion =
      ComputeFilterPrimitiveSubregion(filter, aPrimitiveDescrs, sourceIndices);

    nsTArray<bool> sourcesAreTainted;
    GetInputsAreTainted(aPrimitiveDescrs, sourceIndices, filterInputIsTainted, sourcesAreTainted);

    FilterPrimitiveDescription descr =
      filter->GetPrimitiveDescription(this, primitiveSubregion, sourcesAreTainted, aInputImages);

    descr.SetIsTainted(filter->OutputIsTainted(sourcesAreTainted, principal));
    descr.SetFilterSpaceBounds(mFilterSpaceBounds);
    descr.SetPrimitiveSubregion(primitiveSubregion.Intersect(descr.FilterSpaceBounds()));

    for (uint32_t i = 0; i < sourceIndices.Length(); i++) {
      int32_t inputIndex = sourceIndices[i];
      descr.SetInputPrimitive(i, inputIndex);

      ColorSpace inputColorSpace = inputIndex >= 0
        ? aPrimitiveDescrs[inputIndex].OutputColorSpace()
        : ColorSpace(ColorSpace::SRGB);

      ColorSpace desiredInputColorSpace = filter->GetInputColorSpace(i, inputColorSpace);
      descr.SetInputColorSpace(i, desiredInputColorSpace);
      if (i == 0) {
        // the output color space is whatever in1 is if there is an in1
        descr.SetOutputColorSpace(desiredInputColorSpace);
      }
    }

    if (sourceIndices.Length() == 0) {
      descr.SetOutputColorSpace(filter->GetOutputColorSpace());
    }

    aPrimitiveDescrs.AppendElement(descr);
    uint32_t primitiveDescrIndex = aPrimitiveDescrs.Length() - 1;

    nsAutoString str;
    filter->GetResultImageName().GetAnimValue(str, filter);
    imageTable.Put(str, primitiveDescrIndex);
  }

  return NS_OK;
}