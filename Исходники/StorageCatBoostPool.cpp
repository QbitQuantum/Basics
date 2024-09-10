StorageCatBoostPool::StorageCatBoostPool(const Context & context,
                                         String column_description_file_name_,
                                         String data_description_file_name_)
        : column_description_file_name(std::move(column_description_file_name_)),
          data_description_file_name(std::move(data_description_file_name_))
{
    auto base_path = canonicalPath(context.getPath());
    column_description_file_name = resolvePath(base_path, std::move(column_description_file_name));
    data_description_file_name = resolvePath(base_path, std::move(data_description_file_name));
    if (context.getApplicationType() == Context::ApplicationType::SERVER)
    {
        const auto & base_path_str = base_path.string();
        checkCreationIsAllowed(base_path_str, column_description_file_name);
        checkCreationIsAllowed(base_path_str, data_description_file_name);
    }

    parseColumnDescription();
    createSampleBlockAndColumns();
}