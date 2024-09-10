void TriangleMesh3f::drawImmediate()
{
    glBegin( GL_TRIANGLES );

    for( uint i = 0; i < m_vFaces.size(); ++i )
    {
        TriangleMesh3fFace* pFace = m_vFaces[i];
        TriangleMesh3fHalfEdge* e0 = pFace->getInitialEdge();
        TriangleMesh3fHalfEdge* e1 = e0->getNextEdge();
        TriangleMesh3fHalfEdge* e2 = e1->getNextEdge();

        Vector3f* v0 = e0->getDestinationVertex()->getPosition();
        Vector3f* v1 = e1->getDestinationVertex()->getPosition();
        Vector3f* v2 = e2->getDestinationVertex()->getPosition();

        Vector3f faceNormal;
        pFace->getNormal( &faceNormal );
        faceNormal.normalize();

        glNormal3fv( faceNormal );
        glVertex3fv( v0->elements );
        glVertex3fv( v1->elements );
        glVertex3fv( v2->elements );
    }

    glEnd();
}