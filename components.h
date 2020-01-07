#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "settings.h"

#include<QGraphicsPixmapItem>
#include<QGraphicsSimpleTextItem>
#include<QGraphicsItem>
#include<QKeyEvent>

enum class EColor{
    Red,Pink,Blue
};

class CBullet;

class CCannon : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CCannon(EColor eColor,QGraphicsItem* pParent = nullptr);
    void Shoot();

    EColor GetColor() const;
    void SetColor(EColor eColor);

signals:
    void sigIncreaseScore();
    void sigDecreseScore();

private:
    EColor m_eColor;
};

//Alien
class CAlien : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    CAlien(EColor eColor,QGraphicsItem*pParent = nullptr);
    EColor GetColor() const;
    void SetColor(EColor eColor);

signals:
    void sigDecreseHealth();
    void sigGameOver();

public slots:
    void onMove();
private:
    EColor m_eColor;
};

//Bullet
class CBullet : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    CBullet(EColor eColor,QGraphicsItem*   pParent = nullptr);
    EColor GetColor() const;
    void SetColor(EColor eColor);
signals:
    void sigIncreaseScore();
    void sigDecreseScore();
public slots:
    void onMove();
private:
    EColor m_eColor;
};

//points
class CPoints : public QGraphicsTextItem{

public:
    CPoints(QGraphicsItem *pParent=nullptr);

    void IncreaseScore();
    void DecreaseScore();
    void DecreaseHealth();

    int GetHealth() const;
    int GetScore() const;

    void Reset();

private:
    int m_nHealth = gMaxHealth;
    int m_nScore = 0;
};










#endif // COMPONENTS_H
