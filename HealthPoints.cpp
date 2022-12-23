#include "HealthPoints.h"

HealthPoints::HealthPoints(int max_points):
    m_hp(max_points)
    {
        if(max_points<=0)
            throw InvalidArgument();
    }

bool operator==(const HealthPoints& hp1,const HealthPoints& hp2)
{
    return hp1.m_hp==hp2.m_hp;
}

bool operator<(const HealthPoints& hp1,const HealthPoints& hp2)
{
    return hp1.m_hp<hp2.m_hp;
}

HealthPoints& HealthPoints::operator+=(const HealthPoints& hp)
{
    m_hp+=hp.m_hp;
    return *this;
}

HealthPoints& HealthPoints::operator-=(const HealthPoints& hp)
{
    m_hp-=hp.m_hp;
    return *this;
}

bool operator!=(const HealthPoints& hp1,const HealthPoints& hp2)
{
    return !(hp1==hp2);
}

bool operator>(const HealthPoints& hp1,const HealthPoints& hp2)
{
    return (hp2<hp1);
}

bool operator<=(const HealthPoints& hp1,const HealthPoints& hp2)
{
    return !(hp2<hp1);
}

bool operator>=(const HealthPoints& hp1,const HealthPoints& hp2)
{
    return (hp2<=hp1);
}



