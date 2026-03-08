/*
 * Fahrzeug.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */


#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include "Simulationsobjekt.h"
#include <iostream>
#include <string>
#include <limits>
#include <memory>

using namespace std;

// Declare the global variable
extern double dGlobaleZeit;

class Weg; // Forward declaration
class Verhalten;


class Fahrzeug : public Simulationsobjekt{
protected:

    double p_dMaxGeschwindigkeit = 0; // Maximum speed of the vehicle
    double p_dGesamtStrecke = 0;      // Total distance traveled by the vehicle
    double p_dGesamtZeit = 0;         // Total time spent by the vehicle in motion
    double p_dZeit = 0;               // The last simulation time for the vehicle

    double p_dAbschnittStrecke = 0;   // Distance traveled on the current path

    // Add a smart pointer for behavior
    unique_ptr<Verhalten> p_pVerhalten;


public:

    double getAbschnittStrecke() const {
    	return p_dAbschnittStrecke; }

    void setAbschnittStrecke(double distance) {
    	p_dAbschnittStrecke = distance; }


    double getGesamtStrecke() const;

    // Constructor with string parameter
    Fahrzeug(string name);

    // Constructor with name and max speed parameter
    Fahrzeug(string name, double maxGeschwindigkeit);

    // Default constructor
    Fahrzeug();

    // Destructor
    virtual~Fahrzeug();

    // function to output the table header
    static void vKopf();
    // Member function to output vehicle data
    virtual void vAusgeben(ostream& to) const ;

    // Function to simulate the vehicle's movement
    virtual void vSimulieren();

    // Default implementation for vehicles without tanks
    virtual double dTanken(double dMenge = numeric_limits<double>::infinity());

    // Virtual function to calculate the current speed
    virtual double dGeschwindigkeit() const ;

    // Declaration of the overloaded '<' operator for the 'Fahrzeug' class
    bool operator<(const Fahrzeug& TheOtherObjects) const;

    // Deleting the copy constructor
    Fahrzeug(const Fahrzeug&) = delete;

    // Declare the assignment operator
    Fahrzeug& operator = (const Fahrzeug& TheOtherObjects);

    // Function to set new behavior
    void vNeueStrecke(Weg& weg2 );

    void vNeueStrecke(Weg& weg1 , double startzeit );

    virtual void vZeichnen(const Weg&) const;


};








#endif /* FAHRZEUG_H_ */

