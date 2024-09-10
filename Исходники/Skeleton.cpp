//#include "d3dx10.h"
//#pragma comment(lib, "d3dx10.lib")
void skeleton::loadKeyframe(joint& j,int time,keyframeTranslation& translation,keyframeRotation& rotation,keyframeScale& scale)
{
	MVector position;

	int parentIdx = j.parentIndex;
int DEBUG_TIME = 7;
	MMatrix matrix;
	{
		matrix = j.jointDag.inclusiveMatrix();
		MFnIkJoint jn(j.jointDag);
		if(jn.name() == "L_toe2")
		{
			char str[256];
			sprintf(str,"%5.5f,%5.5f,%5.5f\n\n",matrix[3][0],matrix[3][1],matrix[3][2]);
			OutputDebugString(str);
		}
		if(time == DEBUG_TIME)
		{
			MFnIkJoint jn(j.jointDag);
			if(jn.name() == "L_knee")
			{
				char str[256];
				sprintf(str,"%5.5f,%5.5f,%5.5f,%5.5f\n%5.5f,%5.5f,%5.5f,%5.5f\n%5.5f,%5.5f,%5.5f,%5.5f\n%5.5f,%5.5f,%5.5f,%5.5f\n\n",
					matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],
					matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],
					matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],
					matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3]);
				//sprintf(str,"%5.5f,%5.5f,%5.5f\n\n",matrix[3][0],matrix[3][1],matrix[3][2]);
				OutputDebugString(str);
//				breakable;
			}
		}

		//printMatrix(matrix);
		MMatrix worldMatrix = j.worldMatrix;
		//printMatrix(worldMatrix);

		MMatrix invWorldMatrix = worldMatrix.inverse();
		//matrix = invWorldMatrix * matrix;

		//MTransformationMatrix mtm = matrix;
		//double q_x,q_y,q_z,q_w;
		//mtm.getRotationQuaternion(q_x,q_y,q_z,q_w);
		//double s_xyz[3];
		//mtm.getScale(s_xyz,MSpace::kWorld);
		//MVector t_xyz = mtm.getTranslation(MSpace::kWorld);

		//D3DXMATRIX d3dM(matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],
		//	matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],
		//	matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],
		//	matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3]);

		//D3DXVECTOR3 d3dS,d3dT;
		//D3DXQUATERNION d3dQ;
		//HRESULT hr = D3DXMatrixDecompose(&d3dS,&d3dQ,&d3dT,&d3dM);

		//MMatrix matrixT = worldMatrix * matrix;


		//float t[3],q[4],s[3];
		//extractTranMatrix(matrix,t,q,s);

		//Vector3 t1(t[0],t[1],t[2]);
		//Quaternion q1(q_x,q_y,q_z,q_w);//q[0],q[1],q[2],q[3]);
		//Vector3 s1(s[0],s[1],s[2]);
		//Matrix4 m;
		//m.transform(t1,s1,q1);

		//printMatrix(matrix);

		if(j.parentIndex >= 0)
		{
			MMatrix pMatrix = m_joints[parentIdx].jointDag.inclusiveMatrix();
			//printMatrix(pMatrix);
			MMatrix pWorldMatrix = m_joints[parentIdx].worldMatrix;
			//printMatrix(pWorldMatrix);
			MMatrix invpWorldMatrix = pWorldMatrix.inverse();
			//pMatrix = invpWorldMatrix * pMatrix;
			//printMatrix(pMatrix);

			MMatrix pInvMatrix = pMatrix.inverse();
			matrix = matrix * pInvMatrix;
			//printMatrix(matrix);
		}
	}
	if(time == DEBUG_TIME)
	{
		MFnIkJoint jn(j.jointDag);
		if(jn.name() == "L_knee")
		{
			char str[256];
			sprintf(str,"%5.5f,%5.5f,%5.5f,%5.5f\n%5.5f,%5.5f,%5.5f,%5.5f\n%5.5f,%5.5f,%5.5f,%5.5f\n%5.5f,%5.5f,%5.5f,%5.5f\n\n",
				matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],
				matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],
				matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],
				matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3]);
			OutputDebugString(str);
//			breakable;
		}
	}
	{
		MMatrix matrix	= j.jointDag.inclusiveMatrix() * j.jointDag.exclusiveMatrixInverse();
		//printMatrix(matrix);
		MMatrix worldMatrix = j.localMatrix;
		//printMatrix(worldMatrix);

		MMatrix invWorldMatrix = worldMatrix.inverse();
		matrix = matrix * invWorldMatrix;
		if(j.parentIndex >= 0)
		{
			matrix = matrix * m_joints[j.parentIndex].localMatrix;
		}
		//printMatrix(matrix);
	}

	extractTranMatrix(matrix,translation.v,rotation.q,scale.v);
	if(time >= DEBUG_TIME)
	{
		MFnIkJoint jn(j.jointDag);
		if(jn.name() == "L_leg")
		{
			char str[256];
			sprintf(str,"%5.5f,%5.5f,%5.5f\n\n",translation.v[0],translation.v[1],translation.v[2]);
			OutputDebugString(str);
			sprintf(str,"%5.5f,%5.5f,%5.5f,%5.5f\n\n",rotation.q[0],rotation.q[1],rotation.q[2],rotation.q[3]);
			OutputDebugString(str);
			sprintf(str,"%5.5f,%5.5f,%5.5f\n\n",scale.v[0],scale.v[1],scale.v[2]);
			OutputDebugString(str);

			/*D3DXMATRIX d3dM(matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],
				matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],
				matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],
				matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3]);

			D3DXVECTOR3 d3dS,d3dT;
			D3DXQUATERNION d3dQ;
			HRESULT hr = D3DXMatrixDecompose(&d3dS,&d3dQ,&d3dT,&d3dM);
			hr = hr;*/

			//rotation.q[0] = -rotation.q[0];
			//rotation.q[1] = -rotation.q[1];
			//rotation.q[2] = -rotation.q[2];
			//rotation.q[3] = -rotation.q[3];
		}
	}

	/*D3DXQUATERNION q1 = D3DXQUATERNION(0.14122,0.09228,-0.82219,0.54365);
	D3DXQUATERNION q2 = D3DXQUATERNION(-0.13556,-0.09684,0.85495,-0.49124);
	D3DXQUATERNION q3;
	D3DXQuaternionSlerp(&q3,&q1,&q2,1-0.63636363);*/
	translation.time = time;
	rotation.time = time;
	scale.time = time;
}