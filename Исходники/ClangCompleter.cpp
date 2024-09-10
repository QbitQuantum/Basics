// Copy-ctor for unique_future is private in C++03 mode so we need to take it as
// an out param
void ClangCompleter::CreateSortingTask(
  const std::string &query,
  unique_future< AsyncCompletions > &future ) {
  // Careful! The code in this function may burn your eyes.

  function< CompletionDatas( const CompletionDatas & ) >
  sort_candidates_for_query_functor =
    bind( &ClangCompleter::SortCandidatesForQuery,
          boost::ref( *this ),
          query,
          _1 );

  function< CompletionDatas() > operate_on_completion_data_functor =
    bind( &ClangResultsCache::OperateOnCompletionDatas< CompletionDatas >,
          boost::cref( latest_clang_results_ ),
          boost::move( sort_candidates_for_query_functor ) );

  shared_ptr< packaged_task< AsyncCompletions > > task =
    make_shared< packaged_task< AsyncCompletions > >(
      bind( ReturnValueAsShared< std::vector< CompletionData > >,
            boost::move( operate_on_completion_data_functor ) ) );

  future = task->get_future();
  sorting_task_.Set( task );
}