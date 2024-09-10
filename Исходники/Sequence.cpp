void Sequence::initialize_Sequence(int RU_number, std::string promoter, int p_size,
                                  std::string gene, int g_size) {
    regulation_unit_number = RU_number;
    gene_sequence += gene;
    gene_size = g_size;
    promoter_sequence += promoter;
    promoter_size = p_size;
    Translation();
}