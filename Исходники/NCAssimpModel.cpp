aiMatrix4x4 NCAssimpModel::returnTranslation(aiMatrix4x4 incmat) {
    
    aiVector3D pos;
    aiQuaternion quat;
    aiVector3D scale;
    
    incmat.Decompose(scale, quat, pos);
    
    aiMatrix4x4 trans;
    aiMatrix4x4::Translation(pos, trans);
    
    return trans;
    
}