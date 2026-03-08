/*
 * Streckenende.cpp
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#include "Streckenende.h"
#include "Weg.h"
#include "Kreuzung.h"
#include "Fahrrad.h"
#include <typeinfo>

Streckenende::Streckenende(Fahrzeug& fahrzeug, const Weg& weg)
    : Fahrausnahme(fahrzeug, const_cast<Weg&>(weg)) {}

Streckenende::~Streckenende(){}

void Streckenende::vBearbeiten() const {
    // Convert weak_ptr to shared_ptr to access the Kreuzung
    auto zielKreuzung = p_rWeg.getZielKreuzung().lock();

    // Remove the vehicle from the list
    auto fahrzeug = p_rWeg.pAbgabe(p_rFahrzeug);


	if (!fahrzeug) {
		cerr << "Error: No Fahrzeug to process at Streckenende for Weg: "
			 << p_rWeg.getName() << endl;
		return;}
	cout << "Streckenende Exception : " << p_rFahrzeug.getName()
                  << " has reached the end of " << p_rWeg.getName() << endl;

	if (zielKreuzung){
		// Determine the new path
		auto neuerWeg = zielKreuzung->pZufaelligerWeg(p_rWeg);

		// Refuel the vehicle at the crossing
		if (typeid(p_rFahrzeug) != typeid(Fahrrad)) {
			if (zielKreuzung->getTankstelle() > 0){
				zielKreuzung->vTanken(p_rFahrzeug);
			}
		}

		// Add the vehicle to the new path
		neuerWeg->vAnnahme(std::move(fahrzeug));

		cout << endl << "ZEIT: " << dGlobaleZeit << "\n";
		if ( typeid(p_rFahrzeug) == typeid(Fahrrad) ){
			cout << "KREUZUNG: " << zielKreuzung->getName() << endl;}

		if ( typeid(p_rFahrzeug) != typeid(Fahrrad) ) {
			if (zielKreuzung->getName() == "Kr2"){
				cout << "KREUZUNG: " << zielKreuzung->getName();
			    cout << " (" << zielKreuzung->getTankstelle() << " liters remaining)\n";}}

		if ( typeid(p_rFahrzeug) != typeid(Fahrrad) ) {
			if ( zielKreuzung->getName() != "Kr2"){
				cout << "KREUZUNG: " << zielKreuzung->getName() << endl;
				}}

		cout << "WECHSEL: " << p_rWeg.getName()
				  << " -> " << neuerWeg->getName() << "\n";
		cout << "FAHRZEUG: " << p_rFahrzeug.getName() << "\n"<<endl;
	}



}


