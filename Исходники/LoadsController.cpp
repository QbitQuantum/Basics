void LoadsController::onRemoveObject(openstudio::model::ModelObject modelObject)
{
  boost::optional<model::SpaceLoadDefinition> spaceLoadDefinition = modelObject.optionalCast<model::SpaceLoadDefinition>();
  if (spaceLoadDefinition){

    unsigned numInstances = spaceLoadDefinition->instances().size();
    if (numInstances > 0){
      QMessageBox msgBox(subTabView());
      msgBox.setText("There are " + QString::number(numInstances) + " instances that reference this definition.");
      msgBox.setInformativeText("Do you want to remove this definition and all of its instances?");
      msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
      msgBox.setDefaultButton(QMessageBox::Yes);
      int ret = msgBox.exec();
      if (ret == QMessageBox::No){
        return;
      }
    }
    modelObject.remove();
  }
}