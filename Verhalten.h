/*
 * Verhalten.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_

#include "Weg.h"
#include "Fahrzeug.h"

class Verhalten {
protected:
    const Weg& p_Weg; // Reference to the associated path (Weg)

public:
   /* void setWeg(Weg* weg1) {
            p_Weg = weg1;
        }*/
    const Weg& getWeg() const {
            return p_Weg;
        }
    // Constructor
    explicit Verhalten(const Weg& weg);

    // Virtual destructor
    virtual ~Verhalten();

    // Pure virtual method to compute the distance
    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const =0;
};

#endif /* VERHALTEN_H_ */

