//Алгоритм вперед-назад. Использует несколько иначе сформированные матрицы, нежели Витерби
std::vector<int> Forward_Backward_impl(long num_of_states, Matrix &trans, Matrix& emission, Matrix &start_prob, std::vector<int> &obs_seq)
{
    std::vector<Matrix> obs;
    for (int i = 0; i < obs_seq.size(); i++) obs.push_back(make_obs_for_forward_backward(obs_seq[i], num_of_states, emission));
    Matrix trans_trans = trans.trans();
    std::vector<Matrix> F;
    F.push_back(start_prob);
    for(int i = 0; i < obs.size(); i++)
    {
        F.push_back(
            obs[i].dot(&trans_trans).dot(&F[F.size() - 1]).normalize()
        );
    }
    Matrix b_start(num_of_states, 1);
    for(int i = 0; i < num_of_states; i++) b_start.set_element(i, 0, 1.0);
    std::vector<Matrix> B;
    B.push_back(b_start);
    for(int i = obs.size() - 1; i >= 0; i--)
    {
        B.push_back(
            trans.dot(&obs[i]).dot(&B[B.size() - 1]).normalize()
        );
    }
    std::vector<Matrix> gamma;
    for (int i = 0; i < F.size(); i++)
    {
        gamma.push_back(
            F[i].mul(&B[B.size() - i - 1]).normalize()
        );
    }
    std::vector<int> res;
    for(int i = 1; i < gamma.size(); i++) res.push_back(gamma[i].max_value_index());
    return res;
}