Triangle::~Triangle(){
        int i;
        triangles.Remove(this);
        for(i=0;i<3;i++) {
                if(vertex[i]) vertex[i]->face.Remove(this);
        }
        for(i=0;i<3;i++) {
                int i2 = (i+1)%3;
                if(!vertex[i] || !vertex[i2]) continue;
                vertex[i ]->RemoveIfNonNeighbor(vertex[i2]);
                vertex[i2]->RemoveIfNonNeighbor(vertex[i ]);
        }
}