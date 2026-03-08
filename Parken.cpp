/*
 * Parken.cpp
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#include "Parken.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Losfahren.h"
#include "Streckenende.h"

Parken::Parken(const Weg& weg, double startzeit)
    : Verhalten(weg), p_dStartzeit(startzeit) {}

double Parken::dStrecke(Fahrzeug& fahrzeug, double dZeitIntervall) const {

    const double EPSILON = 1e-3;  // A small value to account for floating-point precision
    // Output a message when start time is reached
    if (abs(dGlobaleZeit - p_dStartzeit) <= EPSILON) {
    	fahrzeug.setp_dZeit(p_dStartzeit);
    	throw Losfahren(const_cast<Fahrzeug&>(fahrzeug), const_cast<Weg&>(p_Weg));

        }
    else {
    	return 0.0;}
    	// Parked vehicles don't move
}
