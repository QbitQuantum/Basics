void bkgl::updateInverseTransposeModelview()
{
  if (curMatrixStack == &modelViewStack)
  {
	Matrix M = curMatrixStack->top();
	inverseTransposeModelview = M.transpose().inverse();
  }
}