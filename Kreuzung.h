/*
 * Kreuzung.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_


#include "Simulationsobjekt.h"
#include "Weg.h"
#include <list>
#include <memory>

class Kreuzung : public Simulationsobjekt {
private:
    double p_dTankstelle;  // Available fuel at the crossing
    list<shared_ptr<Weg>> p_pWege;  // List of outgoing paths

public:
    // Getter for the tank capacity
    double getTankstelle() const { return p_dTankstelle; }

    // Constructor
    Kreuzung(const string& name, double tankstelle = 0.0);

    // Destructor
    virtual ~Kreuzung() = default;

    // Refuel the vehicle
    void vTanken(Fahrzeug& fahrzeug);

    // Static method to connect crossings
    static void vVerbinde(const string& nameHinweg, const string& nameRueckweg,
                          double laenge,shared_ptr<Kreuzung> start, shared_ptr<Kreuzung> ziel, Tempolimit tempolimit);

    // Accept a vehicle (parked) and potentially refuel it
    void vAnnahme(unique_ptr<Fahrzeug> fahrzeug, double startzeit = 0.0);

    // Simulate all outgoing paths
    void vSimulieren();

    // Get a random outgoing path, avoiding the incoming one
    shared_ptr<Weg> pZufaelligerWeg(Weg& incomingWeg);
};





#endif /* KREUZUNG_H_ */
