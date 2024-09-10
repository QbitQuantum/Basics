void CleanTree(TreeType& node)
{
  node.Stat().LastDistanceNode() = NULL;
  node.Stat().LastDistance() = 0.0;

  for (size_t i = 0; i < node.NumChildren(); ++i)
    CleanTree(node.Child(i));
}