Region RegionFactory::
        operator()(const Reference& ref) const
{
    Position a, b;
    // For integers 'i': "2 to the power of 'i'" == powf(2.f, i) == ldexpf(1.f, i)
    Position blockSize( block_size_.texels_per_row () * ldexpf(1.f,ref.log2_samples_size[0]),
                        block_size_.texels_per_column () * ldexpf(1.f,ref.log2_samples_size[1]));
    a.time = blockSize.time * ref.block_index[0];
    a.scale = blockSize.scale * ref.block_index[1];
    b.time = a.time + blockSize.time;
    b.scale = a.scale + blockSize.scale;

    return Region(a,b);
}