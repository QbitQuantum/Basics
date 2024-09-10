void SubSystem::calcGrad(VEC_pD &params, Eigen::VectorXd &grad)
{
    assert(grad.size() == int(params.size()));

    grad.setZero();
    for (int j=0; j < int(params.size()); j++) {
        MAP_pD_pD::const_iterator
          pmapfind = pmap.find(params[j]);
        if (pmapfind != pmap.end()) {
            // assert(p2c.find(pmapfind->second) != p2c.end());
            std::vector<Constraint *> constrs=p2c[pmapfind->second];
            for (std::vector<Constraint *>::const_iterator constr = constrs.begin();
                 constr != constrs.end(); ++constr)
                grad[j] += (*constr)->error() * (*constr)->grad(pmapfind->second);
        }
    }
}