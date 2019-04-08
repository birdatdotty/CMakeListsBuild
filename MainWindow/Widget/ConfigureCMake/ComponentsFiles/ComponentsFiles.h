#ifndef FILES_H
#define FILES_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QLabel>
#include <QPushButton>
#include <QStringListModel>
#include <QJsonArray>

class ComponentsFiles : public QWidget
{
  Q_OBJECT
  public:
    explicit ComponentsFiles(QWidget *parent = nullptr);

  public slots:
    void update(QJsonArray sources, QJsonArray headers);

  private:
    QVBoxLayout mainLayout;
    QListView* listView;
    QStringListModel* listModel;
    QLabel* label;
    QPushButton *addFile;

  private slots:
    void slotAddFile();
    void slotSetFiles(QStringList fileList);
};

#endif // FILES_H
