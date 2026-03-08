/*
 * Parken.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"

class Parken : public Verhalten {
protected:

	double p_dStartzeit;

public:


    Parken(const Weg& weg, double startzeit);

    double dStrecke( Fahrzeug& fahrzeug, double dZeitIntervall) const override;
};

#endif /* PARKEN_H_ */
