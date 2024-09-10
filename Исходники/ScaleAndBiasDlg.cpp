void ScaleAndBiasDlg::CopyScaleAndBias() {
  FLOATMATRIX4 bias;
  FLOATMATRIX4 scale;

  bias.Translation(biasVec);
  scale.Scaling(scaleVec);

  SetExpertTransform(scale*bias);
}