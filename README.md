# CMakeListsBuild
Utils for create qt project (only hierarchic) with cmake

Данный проект для создания CMakeList.txt по готовым исхожникам (*.cpp *.h). Я постарался сделать иерархическую систему, для чего я создаю статические библиотеки во вложенных папках ( *.a ):

для примера лежит testcmake, в нем нужно создать два CMakeList.txt

  1.1. example1/Example/Button1 - указать компонент Widgets, выбрать оба файла и выбрать режим сборки статической библиотеки

  1.2. example1/Example/Button2 - указать компонент Widgets, выбрать оба файла и выбрать режим сборки статической библиотеки

  1.3. example1/Example - указать компонент Widgets, выбрать оба файла и выбрать режим сборки статической библиотеки
  
  1.4. example1 - указать компонент Widgets, выбрать main.cc, режим сборки "приложение", а также добавить подпроект Widget

  После можно собрать проект
  
  2.1. cd .../example1/
  
  2.2. mkdir build
  
  2.3. cd build
  
  2.4. cmake ..
  
  2.5. make

Извеняюсь за неочевидность и глюченность.

Позже я реализую нормальную систему добавления библиотек:)
