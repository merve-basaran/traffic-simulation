/*
 * Fahren.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#ifndef FAHREN_H_
#define FAHREN_H_

using namespace std;

#include "Verhalten.h"

class Fahren : public Verhalten {
public:
    explicit Fahren(const Weg& weg);

    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override;
};

#endif /* FAHREN_H_ */
