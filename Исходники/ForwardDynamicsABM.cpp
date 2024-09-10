// A part of phase 2 (inbound loop) that can be calculated before external forces are given
void ForwardDynamicsABM::calcABMPhase2Part1()
{
    const LinkTraverse& traverse = body->linkTraverse();
    const int n = traverse.numLinks();

    for(int i = n-1; i >= 0; --i){
        DyLink* link = static_cast<DyLink*>(traverse[i]);

        for(DyLink* child = link->child(); child; child = child->sibling()){

            if(child->isFixedJoint()){
                link->Ivv() += child->Ivv();
                link->Iwv() += child->Iwv();
                link->Iww() += child->Iww();

            }else{
                const Vector3 hhv_dd = child->hhv() / child->dd();
                link->Ivv().noalias() += child->Ivv() - child->hhv() * hhv_dd.transpose();
                link->Iwv().noalias() += child->Iwv() - child->hhw() * hhv_dd.transpose();
                link->Iww().noalias() += child->Iww() - child->hhw() * (child->hhw() / child->dd()).transpose();
            }

            link->pf()  .noalias() += child->Ivv() * child->cv() + child->Iwv().transpose() * child->cw();
            link->ptau().noalias() += child->Iwv() * child->cv() + child->Iww() * child->cw();
        }

        if(i > 0){
            if(!link->isFixedJoint()){
                link->hhv().noalias() = link->Ivv() * link->sv() + link->Iwv().transpose() * link->sw();
                link->hhw().noalias() = link->Iwv() * link->sv() + link->Iww() * link->sw();
                link->dd() = link->sv().dot(link->hhv()) + link->sw().dot(link->hhw()) + link->Jm2();
                link->uu() = -(link->hhv().dot(link->cv()) + link->hhw().dot(link->cw()));
            }
        }
    }
}