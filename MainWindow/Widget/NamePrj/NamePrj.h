#ifndef NAMEPRJ_H
#define NAMEPRJ_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class Config;

class NamePrj: public QWidget
{
  Q_OBJECT
  public:
    NamePrj(Config *config, QWidget *parent);

  private:
    QHBoxLayout mainLayout;
    QLabel *lPrjPath, *lNamePrj;
    QLineEdit *ePrjPath, *eNamePrj;
    QPushButton *btnPrjPath;

};

#endif // NAMEPRJ_H
