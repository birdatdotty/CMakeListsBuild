#ifndef CMAKELISTSBUILD_H
#define CMAKELISTSBUILD_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

class CMakeListsBuild : public QWidget
{
  Q_OBJECT
public:
  explicit CMakeListsBuild(QWidget *parent = nullptr);
  ~CMakeListsBuild();

signals:

public slots:

private:
  QLabel* label;
  QLineEdit* filePath;
  QVBoxLayout mainLayout;
  QPushButton *create;

  QStringList pkgs;
  QStringList files;

  // App, StaticLib, DinamicLib
  QString buildCtxApp(QJsonObject json);
  QString buildCtxStaticLib(QJsonObject json);
  QString buildCtxDinamicLib(QJsonObject json);

private slots:
  void update();
  void btnClick();
};

#endif // CMAKELISTSBUILD_H
