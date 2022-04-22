#include "mainwindow.h"

#include <QDockWidget>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setCentralWidget(ui->plainTextEdit);
  QDockWidget *dockWidget = new QDockWidget(tr("Dock Widget"), this);
  dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  dockWidget->setWidget(ui->fileExplorerTreeWidget);
  dockWidget->setWindowTitle("File Explorer");
  addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
}

MainWindow::~MainWindow() { delete ui; }
