# CMakeListsBuild
Utils for create qt project (only hierarchic) with cmake

Данный проект для создания CMakeList.txt по готовым исхожникам (*.cpp *.h). Я постарался сделать иерархическую систему:
для примера лежит testcmake, в нем нужно создать два CMakeList.txt
1.1. testcmake/Widget/ - указать компонент Widgets, выбрать оба файла и выбрать режим сборки статической библиотеки
1.2. testcmake/ - указать компонент Widgets, выбрать main.cc, режим сборки "приложение", а также добавить подпроект Widget
# После можно собрать проект
2.1. cd .../testcmake/
2.2. mkdir build
2.3. cd build
2.4. cmake ..
2.5. make
