/*
 * Fahrverhalten.h
 *
 *  Created on: 27 Dec 2025
 *      Author: mervebasaran
 */

/**
 * @file Fahrverhalten.h
 * @brief Driving behavior (vehicle is moving).
 */

#ifndef FAHRVERHALTEN_H
#define FAHRVERHALTEN_H

#include "Verhalten.h"

/**
 * @brief Normal driving behavior.
 *
 * Computes distance = speed * dt, but clamps it so the vehicle
 * does not exceed the end of the road.
 */
class Fahrverhalten : public Verhalten
{
public:
    /**
     * @brief Construct driving behavior on a road.
     * @param weg Road reference.
     */
    explicit Fahrverhalten( Weg& weg);

    /**
     * @brief Compute drivable distance within dt (clamped to remaining road).
     */
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

#endif // FAHRVERHALTEN_H
