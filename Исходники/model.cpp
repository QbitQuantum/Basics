void Model::updateJoints(float fTime)
{


    //std::cout << "Current Time: " << fTime << std::endl;
    // update matrix
    for(int i = 0; i < COUNT_MODEL_SIMULATE; i++)
    {
        // update matrix
        for(int x = 0; x < m_usNumJoints; x++)
        {
            //Transformation matrix
            vgMs3d::CMatrix4X4 matTmp;
            //Current joint
            MS3DJoint * pJoint = &m_pJoints[x];
            //Current frame]
            unsigned int uiFrame = 0;

            //if there are no keyframes, don't do any transformations
            if(pJoint->m_usNumRotFrames == 0 && pJoint->m_TransKeyFrames == 0)
            {
                pJoint->m_matFinal = pJoint->m_matAbs;
                continue;
            }
            //Calculate the current frame
            //Translation
            while(uiFrame < pJoint->m_usNumTransFrames && pJoint->m_TransKeyFrames[uiFrame].m_fTime < fTime)
                uiFrame++;

            float fTranslation[3];
            float fDeltaT = 1;
            float fInterp = 0;

            //If its at the extremes
            if(uiFrame == 0)
                memcpy(fTranslation, pJoint->m_TransKeyFrames[0].m_fParam, sizeof(float[3]));
            else if(uiFrame == pJoint->m_usNumTransFrames)
                memcpy(fTranslation, pJoint->m_TransKeyFrames[uiFrame-1].m_fParam, sizeof(float[3]));
            //If its in the middle of two frames
            else
            {
                MS3DKeyframe * pkCur = &pJoint->m_TransKeyFrames[uiFrame];
                MS3DKeyframe * pkPrev = &pJoint->m_TransKeyFrames[uiFrame-1];

                fDeltaT = pkCur->m_fTime - pkPrev->m_fTime;
                fInterp = (fTime - pkPrev->m_fTime) / fDeltaT;

                //Interpolate between the translations
                fTranslation[0] = pkPrev->m_fParam[0] + (pkCur->m_fParam[0] - pkPrev->m_fParam[0]) * fInterp;
                fTranslation[1] = pkPrev->m_fParam[1] + (pkCur->m_fParam[1] - pkPrev->m_fParam[1]) * fInterp;
                fTranslation[2] = pkPrev->m_fParam[2] + (pkCur->m_fParam[2] - pkPrev->m_fParam[2]) * fInterp;
            }
            //Calculate the current rotation
            uiFrame = 0;
            while(uiFrame < pJoint->m_usNumRotFrames && pJoint->m_RotKeyFrames[uiFrame].m_fTime < fTime)
                uiFrame++;


            //If its at the extremes
            if(uiFrame == 0)
                matTmp.SetRotation(pJoint->m_RotKeyFrames[0].m_fParam);
            else if(uiFrame == pJoint->m_usNumTransFrames)
                matTmp.SetRotation(pJoint->m_RotKeyFrames[uiFrame-1].m_fParam);
            //If its in the middle of two frames, use a quaternion SLERP operation to calculate a new position
            else
            {
                MS3DKeyframe * pkCur = &pJoint->m_RotKeyFrames[uiFrame];
                MS3DKeyframe * pkPrev = &pJoint->m_RotKeyFrames[uiFrame-1];

                fDeltaT = pkCur->m_fTime - pkPrev->m_fTime;
                fInterp = (fTime - pkPrev->m_fTime) / fDeltaT;

                //Create a rotation quaternion for each frame
                vgMs3d::CQuaternion qCur;
                vgMs3d::CQuaternion qPrev;
                qCur.FromEulers(pkCur->m_fParam);
                qPrev.FromEulers(pkPrev->m_fParam);
                //SLERP between the two frames
                vgMs3d::CQuaternion qFinal = SLERP(qPrev, qCur, fInterp);

                //Convert the quaternion to a rota tion matrix
                matTmp = qFinal.ToMatrix4();
            }

            //Set the translation part of the matrix
            matTmp.SetTranslation(fTranslation);

            //Calculate the joints final transformation
            vgMs3d::CMatrix4X4 matFinal = pJoint->m_matLocal * matTmp;

            //if there is no parent, just use the matrix you just made
            if(pJoint->m_sParent == -1)
                pJoint->m_matFinal = matFinal;
            //otherwise the final matrix is the parents final matrix * the new matrix
            else
                pJoint->m_matFinal = m_pJoints[pJoint->m_sParent].m_matFinal * matFinal;
        }//x

        for (int i=0; i<m_usNumJoints; i++)
        {
            memcpy(m_pJointsMatrix+16*i, m_pJoints[i].m_matFinal.Get(), sizeof(float)*16 );
        }
    }//i

}