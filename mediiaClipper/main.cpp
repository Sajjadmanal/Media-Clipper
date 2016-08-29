#include "videoplayer.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    VideoPlayer player;
    player.resize(1020, 720);
    player.show();

    return app.exec();
}
