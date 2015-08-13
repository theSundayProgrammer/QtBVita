#include "bvboard.h"
#include <utility>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    BVBoard widget;
    widget.resize(300, 300);
    widget.show();

    return app.exec();
}




#include "main.moc"
