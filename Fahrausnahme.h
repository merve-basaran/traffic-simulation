/*
 * Fahrausnahme.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include <exception>
#include <iostream>
#include "Fahrzeug.h"
#include "Weg.h"

/*Both Losfahren and Streckenende are derived from Fahrausnahme.
 * When you catch a Fahrausnahme object, it can handle both derived
 * exceptions because of polymorphism.*/

class Fahrausnahme : public std::exception {
protected:

    Fahrzeug& p_rFahrzeug; // Reference to the vehicle
    Weg& p_rWeg;           // Reference to the path

public:
    // Getter for Fahrzeug and Weg
     Fahrzeug& getFahrzeug() const { return p_rFahrzeug; }
     Weg& getWeg() const { return p_rWeg; }
    // Constructor
    Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg);

    // Pure virtual method for handling the exception
    virtual void vBearbeiten() const = 0;

    // Virtual destructor
    virtual ~Fahrausnahme();
};

#endif /* FAHRAUSNAHME_H_ */
