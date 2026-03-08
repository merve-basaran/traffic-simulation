/*
 * Weg.cpp
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#include "Weg.h"
#include <iomanip>
#include "Fahrzeug.h"
#include "Weg.h"
#include "Losfahren.h"
#include "Streckenende.h"
#include "Kreuzung.h"
#include <utility>


using namespace std;

// Constructors
Weg::Weg()
    : Simulationsobjekt(""), p_dLaenge(0), p_eTempolimit(Tempolimit::Autobahn) {
}

Weg::Weg(const string& name, double laenge, Tempolimit tempolimit , shared_ptr<Kreuzung> zielKreuzung)
    : Simulationsobjekt(name), p_dLaenge(laenge > 0 ? laenge : 0), p_eTempolimit(tempolimit) ,  p_pZielKreuzung(zielKreuzung) {
}

// Destructor
Weg::~Weg() {
    cout << "Weg destroyed: " << p_sName << endl;
}

void Weg::vSimulieren() {
	p_pFahrzeuge.vAktualisieren(); //Applies the changes accumulated in the previous step
    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end();) {
        auto& fahrzeug = *it;

        try {
            if (fahrzeug) {
                fahrzeug->vSimulieren();
                fahrzeug->vZeichnen(*this);
            }
            ++it; // Move to the next vehicle
        } catch (const Streckenende& e) {
            e.vBearbeiten(); // Print the exception message

        } catch (const Losfahren& e) {
            e.vBearbeiten(); // Print the exception message
            ++it;
        }

    }
    p_pFahrzeuge.vAktualisieren(); //vertagte Liste / delayed list Applies the "remove/add/move" operations accumulated in this step.
}



void Weg::vAusgeben(ostream& os) const {
    // Call the base class output method for ID and Name
    Simulationsobjekt::vAusgeben(os);
    // Output Weg-specific details
    os << setw(20) << fixed << setprecision(2) << p_dLaenge ;

    // List vehicle names in parentheses
    os << " (";

    for (const auto& fahrzeug : p_pFahrzeuge) {
        if (fahrzeug) {
            os << fahrzeug->getName() << " ";
        }
    }
    os << ")";
}

// Header for displaying paths
void Weg::vKopf() {
    cout << left
         << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(20) << "Laenge"
         << "Fahrzeuge"
         << endl;
    cout << string(60, '-') << endl;
}

// Convert Tempolimit to speed in double
double Weg::getTempolimit() const {

    return static_cast<double>(p_eTempolimit);
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug , double startzeit) {
    // Insert parked vehicles at the front
    fahrzeug->vNeueStrecke(*this, startzeit);
    p_pFahrzeuge.push_front(std::move(fahrzeug));
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug ) {
    // Insert moving vehicles at the back
    fahrzeug->vNeueStrecke(*this);
    p_pFahrzeuge.push_back(std::move(fahrzeug));
}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug) {

    for (auto i = p_pFahrzeuge.begin(); i != p_pFahrzeuge.end(); ++i) {
        if (**i == fahrzeug) {
            auto removedFahrzeug = std::move(*i);
            p_pFahrzeuge.erase(i); // Remove from the list
            return removedFahrzeug; // Return the unique_ptr
        }
    }
    return nullptr; // If not found, return nullptr
}



