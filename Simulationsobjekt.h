/*
 * Simulationsobjekt.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

using namespace std;

#include <string>
#include <iostream>

class Simulationsobjekt {
protected:
    string p_sName="";   // Name of the simulation object
    int p_iID;             // Unique ID for the object
    static int p_iMaxID;
    mutable double p_dZeit = 0.0;  // Local time for the object


public:

    // Getter for the name
    string getName() const {
           return p_sName;
       }
    void setp_dZeit(double zeit) {
    	p_dZeit = zeit; }

    Simulationsobjekt(const string name);

    virtual ~Simulationsobjekt();

    virtual void vSimulieren() = 0;       // Pure virtual simulation method
    virtual void vAusgeben(ostream& os) const;

    Simulationsobjekt(const Simulationsobjekt&) = delete;  // Delete copy constructor
    Simulationsobjekt& operator=(const Simulationsobjekt&) = delete; // Delete assignment operator

    bool operator==(const Simulationsobjekt& other) const; // Compare by ID

    friend ostream& operator<<(ostream& out, const Simulationsobjekt& some);
};





#endif /* SIMULATIONSOBJEKT_H_ */
