
#ifndef MATAM_EX2_HEALTHPOINTS_H
#define MATAM_EX2_HEALTHPOINTS_H
#include <iostream>

const int DEFAULT_MAXHP = 100;

class HealthPoints {
public:

    /**
     * Constructor Health Points Class
     *
     * @param maxHP - maxHP of the object. initializes m_currentHP and m_maxHP to parameter's value.
     * Throws an "Invalid Argument" exception upon non-natural value.
     */
    HealthPoints(const int maxHP = DEFAULT_MAXHP);

    HealthPoints(const HealthPoints& healthPoints) = default;

    /**
     * Health Points Class Assignment Operator
     *
     * Copies every parameter of the given Health Points Object to "this" object.
     * @param healthPoints - Health Points object to assign
     * @return
     *      This Player object after assignment.
     */
    HealthPoints& operator=(const HealthPoints& healthPoints);


    /**
     * Adds given points to the m_currentHP parameter to a maximum of m_maxHP or to a minimum of 0 m_currentHP.
     * @param pointsToAdd - Given points to add.
     * @return
     *      reference to updated This object after addition.
     */
    HealthPoints& operator+=(const int pointsToAdd);

    /**
     * Subtracts given points from the m_currentHP parameter to a maximum of m_maxHP or to a minimum of 0 m_currentHP.
     * @param pointsToSubtract - Given points to subtract
     * @return
     *      reference to updated This object after addition.
     */
    HealthPoints& operator-=(const int pointsToSubtract);

    class InvalidArgument {};

private:
    int m_maxHP;
    int m_currentHP;

    /**
     * Compares between 2 Health Points objects' m_currentHP parameter
     *
     * @param healthPoints1 - First Health Points object
     * @param healthPoints2 - Second Health Points object
     * @return
     *      - true - if said parameters are the same
     *      - false - else
     */
    friend bool operator==(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);

    /**
     * Determines if first Health Points object's m_currentHP is less than the second's.
     *
     * @param healthPoints1 - First Health Points object
     * @param healthPoints2 - Second Health Points object
     * @return
     *      true - if the above statement is true
     *      false - else
     */
    friend bool operator<(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);

    /**
     * Outputs the object in given structure: <m_currentHP>(<m_maxHP>)
     *
     * @param output - ostream object to whom the object is outputted.
     * @param healthPoints - the object that's outputted
     * @return
     *      an ostream output containing the object output
     */
    friend std::ostream& operator<<(std::ostream& output, const HealthPoints& healthPoints);
};

// ------------------------------ HEALTH POINTS ADDITIONAL ARITHMETICAL OPERATORS ------------------------------ //

HealthPoints operator+(const int pointsToAdd, const HealthPoints& healthPoints);

HealthPoints operator+(const HealthPoints& healthPoints, const int pointsToAdd);

HealthPoints operator-(const HealthPoints& healthPoints, const int pointToSubtract);

// ------------------------------ HEALTH POINTS ADDITIONAL BOOLEAN OPERATORS ------------------------------ //

/**
 * Compares between 2 Health Points objects' m_currentHP parameter
 *
 * @param healthPoints1 - First Health Points object
 * @param healthPoints2 - Second Health Points object
 * @return
 *      - true - if said parameters are different
 *      - false - else
 */
bool operator!=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);


/**
 * Determines if first Health Points object's m_currentHP is less than or equal to the second's.
 *
 * @param healthPoints1 - First Health Points object
 * @param healthPoints2 - Second Health Points object
 * @return
 *      true - if the above statement is true
 *      false - else
 */
bool operator<=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);


/**
 * Determines if first Health Points object's m_currentHP is more than the second's.
 *
 * @param healthPoints1 - First Health Points object
 * @param healthPoints2 - Second Health Points object
 * @return
 *      true - if the above statement is true
 *      false - else
 */
bool operator>(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);


/**
 * Determines if first Health Points object's m_currentHP is more than or equal to the second's.
 *
 * @param healthPoints1 - First Health Points object
 * @param healthPoints2 - Second Health Points object
 * @return
 *      true - if the above statement is true
 *      false - else
 */
bool operator>=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);


#endif //MATAM_EX2_HEALTHPOINTS_H

