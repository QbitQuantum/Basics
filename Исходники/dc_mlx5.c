ucs_status_t uct_dc_mlx5_ep_atomic_fadd64(uct_ep_h tl_ep, uint64_t add,
                                          uint64_t remote_addr, uct_rkey_t rkey,
                                          uint64_t *result, uct_completion_t *comp)
{
    return uct_dc_mlx5_ep_atomic(ucs_derived_of(tl_ep, uct_dc_mlx5_ep_t),
                                 MLX5_OPCODE_ATOMIC_FA, result, 0, sizeof(uint64_t),
                                 remote_addr, rkey, 0, 0, htonll(add), comp);
}