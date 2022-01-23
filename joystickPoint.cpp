
#include "joystickPoint.h"
#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include <qtimer.h>

const float PI = 3.14159265359f;
const float RADIANS_IN_DEGREE = PI / 180.0f;

JoystickPoint::JoystickPoint():
                                _shaderProgram(0),
                                _horizontalPosition(0),
                                _verticalPosition(0)
{
    connect(this,
            SIGNAL(windowChanged(QQuickWindow*)),
            this,
            SLOT(handleWindowChanged(QQuickWindow*)));
}

void JoystickPoint::setHorizontalPosition(float horizontalPosition)
{
    _horizontalPosition = horizontalPosition;

    emit positionChanged();

    if (window())
        window()->update();
}

void JoystickPoint::setVerticalPosition(float verticalPosition)
{
    _verticalPosition = verticalPosition;

    emit positionChanged();

    if (window())
        window()->update();
}

void JoystickPoint::handleWindowChanged(QQuickWindow *window)
{
    if (window) {
        connect(window,
                SIGNAL(beforeSynchronizing()),
                this,
                SLOT(synchronize()),
                Qt::DirectConnection);

        connect(window,
                SIGNAL(sceneGraphInvalidated()),
                this,
                SLOT(cleanup()),
                Qt::DirectConnection);

        window->setClearBeforeRendering(false);
    }
}

void JoystickPoint::cleanup()
{
    delete _shaderProgram;
    _shaderProgram = 0;

    _horizontalPosition = 0;
    _verticalPosition = 0;
}

void JoystickPoint::synchronize()
{
    connect(window(),
            SIGNAL(beforeRendering()),
            this,
            SLOT(render()),
            Qt::DirectConnection);

    _viewportSize = window()->size() * window()->devicePixelRatio();
}

void JoystickPoint::render()
{
    if (!_shaderProgram)
    {
        _shaderProgram = new QOpenGLShaderProgram();
        _shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                                "precision mediump float;"
                                                "attribute vec2 positionAttrib;"
                                                "uniform vec2 positionUniform;"
                                                "uniform float scaleUniform;"
                                                "uniform vec2 screenDimensionsUniform;"
                                                "void main()"
                                                "{"
                                                    "gl_Position = vec4((positionAttrib.x * scaleUniform + positionUniform.x) * (2.0 / screenDimensionsUniform[0]),"
                                                                        "(positionAttrib.y * scaleUniform + positionUniform.y) * (2.0 / screenDimensionsUniform[1]),"
                                                                        "0.0,"
                                                                        "1.0);"
                                                "}");

        _shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                                "precision mediump float;"
                                                "void main()"
                                                "{"
                                                    "gl_FragColor = vec4(0.0, 0.0, 0.5, 1.0);"
                                                "}");

        _shaderProgram->bindAttributeLocation("positionAttrib", 0);
    }

    _shaderProgram->bind();
    _shaderProgram->enableAttributeArray(0);

    const float radius = 50.0f;

    if((_horizontalPosition + radius) > _viewportSize.width() / 2.0f)
        _horizontalPosition = _viewportSize.width() / 2.0f - radius;

    if((_horizontalPosition - radius) < -(_viewportSize.width() / 2.0f))
        _horizontalPosition = -(_viewportSize.width() / 2.0f) + radius;

    if((_verticalPosition + radius) > _viewportSize.height() / 2.0f)
        _verticalPosition = _viewportSize.height() / 2.0f - radius;

    if((_verticalPosition - radius) < -(_viewportSize.height() / 2.0f))
        _verticalPosition = -(_viewportSize.height() / 2.0f) + radius;

    _shaderProgram->setUniformValue("scaleUniform", radius);
    _shaderProgram->setUniformValue("positionUniform",QVector2D(_horizontalPosition,_verticalPosition));
    _shaderProgram->setUniformValue("screenDimensionsUniform",QVector2D(_viewportSize.width(),
                                                                        _viewportSize.height()));

    QVector2D circlePoints[361];
    QVector2D* begin = &circlePoints[1];

    for(unsigned short i = 0; i < 360; ++i)
    {
        begin[i].setX(cosf(static_cast<float>(i) * RADIANS_IN_DEGREE));
        begin[i].setY(sinf(static_cast<float>(i) * RADIANS_IN_DEGREE));
    }

    circlePoints[360].setX(begin[0].x());
    circlePoints[360].setY(begin[0].y());

    _shaderProgram->setAttributeArray(0,
                                    GL_FLOAT,
                                    circlePoints,
                                    2);

    glViewport(0,
               0,
               _viewportSize.width(),
               _viewportSize.height());

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 361);

    _shaderProgram->disableAttributeArray(0);
    _shaderProgram->release();
}
