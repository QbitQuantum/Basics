void Model::compute_NORMALS()
{

        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        mesh.normals_Vertices. fill( Eigen::Vector3d::Zero() );
        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////

        for (int tr=0; tr<totalTriangles; tr++)
        {

                int vertexIndex_1 = mesh.triangles[tr].vertexID_1;
                int vertexIndex_2 = mesh.triangles[tr].vertexID_2;
                int vertexIndex_3 = mesh.triangles[tr].vertexID_3;

                Eigen::Vector3d VertexA;
                Eigen::Vector3d VertexB;
                Eigen::Vector3d VertexC;
                Eigen::Vector3d vect_1;
                Eigen::Vector3d vect_2;
                Eigen::Vector3d currNormal;

                VertexA << mesh.verticesWeighted[vertexIndex_1];   //  0
                VertexB << mesh.verticesWeighted[vertexIndex_2];   //  1
                VertexC << mesh.verticesWeighted[vertexIndex_3];   //  2

                vect_1 = VertexB - VertexA;   // 1 - 0
                vect_2 = VertexC - VertexA;   // 2 - 0

                currNormal = vect_1.cross(vect_2);

                currNormal.normalize();

                /////////////////////////////////////////////////////
                mesh.normals_Vertices[ vertexIndex_1 ] += currNormal;
                mesh.normals_Vertices[ vertexIndex_2 ] += currNormal;
                mesh.normals_Vertices[ vertexIndex_3 ] += currNormal;
                /////////////////////////////////////////////////////

        }

        ///////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////
        for (int vvv=0; vvv< totalVertices; vvv++)      mesh.normals_Vertices[vvv].normalize();
        ///////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////

}