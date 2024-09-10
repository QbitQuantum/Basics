 void uniformMatrix4fv(GLint uniform, Matrix mat)
 {
     DirectX::XMFLOAT4X4 fMat;
     XMStoreFloat4x4(&fMat, mat.getXMMatrix());
     glUniformMatrix4fv(uniform, 1, GL_FALSE, &fMat.m[0][0]);
 }