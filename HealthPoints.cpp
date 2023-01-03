#include "HealthPoints.h"

// constructor's implimintation
HealthPoints::HealthPoints(int max_points)
    : m_hp(max_points), m_maxHP(max_points) {
  if (max_points <= MIN_HP)
    throw HealthPoints::InvalidArgument();
}

// arithmetic operators overloading
HealthPoints &HealthPoints::operator+=(const HealthPoints &hp1) {
  m_hp += hp1.m_hp;
  if (m_hp < MIN_HP) {
    m_hp = MIN_HP;
  } else if (m_hp > m_maxHP) {
    m_hp = m_maxHP;
  }
  return *this;
}

HealthPoints operator+(const HealthPoints &hp1, const HealthPoints &hp2) {
  int max_hp_of_sum = std::min(hp1.m_maxHP, hp2.m_maxHP);
  HealthPoints result(max_hp_of_sum);
  result.m_hp = hp1.m_hp;
  return (result += hp2);
}

// HealthPoints HealthPoints::operator-() const { return HealthPoints(-m_hp); }

HealthPoints &HealthPoints::operator-=(const HealthPoints &hp1) {
  m_hp -= hp1.m_hp;
  if (m_hp < MIN_HP) {
    m_hp = MIN_HP;
  } else if (m_hp > m_maxHP) {
    m_hp = m_maxHP;
  }
  return *this;
}

HealthPoints operator-(const HealthPoints &hp1, const HealthPoints &hp2) {
  HealthPoints result(hp1);
  return (result -= hp2);
}

// boolean operators overloading

bool operator==(const HealthPoints &hp1, const HealthPoints &hp2) {
  return hp1.m_hp == hp2.m_hp;
}

bool operator<(const HealthPoints &hp1, const HealthPoints &hp2) {
  return hp1.m_hp < hp2.m_hp;
}

bool operator!=(const HealthPoints &hp1, const HealthPoints &hp2) {
  return !(hp1 == hp2);
}

bool operator>(const HealthPoints &hp1, const HealthPoints &hp2) {
  return (hp2 < hp1);
}

bool operator<=(const HealthPoints &hp1, const HealthPoints &hp2) {
  return !(hp2 < hp1);
}

bool operator>=(const HealthPoints &hp1, const HealthPoints &hp2) {
  return (hp2 <= hp1);
}

// iostream operator overloading
std::ostream &operator<<(std::ostream &os, const HealthPoints &hp) {
  os << hp.m_hp << '(' << hp.m_maxHP << ')';
  return os;
}
