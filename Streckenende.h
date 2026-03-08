/*
 * Streckenende.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme {
public:
    // Constructor
    Streckenende(Fahrzeug& fahrzeug, const Weg& weg);

    virtual ~Streckenende();

    // Override vBearbeiten
    void vBearbeiten() const override;
};

#endif /* STRECKENENDE_H_ */
