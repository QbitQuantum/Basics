vector<uint> matrix_utils::remove_linear_dependence_rows(Matrix &matrix) {
	vector<uint> removed_rows;
	//need to prevent swap whole columns, just swap indexes
	vector<uint> columns(matrix[0].size());
	for (uint i = 0; i != columns.size(); i++) {
		columns[i] = i;
	}

	Matrix temp_matrix;
	temp_matrix.reserve(matrix.size());
	for (uint i = 0; i != matrix.size(); i++) {
		temp_matrix.push_back(vector<double>(matrix[i].begin(), matrix[i].end()));
	}
	for (uint i = 0; i != temp_matrix.size(); i++) {
		uint index_max = i;
		for (uint j = i + 1; j != temp_matrix[0].size(); j++) {
			if (abs(temp_matrix[i][columns[index_max]]) < abs(temp_matrix[i][columns[j]])) {
				index_max = j;
			}
		}
		if (index_max != i) {
			uint tmp = columns[i];
			columns[i] = columns[index_max];
			columns[index_max] = tmp;
		}
		index_max = columns[i];
		if (abs(temp_matrix[i][index_max]) < 1e-7) {
			temp_matrix.erase(temp_matrix.begin() + i);
			matrix.erase(matrix.begin() + i);
			removed_rows.push_back(i);
			i--;
			continue;
		}

		double divisor = temp_matrix[i][index_max];
		for (uint k = 0; k != temp_matrix[0].size(); k++) {
			temp_matrix[i][k] /= divisor;
		}
		for (uint j = i + 1; j != temp_matrix.size(); j++) {
			double multiplier = -temp_matrix[j][index_max];
			for (uint k = 0; k != temp_matrix[0].size(); k++) {
				temp_matrix[j][k] += temp_matrix[i][k] * multiplier;
			}
		}
	}

	return removed_rows;
}