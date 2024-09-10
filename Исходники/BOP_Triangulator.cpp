/**
 * Returns which of vertex v1 or v2 is nearest to u.
 * @param mesh mesh that contains the faces, edges and vertices
 * @param u reference vertex index
 * @param v1 first vertex index
 * @param v2 second vertex index
 * @return the nearest vertex index
 */
BOP_Index BOP_getNearestVertex(BOP_Mesh* mesh, BOP_Index u, BOP_Index v1, BOP_Index v2)
{
	MT_Point3 q = mesh->getVertex(u)->getPoint();
	MT_Point3 p1 = mesh->getVertex(v1)->getPoint();
	MT_Point3 p2 = mesh->getVertex(v2)->getPoint();
	if (BOP_comp(q.distance(p1), q.distance(p2)) > 0) return v2;
	else return v1;
}