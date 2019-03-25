#ifndef PROBUILD_H
#define PROBUILD_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>


class ProBuild : public QWidget
{
  Q_OBJECT
public:
  explicit ProBuild(QWidget *parent = nullptr);
  ~ProBuild();

signals:

public slots:

private:
  QLabel* label;
  QLineEdit* filePath;
  QVBoxLayout mainLayout;
  QPushButton *create;

  QStringList pkgs;
  QStringList files;

  QString buildCtx();
};

#endif // PROBUILD_H
