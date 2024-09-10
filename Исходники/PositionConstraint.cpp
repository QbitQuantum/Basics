 void PositionConstraint::fillObjGrad(std::vector<double>& dG) {
     VectorXd dP = evalCon();
     for(int dofIndex = 0; dofIndex < mNode->getNumDependentDofs(); dofIndex++) {
         int i = mNode->getDependentDof(dofIndex);            
         const Var* v = mVariables[i];
         double w = v->mWeight;
         VectorXd J = xformHom(mNode->getDerivWorldTransform(dofIndex), mOffset);
         J /= w;
         dG[i] += 2 * dP.dot(J);
     }
 }