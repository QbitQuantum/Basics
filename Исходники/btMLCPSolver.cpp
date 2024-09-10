void btMLCPSolver::createMLCPFast(const btContactSolverInfo& infoGlobal)
{
	int numContactRows = interleaveContactAndFriction ? 3 : 1;

	int numConstraintRows = m_allConstraintArray.size();
	int n = numConstraintRows;
	{
		BT_PROFILE("init b (rhs)");
		m_b.resize(numConstraintRows);
		m_bSplit.resize(numConstraintRows);
		m_b.setZero();
		m_bSplit.setZero();
		for (int i=0;i<numConstraintRows ;i++)
		{
			btScalar jacDiag = m_allConstraintArray[i].m_jacDiagABInv;
			if (!btFuzzyZero(jacDiag))
			{
				btScalar rhs = m_allConstraintArray[i].m_rhs;
				btScalar rhsPenetration = m_allConstraintArray[i].m_rhsPenetration;
				m_b[i]=rhs/jacDiag;
				m_bSplit[i] = rhsPenetration/jacDiag;
			}

		}
	}

	btScalar* w = 0;
	int nub = 0;

	m_lo.resize(numConstraintRows);
	m_hi.resize(numConstraintRows);
 
	{
		BT_PROFILE("init lo/ho");

		for (int i=0;i<numConstraintRows;i++)
		{
			if (0)//m_limitDependencies[i]>=0)
			{
				m_lo[i] = -BT_INFINITY;
				m_hi[i] = BT_INFINITY;
			} else
			{
				m_lo[i] = m_allConstraintArray[i].m_lowerLimit;
				m_hi[i] = m_allConstraintArray[i].m_upperLimit;
			}
		}
	}

	//
	int m=m_allConstraintArray.size();

	int numBodies = m_tmpSolverBodyPool.size();
	btAlignedObjectArray<int> bodyJointNodeArray;
	{
		BT_PROFILE("bodyJointNodeArray.resize");
		bodyJointNodeArray.resize(numBodies,-1);
	}
	btAlignedObjectArray<btJointNode> jointNodeArray;
	{
		BT_PROFILE("jointNodeArray.reserve");
		jointNodeArray.reserve(2*m_allConstraintArray.size());
	}

	static btMatrixXu J3;
	{
		BT_PROFILE("J3.resize");
		J3.resize(2*m,8);
	}
	static btMatrixXu JinvM3;
	{
		BT_PROFILE("JinvM3.resize/setZero");

		JinvM3.resize(2*m,8);
		JinvM3.setZero();
		J3.setZero();
	}
	int cur=0;
	int rowOffset = 0;
	static btAlignedObjectArray<int> ofs;
	{
		BT_PROFILE("ofs resize");
		ofs.resize(0);
		ofs.resizeNoInitialize(m_allConstraintArray.size());
	}				
	{
		BT_PROFILE("Compute J and JinvM");
		int c=0;

		int numRows = 0;

		for (int i=0;i<m_allConstraintArray.size();i+=numRows,c++)
		{
			ofs[c] = rowOffset;
			int sbA = m_allConstraintArray[i].m_solverBodyIdA;
			int sbB = m_allConstraintArray[i].m_solverBodyIdB;
			btRigidBody* orgBodyA = m_tmpSolverBodyPool[sbA].m_originalBody;
			btRigidBody* orgBodyB = m_tmpSolverBodyPool[sbB].m_originalBody;

			numRows = i<m_tmpSolverNonContactConstraintPool.size() ? m_tmpConstraintSizesPool[c].m_numConstraintRows : numContactRows ;
			if (orgBodyA)
			{
				{
					int slotA=-1;
					//find free jointNode slot for sbA
					slotA =jointNodeArray.size();
					jointNodeArray.expand();//NonInitializing();
					int prevSlot = bodyJointNodeArray[sbA];
					bodyJointNodeArray[sbA] = slotA;
					jointNodeArray[slotA].nextJointNodeIndex = prevSlot;
					jointNodeArray[slotA].jointIndex = c;
					jointNodeArray[slotA].constraintRowIndex = i;
					jointNodeArray[slotA].otherBodyIndex = orgBodyB ? sbB : -1;
				}
				for (int row=0;row<numRows;row++,cur++)
				{
					btVector3 normalInvMass =				m_allConstraintArray[i+row].m_contactNormal1 *		orgBodyA->getInvMass();
					btVector3 relPosCrossNormalInvInertia = m_allConstraintArray[i+row].m_relpos1CrossNormal *	orgBodyA->getInvInertiaTensorWorld();

					for (int r=0;r<3;r++)
					{
						J3.setElem(cur,r,m_allConstraintArray[i+row].m_contactNormal1[r]);
						J3.setElem(cur,r+4,m_allConstraintArray[i+row].m_relpos1CrossNormal[r]);
						JinvM3.setElem(cur,r,normalInvMass[r]);
						JinvM3.setElem(cur,r+4,relPosCrossNormalInvInertia[r]);
					}
					J3.setElem(cur,3,0);
					JinvM3.setElem(cur,3,0);
					J3.setElem(cur,7,0);
					JinvM3.setElem(cur,7,0);
				}
			} else
			{
				cur += numRows;
			}
			if (orgBodyB)
			{

				{
					int slotB=-1;
					//find free jointNode slot for sbA
					slotB =jointNodeArray.size();
					jointNodeArray.expand();//NonInitializing();
					int prevSlot = bodyJointNodeArray[sbB];
					bodyJointNodeArray[sbB] = slotB;
					jointNodeArray[slotB].nextJointNodeIndex = prevSlot;
					jointNodeArray[slotB].jointIndex = c;
					jointNodeArray[slotB].otherBodyIndex = orgBodyA ? sbA : -1;
					jointNodeArray[slotB].constraintRowIndex = i;
				}

				for (int row=0;row<numRows;row++,cur++)
				{
					btVector3 normalInvMassB = m_allConstraintArray[i+row].m_contactNormal2*orgBodyB->getInvMass();
					btVector3 relPosInvInertiaB = m_allConstraintArray[i+row].m_relpos2CrossNormal * orgBodyB->getInvInertiaTensorWorld();

					for (int r=0;r<3;r++)
					{
						J3.setElem(cur,r,m_allConstraintArray[i+row].m_contactNormal2[r]);
						J3.setElem(cur,r+4,m_allConstraintArray[i+row].m_relpos2CrossNormal[r]);
						JinvM3.setElem(cur,r,normalInvMassB[r]);
						JinvM3.setElem(cur,r+4,relPosInvInertiaB[r]);
					}
					J3.setElem(cur,3,0);
					JinvM3.setElem(cur,3,0);
					J3.setElem(cur,7,0);
					JinvM3.setElem(cur,7,0);
				}
			}
			else
			{
				cur += numRows;
			}
			rowOffset+=numRows;

		}
		
	}


	//compute JinvM = J*invM.
	const btScalar* JinvM = JinvM3.getBufferPointer();

	const btScalar* Jptr = J3.getBufferPointer();
	{
		BT_PROFILE("m_A.resize");
		m_A.resize(n,n);
	}
	
	{
		BT_PROFILE("m_A.setZero");
		m_A.setZero();
	}
	int c=0;
	{
		int numRows = 0;
		BT_PROFILE("Compute A");
		for (int i=0;i<m_allConstraintArray.size();i+= numRows,c++)
		{
			int row__ = ofs[c];
			int sbA = m_allConstraintArray[i].m_solverBodyIdA;
			int sbB = m_allConstraintArray[i].m_solverBodyIdB;
			btRigidBody* orgBodyA = m_tmpSolverBodyPool[sbA].m_originalBody;
			btRigidBody* orgBodyB = m_tmpSolverBodyPool[sbB].m_originalBody;

			numRows = i<m_tmpSolverNonContactConstraintPool.size() ? m_tmpConstraintSizesPool[c].m_numConstraintRows : numContactRows ;
					
			const btScalar *JinvMrow = JinvM + 2*8*(size_t)row__;

			{
				int startJointNodeA = bodyJointNodeArray[sbA];
				while (startJointNodeA>=0)
				{
					int j0 = jointNodeArray[startJointNodeA].jointIndex;
					int cr0 = jointNodeArray[startJointNodeA].constraintRowIndex;
					if (j0<c)
					{
								 
						int numRowsOther = cr0 < m_tmpSolverNonContactConstraintPool.size() ? m_tmpConstraintSizesPool[j0].m_numConstraintRows : numContactRows;
						size_t ofsother = (m_allConstraintArray[cr0].m_solverBodyIdB == sbA) ? 8*numRowsOther  : 0;
						//printf("%d joint i %d and j0: %d: ",count++,i,j0);
						m_A.multiplyAdd2_p8r ( JinvMrow, 
						Jptr + 2*8*(size_t)ofs[j0] + ofsother, numRows, numRowsOther,  row__,ofs[j0]);
					}
					startJointNodeA = jointNodeArray[startJointNodeA].nextJointNodeIndex;
				}
			}

			{
				int startJointNodeB = bodyJointNodeArray[sbB];
				while (startJointNodeB>=0)
				{
					int j1 = jointNodeArray[startJointNodeB].jointIndex;
					int cj1 = jointNodeArray[startJointNodeB].constraintRowIndex;

					if (j1<c)
					{
						int numRowsOther =  cj1 < m_tmpSolverNonContactConstraintPool.size() ? m_tmpConstraintSizesPool[j1].m_numConstraintRows : numContactRows;
						size_t ofsother = (m_allConstraintArray[cj1].m_solverBodyIdB == sbB) ? 8*numRowsOther  : 0;
						m_A.multiplyAdd2_p8r ( JinvMrow + 8*(size_t)numRows, 
						Jptr + 2*8*(size_t)ofs[j1] + ofsother, numRows, numRowsOther, row__,ofs[j1]);
					}
					startJointNodeB = jointNodeArray[startJointNodeB].nextJointNodeIndex;
				}
			}
		}

		{
			BT_PROFILE("compute diagonal");
			// compute diagonal blocks of m_A

			int  row__ = 0;
			int numJointRows = m_allConstraintArray.size();

			int jj=0;
			for (;row__<numJointRows;)
			{

				int sbA = m_allConstraintArray[row__].m_solverBodyIdA;
				int sbB = m_allConstraintArray[row__].m_solverBodyIdB;
				btRigidBody* orgBodyA = m_tmpSolverBodyPool[sbA].m_originalBody;
				btRigidBody* orgBodyB = m_tmpSolverBodyPool[sbB].m_originalBody;


				const unsigned int infom =  row__ < m_tmpSolverNonContactConstraintPool.size() ? m_tmpConstraintSizesPool[jj].m_numConstraintRows : numContactRows;
				
				const btScalar *JinvMrow = JinvM + 2*8*(size_t)row__;
				const btScalar *Jrow = Jptr + 2*8*(size_t)row__;
				m_A.multiply2_p8r (JinvMrow, Jrow, infom, infom, row__,row__);
				if (orgBodyB) 
				{
					m_A.multiplyAdd2_p8r (JinvMrow + 8*(size_t)infom, Jrow + 8*(size_t)infom, infom, infom,  row__,row__);
				}
				row__ += infom;
				jj++;
			}
		}
	}

	if (1)
	{
		// add cfm to the diagonal of m_A
		for ( int i=0; i<m_A.rows(); ++i) 
		{
			m_A.setElem(i,i,m_A(i,i)+ m_cfm / infoGlobal.m_timeStep);
		}
	}
				   
	///fill the upper triangle of the matrix, to make it symmetric
	{
		BT_PROFILE("fill the upper triangle ");
		m_A.copyLowerToUpperTriangle();
	}

	{
		BT_PROFILE("resize/init x");
		m_x.resize(numConstraintRows);
		m_xSplit.resize(numConstraintRows);

		if (infoGlobal.m_solverMode&SOLVER_USE_WARMSTARTING)
		{
			for (int i=0;i<m_allConstraintArray.size();i++)
			{
				const btSolverConstraint& c = m_allConstraintArray[i];
				m_x[i]=c.m_appliedImpulse;
				m_xSplit[i] = c.m_appliedPushImpulse;
			}
		} else
		{
			m_x.setZero();
			m_xSplit.setZero();
		}
	}

}