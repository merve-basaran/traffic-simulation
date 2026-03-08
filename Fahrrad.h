/*
 * Fahrrad.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

using namespace std;

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {
public:
   Fahrrad(string name, double maxGeschwindigkeit);

   void vAusgeben(ostream& to) const override ; // Overrides output

   double dGeschwindigkeit() const override;

   ~Fahrrad() override = default;

   void vZeichnen(const Weg& weg) const override;
};



#endif /* FAHRRAD_H_ */
