#ifndef EXTENDEDLIB_H
#define EXTENDEDLIB_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

class ExtendedLib : public QWidget
{
  Q_OBJECT
public:
  explicit ExtendedLib(QWidget *parent = nullptr);

signals:

public slots:

private:
  QHBoxLayout mainLayout;
  QPushButton *addInclude,
              *addLib;

private slots:
  void slotAddLib();
  void slotAddInclude();
};

#endif // EXTENDEDLIB_H
