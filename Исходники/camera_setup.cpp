CameraSetup::CameraSetup(ros::NodeHandle& nh, ros::NodeHandle& nh_private, QWidget *parent, Qt::WFlags flags) :
    QMainWindow(parent, flags), nh_(nh), nh_private_(nh_private), quit_threads_(false), broadcaster_(0)
{
  ui.setupUi(this);

  nh_private_.param("camera_n", camera_n_, 2);
  ROS_DEBUG("Total camera: %d", camera_n_);

  broadcaster_.resize(camera_n_);
  camera_parameter_.resize(camera_n_);
  camera_tf_.resize(camera_n_);

  ui.tableWidget->setRowCount(camera_n_*2);
  ui.tableWidget->setColumnCount(10);
  ui.tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Camera")));
  ui.tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Tx")));
  ui.tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Ty")));
  ui.tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Tz")));
  ui.tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("Rx")));
  ui.tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem(QString("Ry")));
  ui.tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem(QString("Rz")));
  ui.tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem(QString("Rw")));
  ui.tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem(QString("Source")));
  ui.tableWidget->setHorizontalHeaderItem(9, new QTableWidgetItem(QString("Target")));

  for (int i = 0; i < camera_n_; i++)
  {
    string camera_parameter_text;
    nh_private_.param((QString("camera_%1").arg(i)).toStdString(), camera_parameter_text, string(""));
    ROS_DEBUG("Camera %d parameter: %s", i, camera_parameter_text.c_str());
    QStringList tokens = QString(camera_parameter_text.c_str()).split(' ');
    ROS_DEBUG("Camera %d parameter count: %d", i, tokens.size());
    if(tokens.size() != 10)
    {
      ROS_ERROR("camera %d paparmeter count is not correct", i);
      continue;
    }

    int j = 0;
    foreach(QString text, tokens)
    {
      QTableWidgetItem* item = new QTableWidgetItem(text);
      Qt::ItemFlags f = item->flags() & ~Qt::ItemIsEditable;
      item->setFlags(f);
      ui.tableWidget->setItem(i*2, j, item);
      j++;
    }

    CameraParameter parameter;
    parameter.name = tokens[0].toStdString();
    parameter.tf.setOrigin(tf::Vector3(tokens[1].toDouble(), tokens[2].toDouble(), tokens[3].toDouble()));
    parameter.tf.setRotation(tf::Quaternion(tokens[4].toDouble(), tokens[5].toDouble(), tokens[6].toDouble(), tokens[7].toDouble()));
    parameter.source = tokens[8].toStdString();
    parameter.target = tokens[9].toStdString();
    camera_tf_[i] = parameter.tf;
    camera_parameter_[i] = parameter;

    ui.tableWidget->setItem(i*2 + 1, 1, new QTableWidgetItem("0"));
    ui.tableWidget->setItem(i*2 + 1, 2, new QTableWidgetItem("0"));
    ui.tableWidget->setItem(i*2 + 1, 3, new QTableWidgetItem("0"));
    ui.tableWidget->setItem(i*2 + 1, 4, new QTableWidgetItem("0"));
    ui.tableWidget->setItem(i*2 + 1, 5, new QTableWidgetItem("0"));
    ui.tableWidget->setItem(i*2 + 1, 6, new QTableWidgetItem("0"));
    ui.tableWidget->setItem(i*2 + 1, 7, new QTableWidgetItem());
    ui.tableWidget->setItem(i*2 + 1, 8, new QTableWidgetItem());
    ui.tableWidget->setItem(i*2 + 1, 9, new QTableWidgetItem());
    Qt::ItemFlags f = ui.tableWidget->item(i*2 + 1, 7)->flags() & ~Qt::ItemIsEditable;
    ui.tableWidget->item(i*2 + 1, 7)->setFlags(f);
    ui.tableWidget->item(i*2 + 1, 8)->setFlags(f);
    ui.tableWidget->item(i*2 + 1, 9)->setFlags(f);

    ui.tableWidget->setItemDelegateForRow(i*2+1, new DoubleSpinBoxDelegate());
  }