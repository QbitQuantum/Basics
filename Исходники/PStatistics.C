double
Partitioner::CodeCriteria::get_vote(const RegionStats *stats, std::vector<double> *votes) const
{
    if (votes!=NULL)
        votes->resize(dictionary.size(), NAN);

    double sum=0.0, total_wt=0.0;
    for (size_t cc_id=0; cc_id<criteria.size(); ++cc_id) {
        if (criteria[cc_id].weight <= 0.0)
            continue;

        size_t stat_id = stats->find_analysis(get_name(cc_id));
        if (-1==(ssize_t)stat_id)
            continue;

        double stat_val = stats->get_value(stat_id);
        if (!std::isnan(stat_val)) {
            double c = 0.0==criteria[cc_id].variance ?
                       (stat_val==criteria[cc_id].mean ? 1.0 : 0.0) :
                       1 + erf(-fabs(stat_val-criteria[cc_id].mean) / sqrt(2*criteria[cc_id].variance));
            if (votes)
                (*votes)[cc_id] = c;
            if (!std::isnan(c)) {
                sum += c * criteria[cc_id].weight;
                total_wt += criteria[cc_id].weight;
            }
        }
    }
    return total_wt>0.0 ? sum / total_wt : NAN;
}