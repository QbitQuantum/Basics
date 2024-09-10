SparseWeightMatrix tangent_weight_matrix(RandomAccessIterator begin, RandomAccessIterator end,
                                         const Neighbors& neighbors, PairwiseCallback callback,
                                         const IndexType target_dimension, const ScalarType shift,
                                         const bool partial_eigendecomposer=false)
{
	timed_context context("KLTSA weight matrix computation");
	const IndexType k = neighbors[0].size();

	SparseTriplets sparse_triplets;
	sparse_triplets.reserve((k*k+2*k+1)*(end-begin));

#pragma omp parallel shared(begin,end,neighbors,callback,sparse_triplets) default(none)
	{
		IndexType index_iter;
		DenseMatrix gram_matrix = DenseMatrix::Zero(k,k);
		DenseVector rhs = DenseVector::Ones(k);
		DenseMatrix G = DenseMatrix::Zero(k,target_dimension+1);
		G.col(0).setConstant(1/sqrt(static_cast<ScalarType>(k)));
		DenseSelfAdjointEigenSolver solver;
		SparseTriplets local_triplets;
		local_triplets.reserve(k*k+2*k+1);

#pragma omp for nowait
		for (index_iter=0; index_iter<static_cast<IndexType>(end-begin); index_iter++)
		{
			const LocalNeighbors& current_neighbors = neighbors[index_iter];

			for (IndexType i=0; i<k; ++i)
			{
				for (IndexType j=i; j<k; ++j)
				{
					ScalarType kij = callback.kernel(begin[current_neighbors[i]],begin[current_neighbors[j]]);
					gram_matrix(i,j) = kij;
					gram_matrix(j,i) = kij;
				}
			}

			centerMatrix(gram_matrix);

			//UNRESTRICT_ALLOC;
#ifdef TAPKEE_WITH_ARPACK
			if (partial_eigendecomposer)
			{
				G.rightCols(target_dimension).noalias() =
					eigendecomposition<DenseMatrix,DenseMatrixOperation>(Arpack,gram_matrix,target_dimension,0).first;
			}
			else
#endif
			{
				solver.compute(gram_matrix);
				G.rightCols(target_dimension).noalias() = solver.eigenvectors().rightCols(target_dimension);
			}
			//RESTRICT_ALLOC;
			gram_matrix.noalias() = G * G.transpose();

			SparseTriplet diagonal_triplet(index_iter,index_iter,shift);
			local_triplets.push_back(diagonal_triplet);
			for (IndexType i=0; i<k; ++i)
			{
				SparseTriplet neighborhood_diagonal_triplet(current_neighbors[i],current_neighbors[i],1.0);
				local_triplets.push_back(neighborhood_diagonal_triplet);

				for (IndexType j=0; j<k; ++j)
				{
					SparseTriplet tangent_triplet(current_neighbors[i],current_neighbors[j],-gram_matrix(i,j));
					local_triplets.push_back(tangent_triplet);
				}
			}
#pragma omp critical
			{
				copy(local_triplets.begin(),local_triplets.end(),back_inserter(sparse_triplets));
			}

			local_triplets.clear();
		}
	}

	return sparse_matrix_from_triplets(sparse_triplets, end-begin, end-begin);
}