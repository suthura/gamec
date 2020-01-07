#ifndef CSPACEINWADERS_H
#define CSPACEINWADERS_H

#include "components.h"

#include <QPointer>
#include<QGraphicsView>
#include<QKeyEvent>

class CSpaceInwaders : public QGraphicsView
{
    Q_OBJECT
public:
    CSpaceInwaders(QSize onScreenSize , QWidget* pParent = nullptr);

    void Run();
    void CheckPoints();

protected:
    void keyPressEvent(QKeyEvent* pEvent) override;

public slots:
    void onCreateEnemy();
    void onIncreaseScore();
    void onDecreseScore();
    void onDecreaseHealth();
    void onGameOver();

private:
    CCannon*    m_pCannon = nullptr;
    CPoints*    m_pPoints = nullptr;
    QSize       m_onScreenSize;

};

#endif // CSPACEINWADERS_H
