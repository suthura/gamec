#include "spaceinwaders.h"
#include <QTimer>

CSpaceInwaders::CSpaceInwaders(QSize onScreenSize, QWidget *pParent)
    :QGraphicsView(pParent),m_onScreenSize(onScreenSize)
{
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);

    pScene->setSceneRect(0,0,m_onScreenSize.width(),m_onScreenSize.height());

    setBackgroundBrush(QBrush(QImage(":/Resources/SpaceInvadersBg.jpg")));

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);

    setStyleSheet("border-style:none");
}

void CSpaceInwaders::Run()
{
    scene()->clear();
    setCursor(Qt::BlankCursor);

    m_pCannon =new CCannon(EColor::Red);
    m_pCannon->setPos(m_onScreenSize.width()/2,m_onScreenSize.height()-gCannonSize.height());
    m_pCannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_pCannon->setFocus();
    scene()->addItem(m_pCannon);

    connect(m_pCannon, &CCannon::sigIncreaseScore,this,&CSpaceInwaders::onIncreaseScore);
    connect(m_pCannon, &CCannon::sigDecreseScore,this,&CSpaceInwaders::onDecreseScore);

    m_pPoints = new CPoints();
    scene()->addItem(m_pPoints);

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout,this,&CSpaceInwaders::onCreateEnemy);
    pTimer->start(2000);
}

void CSpaceInwaders::CheckPoints()
{
    if ((m_pPoints->GetScore())<0|| (m_pPoints->GetHealth()<=0)){
        m_pPoints->Reset();
        onGameOver();
    }
}

void CSpaceInwaders::keyPressEvent(QKeyEvent *pEvent)
{
    if(m_pCannon==nullptr)
        return;
    switch (pEvent->key()) {
    case Qt::Key_Left:
        if(m_pCannon->pos().x()>0)
            m_pCannon->setPos(m_pCannon->x()-20,m_pCannon->y());
        break;
    case Qt::Key_Right:
        if(m_pCannon->pos().x()+gCannonSize.width()< m_onScreenSize.width())
            m_pCannon->setPos(m_pCannon->x()+20,m_pCannon->y());
        break;

    case Qt::Key_Z:{
        int nColor = static_cast<int>(m_pCannon->GetColor());
        m_pCannon->SetColor(static_cast<EColor>(++nColor));
        break;
    }
    case Qt::Key_Space:
        m_pCannon->Shoot();
        break;
    }
}

void CSpaceInwaders::onCreateEnemy()
{
    int nPos = 100 + (rand()%m_onScreenSize.width()-100);
    int nColor = rand()%3;

    CAlien *pAlien = new CAlien(static_cast<EColor>(nColor));

    pAlien->setPos(nPos,0);

    scene()->addItem(pAlien);

    connect(pAlien,&CAlien::sigGameOver,this, &CSpaceInwaders::onGameOver);
    connect(pAlien, &CAlien::sigDecreseHealth,this,&CSpaceInwaders::onDecreaseHealth);


}

void CSpaceInwaders::onIncreaseScore()
{
    m_pPoints->IncreaseScore();
    CheckPoints();
}

void CSpaceInwaders::onDecreseScore()
{
    m_pPoints->DecreaseScore();
    CheckPoints();
}

void CSpaceInwaders::onDecreaseHealth()
{
    m_pPoints->DecreaseHealth();
    CheckPoints();
}

void CSpaceInwaders::onGameOver()
{
    close();
}
