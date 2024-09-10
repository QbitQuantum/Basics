double FastMKSRules<KernelType, TreeType>::Score(const size_t queryIndex,
        TreeType& referenceNode)
{
    // Compare with the current best.
    const double bestKernel = products(products.n_rows - 1, queryIndex);

    // See if we can perform a parent-child prune.
    const double furthestDist = referenceNode.FurthestDescendantDistance();
    if (referenceNode.Parent() != NULL)
    {
        double maxKernelBound;
        const double parentDist = referenceNode.ParentDistance();
        const double combinedDistBound = parentDist + furthestDist;
        const double lastKernel = referenceNode.Parent()->Stat().LastKernel();
        if (kernel::KernelTraits<KernelType>::IsNormalized)
        {
            const double squaredDist = std::pow(combinedDistBound, 2.0);
            const double delta = (1 - 0.5 * squaredDist);
            if (lastKernel <= delta)
            {
                const double gamma = combinedDistBound * sqrt(1 - 0.25 * squaredDist);
                maxKernelBound = lastKernel * delta +
                                 gamma * sqrt(1 - std::pow(lastKernel, 2.0));
            }
            else
            {
                maxKernelBound = 1.0;
            }
        }
        else
        {
            maxKernelBound = lastKernel +
                             combinedDistBound * queryKernels[queryIndex];
        }

        if (maxKernelBound < bestKernel)
            return DBL_MAX;
    }

    // Calculate the maximum possible kernel value, either by calculating the
    // centroid or, if the centroid is a point, use that.
    ++scores;
    double kernelEval;
    if (tree::TreeTraits<TreeType>::FirstPointIsCentroid)
    {
        // Could it be that this kernel evaluation has already been calculated?
        if (tree::TreeTraits<TreeType>::HasSelfChildren &&
                referenceNode.Parent() != NULL &&
                referenceNode.Point(0) == referenceNode.Parent()->Point(0))
        {
            kernelEval = referenceNode.Parent()->Stat().LastKernel();
        }
        else
        {
            kernelEval = BaseCase(queryIndex, referenceNode.Point(0));
        }
    }
    else
    {
        const arma::vec queryPoint = querySet.unsafe_col(queryIndex);
        arma::vec refCentroid;
        referenceNode.Centroid(refCentroid);

        kernelEval = kernel.Evaluate(queryPoint, refCentroid);
    }

    referenceNode.Stat().LastKernel() = kernelEval;

    double maxKernel;
    if (kernel::KernelTraits<KernelType>::IsNormalized)
    {
        const double squaredDist = std::pow(furthestDist, 2.0);
        const double delta = (1 - 0.5 * squaredDist);
        if (kernelEval <= delta)
        {
            const double gamma = furthestDist * sqrt(1 - 0.25 * squaredDist);
            maxKernel = kernelEval * delta +
                        gamma * sqrt(1 - std::pow(kernelEval, 2.0));
        }
        else
        {
            maxKernel = 1.0;
        }
    }
    else
    {
        maxKernel = kernelEval + furthestDist * queryKernels[queryIndex];
    }

    // We return the inverse of the maximum kernel so that larger kernels are
    // recursed into first.
    return (maxKernel > bestKernel) ? (1.0 / maxKernel) : DBL_MAX;
}