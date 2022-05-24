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
  connect(fileSystemTree->selectionModel(),
          &QItemSelectionModel::selectionChanged, this,
          &MainWindow::fileSelected);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpen_triggered() {
  workingDirectory =
      QFileDialog::getExistingDirectory(this, "Select a directory");
  fileSystemTree->setRootIndex(fileSystemModel->setRootPath(workingDirectory));
}

void MainWindow::on_actionExit_triggered() { QApplication::quit(); }

void MainWindow::configureFileExplorerDockWidgetAreasAndFeatures(
    QDockWidget* dockWidget) {
  dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dockWidget->setFeatures(QDockWidget::DockWidgetMovable |
                          QDockWidget::DockWidgetFloatable);
}

void MainWindow::fileSelected(const QItemSelection& news,  // not used
                              const QItemSelection& olds) {
  auto model = static_cast<QFileSystemModel>(fileSystemTree->model());
  auto path{model.filePath(fileSystemTree->currentIndex())};
  if (!path.endsWith(".md")) return;
  if (QFileInfo fileinfo{path}; fileinfo.isDir()) return;

  QFile file{path};
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::warning(this, "Could not open file " + path,
                         file.errorString());
    return;
  }
  QTextStream stream{&file};
  ui->plainTextEdit->setText(stream.readAll());
  file.close();
}
