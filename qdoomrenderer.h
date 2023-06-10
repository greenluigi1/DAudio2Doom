#ifndef QDOOMRENDERER_H
#define QDOOMRENDERER_H

#include <QObject>
#include <QLabel>

class QDoomRenderer : public QLabel
{
public:
    QDoomRenderer();
    void RefreshImage();
private:
    QPixmap buffer;
};

#endif // QDOOMRENDERER_H
