// calculate models bounding box (needed for simple shadows and trivial rejection of in-fog/haze-case)
static void CalculateBoundingBox( CModelObject *pmo, CRenderModel &rm)
{
  if( rm.rm_ulFlags & RMF_BBOXSET) return;
  // get model's data and lerp info
  rm.rm_pmdModelData = (CModelData*)pmo->GetData();
  pmo->GetFrame( rm.rm_iFrame0, rm.rm_iFrame1, rm.rm_fRatio);
  // calculate projection model bounding box in object space
  const FLOAT3D &vMin0 = rm.rm_pmdModelData->md_FrameInfos[rm.rm_iFrame0].mfi_Box.Min();
  const FLOAT3D &vMax0 = rm.rm_pmdModelData->md_FrameInfos[rm.rm_iFrame0].mfi_Box.Max();
  const FLOAT3D &vMin1 = rm.rm_pmdModelData->md_FrameInfos[rm.rm_iFrame1].mfi_Box.Min();
  const FLOAT3D &vMax1 = rm.rm_pmdModelData->md_FrameInfos[rm.rm_iFrame1].mfi_Box.Max();
  rm.rm_vObjectMinBB = Lerp( vMin0, vMin1, rm.rm_fRatio);
  rm.rm_vObjectMaxBB = Lerp( vMax0, vMax1, rm.rm_fRatio);
  rm.rm_vObjectMinBB(1) *= pmo->mo_Stretch(1);  rm.rm_vObjectMaxBB(1) *= pmo->mo_Stretch(1);
  rm.rm_vObjectMinBB(2) *= pmo->mo_Stretch(2);  rm.rm_vObjectMaxBB(2) *= pmo->mo_Stretch(2);
  rm.rm_vObjectMinBB(3) *= pmo->mo_Stretch(3);  rm.rm_vObjectMaxBB(3) *= pmo->mo_Stretch(3);
  rm.rm_ulFlags |= RMF_BBOXSET;
}