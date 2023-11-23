#include <QApplication>
#include <QProxyStyle>

#include "mainwindow.h"
#include "qcustomplot.h"

class Style_tweaks : public QProxyStyle
{
    public:

        void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                           QPainter *painter, const QWidget *widget) const
        {
            /* do not draw focus rectangles - this permits modern styling */
            if (element == QStyle::PE_FrameFocusRect)
                return;

            QProxyStyle::drawPrimitive(element, option, painter, widget);
        }
};


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MainWindow w;
  a.setStyle(new Style_tweaks);

  w.show();

  return a.exec();
}
