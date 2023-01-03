#ifndef HealthPoints_H
#define HealthPoints_H

#include <iostream>

#define MIN_HP 0

class HealthPoints {
public:
  HealthPoints(int max_points = 100);
  HealthPoints &operator+=(const HealthPoints &);
  // HealthPoints operator-() const;
  HealthPoints &operator-=(const HealthPoints &);
  class InvalidArgument {};

private:
  int m_hp;
  int m_maxHP;

  friend bool operator==(const HealthPoints &, const HealthPoints &);
  friend bool operator<(const HealthPoints &, const HealthPoints &);
  friend std::ostream &operator<<(std::ostream &, const HealthPoints &);
  friend HealthPoints operator+(const HealthPoints &, const HealthPoints &);
  // class InvalidArgument {};
};

// HealthPoints operator+(const HealthPoints &, const HealthPoints &);
HealthPoints operator-(const HealthPoints &, const HealthPoints &);
// HealthPoints operator-(const HealthPoints&);
bool operator!=(const HealthPoints &, const HealthPoints &);
bool operator>(const HealthPoints &, const HealthPoints &);
bool operator<=(const HealthPoints &, const HealthPoints &);
bool operator>=(const HealthPoints &, const HealthPoints &);
#endif
