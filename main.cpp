/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QMouseEvent>
#include <utility>
int absolute(int x, int y)
{
    return x>y ? x-y: y-x;
}

//! [0]
class LightWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool on READ isOn WRITE setOn)
public:
    LightWidget(int row, int col, bool visible, QWidget *parent = 0)
        :   QWidget(parent),
            m_color(Qt::black),
            m_on(visible),
            m_row(row),
            m_col(col),
            is_selected(false){}

    bool isOn() const
        { return m_on; }
    void setOn(bool on)
    {
        if (on == m_on)
            return;
        m_on = on;
        update();
    }
    bool isValidMove(LightWidget* w)
    {
        return ((absolute(m_row,w->m_row)==2 && m_col == w->m_col)||
                (absolute(m_col,w->m_col)==2 && m_row == w->m_row));

    }
    std::pair<int,int> getMidPoint(LightWidget *w)
    {
        return std::make_pair((m_row + w->m_row)/2, (m_col + w->m_col)/2);
    }

public slots:
    void turnOff() { setOn(false); }
    void turnOn() { setOn(true); }
    void reset() {is_selected = false;}
    bool isPeg() { return m_on;}
protected:
    virtual void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE
    {
        if (!m_on)
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
    void    mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE
    {

        if(m_on)
        {
            is_selected = true;
            this->repaint();
            emit selected(this);
        }else{
            emit selected(this);
        }

    }


    signals:
    void selected(LightWidget*);
//    void    mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE
//    {
//        m_color=Qt::red;
//        this->repaint();
//    }

private:
    QColor m_color;
    bool m_on;
    bool is_selected;
    int m_row,m_col;
};
//! [0]

//! [1]
bool IsValid(int i, int j)
{
    return (i>=2 && i<5) || (j>=2 && j<5);
}
//! [1]
//! [3]
class TrafficLight : public QWidget
{
    Q_OBJECT
public:
    TrafficLight(QWidget *parent = 0)
        : QWidget(parent),
          active(0)
    {
        QGridLayout *grid = new QGridLayout(this);
        for(int i=0; i<7; ++i)
            for(int j=0; j<7; ++j)
          {
                if(IsValid(i,j))
                {
                    LightWidget *red = new LightWidget(i,j,!(i==3 && j==3));
                    grid->addWidget(red,i,j,1,1);
                    red->connect(red,SIGNAL(selected(LightWidget*)), this, SLOT(onNewSelection(LightWidget*)));
                    board[i][j] = red;
                }
                else
                    board[i][j]=0;
         }
    }
private:
    bool IsEmpty(std::pair<int,int> pos)
    {
        return board[pos.first][pos.second]->isOn();
    }

private slots:
    void onNewSelection(LightWidget* cur)
    {
        if (cur->isPeg())
        {
            if (active)
            {
                active->reset();
                active->repaint();
            }
            active = cur;
        } else if (active && active->isValidMove(cur) && IsEmpty(active->getMidPoint(cur)) ) {
            cur->turnOn();
            active->turnOff();
            active->reset();
            std::pair<int,int> pos = active->getMidPoint(cur);
            board[pos.first][pos.second]->turnOff();
            active=0;
        }
    }
private:
    LightWidget* active;
    LightWidget* board[7][7];
};
//! [3]

//! [4]
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    TrafficLight widget;
    widget.resize(300, 300);
    widget.show();

    return app.exec();
}
//! [4]

#include "main.moc"
