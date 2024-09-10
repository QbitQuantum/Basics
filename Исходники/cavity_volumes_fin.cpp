int main(int argc, const char *argv[])
{
    CavConfig cfg;
    const char *run_control_file = "cavity_volumes_fin.inp";

    if (argc > 1)
        run_control_file = argv[1];

    if (!cfg.init(run_control_file)) {
        std::cerr << "Error while initializing from run control file : " << run_control_file << std::endl;
        return 2;
    }

    cfg.out_inf << "Run control file : " << run_control_file << std::endl;

    CGAL::Timer t;
    int processed_cnt = 0;

    cfg.out_inf << std::endl;
    t.start();
    while (cfg.next_timestep()) {
        const Array_double_3 &a = cfg.atoms.back();
        cfg.out_inf << "Number of input atoms : " << cfg.atoms.size() << std::endl;
        cfg.out_inf << "MD info : " << cfg.ts_info << std::endl;
        cfg.out_inf << "Box : [ " << cfg.box[0] << ", " << cfg.box[1] << ", " << cfg.box[2] << " ]" << std::endl;
        cfg.out_inf << "Last atom : " << a[0] << " " << a[1] << " " << a[2] << std::endl;
        if (!process_conf(cfg)) {
            cfg.out_inf << "process_conf() error. Exiting..." << std::endl;
            return 1;
        }
        processed_cnt++;
    }
    t.stop();

    // save accumulated per-atom surfaces
    if (cfg.out_asf.is_open()) {
        long double total_surf = std::accumulate(cfg.atom_confs_surf.begin(), cfg.atom_confs_surf.end(), 0.0L);
        cfg.out_asf << total_surf << std::endl;  // first line is total exposed surface of all atoms in all confs
        cfg.out_asf << cfg.atom_confs_surf.size() << std::endl;  // second line is the number of atoms
        for (size_t i = 0; i < cfg.atom_confs_surf.size(); i++)
            cfg.out_asf << cfg.atom_confs_surf[i] << std::endl;
    }

    cfg.out_inf << "Processed " << processed_cnt << " (of " << cfg.traj_ts_cnt() << ") configurations." << std::endl;
    cfg.out_inf << "Time: " << t.time() << " sec." << std::endl;

    return 0;
}