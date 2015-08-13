#include "bvboard.h"
#include <utility>


BVBoard::BVBoard(QWidget *parent)
    : QWidget(parent),
      active(0)
{
    QGridLayout *grid = new QGridLayout(this);
    for(int i=0; i<7; ++i)
        for(int j=0; j<7; ++j)
        {
            if(IsValid(i,j))
            {
                PegWidget *peg = new PegWidget(i,j,!(i==3 && j==3));
                grid->addWidget(peg,i,j,1,1);
                peg->connect(peg,SIGNAL(selected(PegWidget*)), this, SLOT(onNewSelection(PegWidget*)));
                board[i][j] = peg;
            }
            else
                board[i][j]=0;
        }
}


void BVBoard::onNewSelection(PegWidget *cur)
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
        cur->insert();
        active->remove();
        std::pair<int,int> pos = active->getMidPoint(cur);
        board[pos.first][pos.second]->remove();
        active=0;
    }
}



