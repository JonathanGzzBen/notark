#include "mainwindow.h"

#include <QDockWidget>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QTreeView>

#include "qheaderview.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setCentralWidget(ui->plainTextEdit);

  fileSystemTree->setModel(fileSystemModel);
  fileSystemTree->setRootIndex(
      fileSystemModel->setRootPath(QDir::currentPath()));
  for (int i{1}; i < fileSystemTree->header()->count(); i++) {
    fileSystemTree->header()->hideSection(i);
  }

  auto fileExplorerDockWidget = new QDockWidget(this);
  configureFileExplorerDockWidgetAreasAndFeatures(fileExplorerDockWidget);
  fileExplorerDockWidget->setWidget(fileSystemTree);
  fileExplorerDockWidget->setWindowTitle("File Explorer");
  addDockWidget(Qt::LeftDockWidgetArea, fileExplorerDockWidget);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpen_triggered() {
  QString path{QFileDialog::getExistingDirectory(this, "Select a directory")};
  fileSystemTree->setRootIndex(fileSystemModel->setRootPath(path));
  ui->plainTextEdit->setPlainText(path);
}

void MainWindow::on_actionExit_triggered() { QApplication::quit(); }

void MainWindow::configureFileExplorerDockWidgetAreasAndFeatures(QDockWidget* dockWidget) {
  dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dockWidget->setFeatures(QDockWidget::DockWidgetMovable |
                          QDockWidget::DockWidgetFloatable);
}
