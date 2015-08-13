#ifndef BVBOARD
#define BVBOARD
#include "pegwidget.h"
#include <utility>

class BVBoard : public QWidget
{
    Q_OBJECT
public:
    BVBoard(QWidget *parent = 0);
private:
    bool IsEmpty(std::pair<int,int> pos);

private slots:
    void onNewSelection(PegWidget* cur);
private:
    PegWidget* active;
    PegWidget* board[7][7];
};
inline bool BVBoard::IsEmpty(std::pair<int, int> pos)
{
    return board[pos.first][pos.second]->isPresent();
}
inline bool IsValid(int i, int j)
{
    return (i>=2 && i<5) || (j>=2 && j<5);
}

#endif // BVBOARD

