#pragma once

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>

class JoystickPoint : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(float horizontalPosition READ horizontalPosition WRITE setHorizontalPosition NOTIFY positionChanged)
    Q_PROPERTY(float verticalPosition READ verticalPosition WRITE setVerticalPosition NOTIFY positionChanged)

public:
    JoystickPoint();

    float horizontalPosition() const { return _horizontalPosition; }
    float verticalPosition() const { return _verticalPosition; }
    void setHorizontalPosition(float h);
    void setVerticalPosition(float v);

public slots:
    void render();
    void synchronize();
    void cleanup();

signals:
    void positionChanged();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:

    float _horizontalPosition;
    float _verticalPosition;
    QSize _viewportSize;
    QOpenGLShaderProgram *_shaderProgram;
};
