/*
 * Losfahren.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme {
public:
    // Constructor
    Losfahren(Fahrzeug& fahrzeug, Weg& weg);

    virtual ~Losfahren();

    // Override vBearbeiten
    void vBearbeiten() const override;
};

#endif /* LOSFAHREN_H_ */
