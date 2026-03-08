/*
 * Weg.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#ifndef WEG_H_
#define WEG_H_


#include "Simulationsobjekt.h"
#include <string>
#include <list>
#include <memory>
#include <iostream>
#include <vector>
#include "Fahrausnahme.h"
#include "SimuClient.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"




using namespace std;

class Fahrzeug;
class Kreuzung;

class Weg : public Simulationsobjekt {
protected:

    double p_dLaenge; // Length of the path in km

    vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge; // List of vehicles on the path

    Tempolimit p_eTempolimit; // Speed limit category

    vector<int> p_coordinates;

    weak_ptr<Weg> p_rRueckweg;       // Reciprocal path
    weak_ptr<Kreuzung> p_pZielKreuzung;    // Destination crossing


public:
    double getLaenge() const {
    	return p_dLaenge; }

    const vertagt::VListe<unique_ptr<Fahrzeug>>& getFahrzeuge() const {
    	return p_pFahrzeuge; }

    string getName() const {
    	return p_sName; }

    weak_ptr<Weg> getRueckweg()  {
        return p_rRueckweg.lock();
    }

    weak_ptr<Kreuzung> getZielKreuzung()  {
        return p_pZielKreuzung.lock();
    }

    void setRueckweg(const shared_ptr<Weg>& rueckweg) {
        p_rRueckweg = rueckweg;
    }



    // Constructors
    Weg();
    Weg(const string& name, double laenge ,  Tempolimit tempolimit = Tempolimit::Autobahn , shared_ptr<Kreuzung> zielKreuzung = nullptr);

    // Destructor
    virtual ~Weg();

    // Simulate the path
    virtual void vSimulieren() override;

    // Output path details
    virtual void vAusgeben(ostream& os) const override;

    static void vKopf();

    // Convert Tempolimit to speed in double
    double getTempolimit() const;

    void vAnnahme(unique_ptr<Fahrzeug> fahrzeug,double startzeit);
    void vAnnahme(unique_ptr<Fahrzeug> fahrzeug);


    unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);




};






#endif /* WEG_H_ */
