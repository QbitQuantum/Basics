math::Jacobian
TemplatedJacobianNode<NodeType>::getWorldJacobian(
    const Eigen::Vector3d& _offset) const
{
  math::Jacobian J = static_cast<const NodeType*>(this)->getWorldJacobian();
  J.bottomRows<3>() += J.topRows<3>().colwise().cross(
                                      getWorldTransform().linear() * _offset);

  return J;
}