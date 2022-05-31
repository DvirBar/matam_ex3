#include "HealthPoints.h"
#include <iostream>


HealthPoints::HealthPoints(const int maxHP) {
    if(maxHP <= 0) {
        throw InvalidArgument();
    }
    
    m_maxHP = maxHP;
    m_currentHP = maxHP;
}


HealthPoints& HealthPoints::operator=(const HealthPoints& healthPoints) {
    if(this == &healthPoints) {
        return *this;
    }

    m_maxHP = healthPoints.m_maxHP;
    m_currentHP = healthPoints.m_currentHP;
    return *this;
}


HealthPoints& HealthPoints::operator+=(const int pointsToAdd) {
    if(m_currentHP + pointsToAdd > m_maxHP) {
        m_currentHP = m_maxHP;
    }

    else if(m_currentHP + pointsToAdd < 0) {
        m_currentHP = 0;
    }
    
    else {
        m_currentHP += pointsToAdd;
    }

    return *this;
}


HealthPoints& HealthPoints::operator-=(const int pointsToSubtract) {
    if(m_currentHP - pointsToSubtract < 0) {
        m_currentHP = 0;
    }

    else if(m_currentHP - pointsToSubtract > m_maxHP) {
        m_currentHP = m_maxHP;
    }
    
    else {
        m_currentHP -= pointsToSubtract;
    }
    
    return *this;
}


bool operator==(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2) {
    return healthPoints1.m_currentHP == healthPoints2.m_currentHP;
}


bool operator<(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2) {
    return healthPoints1.m_currentHP < healthPoints2.m_currentHP;
}


std::ostream& operator<<(std::ostream& output, const HealthPoints& healthPoints) {
    output << healthPoints.m_currentHP << "(" << healthPoints.m_maxHP << ")";
    return output;
}


HealthPoints operator+(const int pointsToAdd, const HealthPoints& healthPoints) {
    HealthPoints result = healthPoints;
    return result += pointsToAdd;
}


HealthPoints operator+(const HealthPoints& healthPoints, const int pointsToAdd) {
    HealthPoints result = healthPoints;
    return result += pointsToAdd;
}


HealthPoints operator-(const HealthPoints& healthPoints, const int pointToSubtract) {
    HealthPoints result = healthPoints;
    return result -= pointToSubtract;
}


bool operator!=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2) {
    return !(healthPoints1 == healthPoints2);
}


bool operator<=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2) {
    return !(healthPoints2 < healthPoints1);
}


bool operator>(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2) {
    return healthPoints2 < healthPoints1;
}


bool operator>=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2) {
    return healthPoints2 <= healthPoints1;
}

