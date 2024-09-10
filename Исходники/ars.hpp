 void generate(std::array<M128I<U>, Rp1> &rk,
               const M128I<std::uint64_t> &weyl, std::true_type) const
 {
     std::get<N>(rk) =
         _mm_add_epi64(std::get<N - 1>(rk).value(), weyl.value());
     generate<N + 1>(rk, weyl, std::integral_constant<bool, N + 1 < Rp1>());
 }