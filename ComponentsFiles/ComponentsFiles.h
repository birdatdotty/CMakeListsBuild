#ifndef FILES_H
#define FILES_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QLabel>
#include <QPushButton>
#include <QStringListModel>

class ComponentsFiles : public QWidget
{
  Q_OBJECT
  public:
    explicit ComponentsFiles(QWidget *parent = nullptr);
  
  private:
    QVBoxLayout mainLayout;
    QListView* listView;
    QStringListModel* listModel;
    QLabel* label;
    QPushButton *addFile;

  private slots:
    void slotAddFile();
};

#endif // FILES_H
