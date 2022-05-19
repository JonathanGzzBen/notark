#include "mainwindow.h"

#include <QDockWidget>
#include <QFileSystemModel>
#include <QTreeView>

#include "qheaderview.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setCentralWidget(ui->plainTextEdit);

  auto fileSystemModel = new QFileSystemModel;
  fileSystemModel->setRootPath(QDir::currentPath());
  auto fileSystemTree = new QTreeView(this);
  fileSystemTree->setModel(fileSystemModel);
  for(int i{1}; i < fileSystemTree->header()->count(); i++) {
    fileSystemTree->header()->hideSection(i);
  }

  auto fileExplorerDockWidget = new QDockWidget(this);
  fileExplorerDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  fileExplorerDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  fileExplorerDockWidget->setWidget(fileSystemTree);
  fileExplorerDockWidget->setWindowTitle("File Explorer");
  addDockWidget(Qt::LeftDockWidgetArea, fileExplorerDockWidget);
}

MainWindow::~MainWindow() { delete ui; }
