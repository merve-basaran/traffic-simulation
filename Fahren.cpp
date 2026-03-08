/*
 * Fahren.cpp
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#include "Fahren.h"
#include "Streckenende.h"

#include <algorithm>

Fahren::Fahren(const Weg& weg) : Verhalten(weg) {}

double Fahren::dStrecke( Fahrzeug& fahrzeug, double dZeitIntervall) const {
	// Use the vehicle's speed times the zeit interval and the path's remaining distance to see wich one to use
	double RESTDistance = p_Weg.getLaenge() - fahrzeug.getAbschnittStrecke();

    return min(RESTDistance,fahrzeug.dGeschwindigkeit() * dZeitIntervall) ;
}

