Remotes unmap_owners(
    Mesh* old_mesh, Int ent_dim, LOs new_ents2old_ents, LOs old_ents2new_ents) {
  auto old_copies2old_owners = old_mesh->ask_dist(ent_dim);
  auto old_owners2old_copies = old_copies2old_owners.invert();
  auto old_copies2new_owners = old_owners2old_copies.exch(old_ents2new_ents, 1);
  auto new_ents2new_owners = unmap(new_ents2old_ents, old_copies2new_owners, 1);
  auto old_own_ranks = old_mesh->ask_owners(ent_dim).ranks;
  auto new_own_ranks = unmap(new_ents2old_ents, old_own_ranks, 1);
  return Remotes(new_own_ranks, new_ents2new_owners);
}