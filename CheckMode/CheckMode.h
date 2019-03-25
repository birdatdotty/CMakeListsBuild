#ifndef CHECKMODE_H
#define CHECKMODE_H

#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CheckMode : public QWidget
{
  enum chMode {App, StaticLib, DinamicLib};
  Q_OBJECT
  public:
    explicit CheckMode(QWidget *parent = nullptr);

  signals:

  public slots:

  private:
    chMode mode;
    QVBoxLayout mainLayout;
    QHBoxLayout radiohBox;

    QGroupBox *groupBox;
    QRadioButton *radioApp,
                 *radioStaticLib,
                 *radioDinamicLib;

  private slots:
    void selectRadioApp();
    void selectRadioStaticLib();
    void selectRadioDinamicLib();
};

#endif // CHECKMODE_H
