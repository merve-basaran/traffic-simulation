/*
 * Kreuzung.cpp
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#include "Kreuzung.h"
#include "PKW.h"
#include <iostream>
#include <random>
#include <utility>

// Constructor
Kreuzung::Kreuzung(const string& name, double tankstelle)
    : Simulationsobjekt(name), p_dTankstelle(tankstelle) {}

// Refuel a vehicle
void Kreuzung::vTanken(Fahrzeug& fahrzeug) {
	if (p_dTankstelle > 0.0) {
        double refuelAmount = fahrzeug.dTanken();
        p_dTankstelle -= refuelAmount;}
	 if (p_dTankstelle < 0) {
		p_dTankstelle = 0;
        }
        cout << "Vehicle " << fahrzeug.getName()
                  << " refueled at " << getName()
                  << ". The Remaining fuel is : " << p_dTankstelle << " liters.\n";

}


void Kreuzung::vVerbinde(const string& hinWeg, const string& rueckWeg, double laenge,
                         shared_ptr<Kreuzung> start, shared_ptr<Kreuzung> ziel, Tempolimit tempolimit) {

    auto hin = std::make_shared<Weg>(hinWeg, laenge, tempolimit, ziel);
    auto rueck = std::make_shared<Weg>(rueckWeg, laenge, tempolimit, start);

    hin->setRueckweg(rueck);
    rueck->setRueckweg(hin);

    start->p_pWege.push_back(move(hin));
    ziel->p_pWege.push_back(move(rueck));
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> fahrzeug, double startzeit) {
    // Refuel the vehicle if there is fuel available
	if (p_dTankstelle > 0) {
		double refueledAmount = fahrzeug->dTanken();
		p_dTankstelle -= refueledAmount; // Decrease the fuel available at the crossing
		cout << p_sName << ": Refueled " << fahrzeug->getName()
				  << " with " << refueledAmount << " liters.\n";
	}
    if(startzeit>dGlobaleZeit){
    	auto Parkende = p_pWege.front();
    	Parkende->vAnnahme(move(fahrzeug), startzeit);
    }
    else{
    	auto Fahr = p_pWege.back();
    	Fahr->vAnnahme(move(fahrzeug));
    }
}

void Kreuzung::vSimulieren() {
    for (const auto& weg : p_pWege) {
        weg->vSimulieren(); // Simulate each outgoing path
    }
}


shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& incomingWeg) {
    vector<shared_ptr<Weg>> validWege;

    for (const auto& weg : p_pWege) {
        if (weg != incomingWeg.getRueckweg().lock()) {
            validWege.push_back(weg);
        }
    }
    if (validWege.empty()) {
        cerr << "Error: No valid Weg available at Kreuzung "
             <<  endl;}
    // If no valid path is available, return the return path
    if (validWege.empty()) {
        return incomingWeg.getRueckweg().lock();
    }

    // Randomly select a valid path
    static mt19937 generator(0);
    uniform_int_distribution<int> dist(0, validWege.size() - 1);

    return validWege[dist(generator)];
}

