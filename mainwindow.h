#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QFileSystemModel>
#include <QMainWindow>
#include <QTreeView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private slots:
  void on_actionOpen_triggered();

  void on_actionExit_triggered();

 private:
  Ui::MainWindow *ui;
  QFileSystemModel *fileSystemModel = new QFileSystemModel;
  QTreeView *fileSystemTree = new QTreeView(this);

  static void configureFileExplorerDockWidgetAreasAndFeatures(QDockWidget* dockWidget);
};
#endif  // MAINWINDOW_H
