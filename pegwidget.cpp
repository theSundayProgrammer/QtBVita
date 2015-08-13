#include "pegwidget.h"
void PegWidget::paintEvent(QPaintEvent *) Q_DECL_OVERRIDE
{
    if (!m_present)
        return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int w = width();
    int h = height();
    painter.setBrush(is_selected?Qt::gray:m_color);
    painter.drawEllipse(0, 0, w,h);
    if(is_selected)
    {
        painter.setBrush(m_color);
        w -=2;
        h -= 2;
        painter.drawEllipse(2, 2, w,h);

    }
}


void PegWidget::mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE
{

    if(m_present)
    {
        is_selected = true;
        this->repaint();
        emit selected(this);
    }else{
        emit selected(this);
    }

}
