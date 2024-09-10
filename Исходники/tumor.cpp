int addInstance(const fs::path& instance_path, std::vector<VolumeVector<short>>& mrs, VolumeVector<unsigned char>& masks, VolumeVector<short>& gts, std::vector<std::vector<double>>& gmm_data, std::vector<int>& counts)
{
    const fs::path flair_path(instance_path / fs::path("VSD.Brain.XX.O.MR_Flair"));
    const fs::path t1_path(instance_path / fs::path("VSD.Brain.XX.O.MR_T1"));
    const fs::path t1c_path(instance_path / fs::path("VSD.Brain.XX.O.MR_T1c"));
    const fs::path t2_path(instance_path / fs::path("VSD.Brain.XX.O.MR_T2"));
    const fs::path gt_path(instance_path / fs::path("VSD.Brain_3more.XX.XX.OT"));

    const vector<fs::path> volume_paths =
    {
        flair_path,
        t1_path,
        t1c_path,
        t2_path
    };

    const VolumePtr<short> gt = readVolume<short>(findMHA(gt_path).string());
    gts.push_back(gt);
    VolumeVector<short> volumes;

    int width, height, depth;
    std::tie(width, height, depth) = getVolumeDimension<short>(gt);

    for (const fs::path& p : volume_paths)
    {
        volumes.push_back(readVolume<short>(findMHA(p).string()));
    }

    mrs.push_back(volumes);

    const short lower_thres = 1;
    const VolumePtr<unsigned char> mask = createMask<short>(volumes[0], lower_thres);
    masks.push_back(mask);

    const std::array<double, 5> rate = { 0.01, 0.6, 0.1, 1.0, 0.3 };
    int n_voxels = 0;
    for (int z = 0; z < depth; ++z)
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                itk::Index<3> index;
                index[0] = x;
                index[1] = y;
                index[2] = z;
                if (mask->GetPixel(index) == 0) continue;
                ++n_voxels;
                const short label = gt->GetPixel(index);
                assert(label <= 4);
                ++counts[label];
                const double p = (double)rand() / RAND_MAX;
                if (p > rate[label]) continue;
                for (int i = 0; i < 4; ++i)
                {
                    const double v = static_cast<double>(volumes[i]->GetPixel(index));
                    gmm_data[label].push_back(v);
                }
            }
        }
    }

    return n_voxels;
}