#ifndef PEGWIDGET
#define PEGWIDGET
#include <QtWidgets>
#include <QMouseEvent>
#include <utility>


class PegWidget : public QWidget
{
    Q_OBJECT

public:
    PegWidget(int row, int col, bool visible, QWidget *parent = 0);

    bool isPresent() const;
    void setOn(bool on);
    bool isValidMove(PegWidget* w);
    std::pair<int,int> getMidPoint(PegWidget *w);

    void remove();
    void insert();
    void reset();
    bool isPeg();
protected:
    virtual void paintEvent(QPaintEvent *);
    void    mousePressEvent(QMouseEvent *event);


signals:
    void selected(PegWidget*);


private:
    QColor m_color;
    bool m_present;
    bool is_selected;
    int m_row,m_col;
};


inline int absolute(int x, int y)
{
    return x>y ? x-y: y-x;
}



inline PegWidget::PegWidget(int row, int col, bool visible, QWidget *parent)
    :   QWidget(parent),
      m_color(Qt::black),
      m_present(visible),
      m_row(row),
      m_col(col),
      is_selected(false){}


inline bool PegWidget::isPresent() const
{ return m_present; }


inline void PegWidget::setOn(bool on)
{
    if (on == m_present)
        return;
    m_present = on;
    update();
}


inline bool PegWidget::isValidMove(PegWidget *w)
{
    return ((absolute(m_row,w->m_row)==2 && m_col == w->m_col)||
            (absolute(m_col,w->m_col)==2 && m_row == w->m_row));

}


inline std::pair<int, int> PegWidget::getMidPoint(PegWidget *w)
{
    return std::make_pair((m_row + w->m_row)/2, (m_col + w->m_col)/2);
}


inline void PegWidget::remove() { setOn(false); reset();  }


inline void PegWidget::insert() { setOn(true); }


inline void PegWidget::reset() {is_selected = false;}


inline bool PegWidget::isPeg() { return m_present;}


#endif // PEGWIDGET

