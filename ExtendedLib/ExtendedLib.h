#ifndef EXTENDEDLIB_H
#define EXTENDEDLIB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QLabel>
#include <QPushButton>
#include <QStringListModel>
#include <QSet>

class ExtendedLib : public QWidget
{
  Q_OBJECT
  public:
    explicit ExtendedLib(QWidget *parent = nullptr);

  private:
    QVBoxLayout mainLayout;
    QListView* listView;
    QStringListModel* listModel;
    QLabel* label;
    QPushButton *addFile;
    QSet<QString> pkgList;

  private slots:
    void slotAddFile();
};

#endif // EXTENDEDLIB_H
