inline void spawn(
  stackless,
  actor<stackless>& sire, F f, SpawnHandler h,
  cache_pool* user, link_type type, std::size_t stack_size
  )
{
  user->get_strand().post(
    boost::bind(
      &detail::make_stackless_actor,
      sire.get_aid(), user,
      make_actor_func<stackless>(f), stack_size
      )
    );

  match mach;
  mach.match_list_.push_back(detail::msg_new_actor);
  sire.recv(
    boost::bind(
      &handle_spawn, _1, _2, _3,
      type, spawn_handler_t(h)
      ),
    mach
    );
}