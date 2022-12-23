#ifndef HealthPoints_H
#define HealthPoints_H
class HealthPoints
{
    public:
    explicit HealthPoints(int max_points=100);
    HealthPoints& operator+=(const HealthPoints&);
    HealthPoints& operator-=(const HealthPoints&);


    private:
    int m_hp;

    friend bool operator==(const HealthPoints&,const HealthPoints&);
    friend bool operator<(const HealthPoints&,const HealthPoints&);
    class InvalidArgument {};
};

HealthPoints operator+(const HealthPoints&,const HealthPoints&);
HealthPoints operator-(const HealthPoints&,const HealthPoints&);
bool operator!=(const HealthPoints&,const HealthPoints&);
bool operator>(const HealthPoints&,const HealthPoints&);
bool operator<=(const HealthPoints&,const HealthPoints&);
bool operator>=(const HealthPoints&,const HealthPoints&);
#endif