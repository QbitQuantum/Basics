void GLProgram::setUniformsForBuiltins(const Mat4 &matrixMV)
{
    auto& matrixP = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

    if(_flags.usesP)
        setUniformLocationWithMatrix4fv(_builtInUniforms[UNIFORM_P_MATRIX], matrixP.m, 1);

    if(_flags.usesMV)
        setUniformLocationWithMatrix4fv(_builtInUniforms[UNIFORM_MV_MATRIX], matrixMV.m, 1);

    if(_flags.usesMVP) {
        Mat4 matrixMVP = matrixP * matrixMV;
        setUniformLocationWithMatrix4fv(_builtInUniforms[UNIFORM_MVP_MATRIX], matrixMVP.m, 1);
    }

    if (_flags.usesNormal)
    {
        Mat4 mvInverse = matrixMV;
        mvInverse.m[12] = mvInverse.m[13] = mvInverse.m[14] = 0.0f;
        mvInverse.inverse();
        mvInverse.transpose();
        GLfloat normalMat[9];
        normalMat[0] = mvInverse.m[0];
        normalMat[1] = mvInverse.m[1];
        normalMat[2] = mvInverse.m[2];
        normalMat[3] = mvInverse.m[4];
        normalMat[4] = mvInverse.m[5];
        normalMat[5] = mvInverse.m[6];
        normalMat[6] = mvInverse.m[8];
        normalMat[7] = mvInverse.m[9];
        normalMat[8] = mvInverse.m[10];
        setUniformLocationWithMatrix3fv(_builtInUniforms[UNIFORM_NORMAL_MATRIX], normalMat, 1);
    }

    if(_flags.usesTime) {
        // This doesn't give the most accurate global time value.
        // Cocos2D doesn't store a high precision time value, so this will have to do.
        // Getting Mach time per frame per shader using time could be extremely expensive.
        float time = _director->getTotalFrames() * _director->getAnimationInterval();

        setUniformLocationWith4f(_builtInUniforms[GLProgram::UNIFORM_TIME], time/10.0, time, time*2, time*4);
        setUniformLocationWith4f(_builtInUniforms[GLProgram::UNIFORM_SIN_TIME], time/8.0, time/4.0, time/2.0, sinf(time));
        setUniformLocationWith4f(_builtInUniforms[GLProgram::UNIFORM_COS_TIME], time/8.0, time/4.0, time/2.0, cosf(time));
    }

    if(_flags.usesRandom)
        setUniformLocationWith4f(_builtInUniforms[GLProgram::UNIFORM_RANDOM01], CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1());
}