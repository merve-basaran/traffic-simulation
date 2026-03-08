/*
 * Simulationsobjekt.cpp
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */




#include "Simulationsobjekt.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Initialize the static member variable for unique ID generation
int Simulationsobjekt::p_iMaxID = 0;

// Constructor
Simulationsobjekt::Simulationsobjekt(const string name)
    : p_sName(name), p_iID(++p_iMaxID), p_dZeit(0.0) {}

// Destructor
Simulationsobjekt::~Simulationsobjekt() {
    cout << "Deleting Simulationsobjekt: " << p_sName << ", ID: " << p_iID << endl;
}

// Output object details
void Simulationsobjekt::vAusgeben(ostream& os) const {
    os << setw(10) << p_iID
       << setw(20) << p_sName;
}

ostream& operator<<(ostream& out, const Simulationsobjekt& some) {

    some.vAusgeben(out); // Delegate to vAusgeben

    return out;

}

// Comparison operator
bool Simulationsobjekt::operator==(const Simulationsobjekt& other) const {
	return p_iID == other.p_iID;
}


