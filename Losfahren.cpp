/*
 * Losfahren.cpp
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#include "Losfahren.h"


Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg)
    : Fahrausnahme(fahrzeug, weg) {}

Losfahren::~Losfahren(){
}

void Losfahren::vBearbeiten() const {
	auto fahrzeug = p_rWeg.pAbgabe(p_rFahrzeug);
	    if (fahrzeug) {
	        // Reinsert the vehicle as moving
	        p_rWeg.vAnnahme(move(fahrzeug));
	        cout << "Losfahren Exception: Fahrzeug "
              << p_rFahrzeug.getName() << " is starting to move on Weg "
              << p_rWeg.getName() << endl;}
}
