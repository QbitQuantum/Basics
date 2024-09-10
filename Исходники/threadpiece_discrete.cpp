void ThreadPiece::calculateBinormal(const Vector3d& edge_prev, const Vector3d& edge_after, Vector3d& binormal)
{
  binormal = 2.0*edge_prev.cross(edge_after);
  binormal /= ((_my_thread->rest_length())*(_my_thread->rest_length()) + edge_prev.dot(edge_after));
}