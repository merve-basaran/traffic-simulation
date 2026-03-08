/*
 * PKW.h
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#ifndef PKW_H_
#define PKW_H_

using namespace std;

#include "Fahrzeug.h"
#include <limits>

class PKW : public Fahrzeug {

private:
	double p_dVerbrauch;
	double p_dTankvolumen ;
	double  p_dTankinhalt;
public:
	PKW(string name, double maxGeschwindigkeit ,double Verbrauch ,double Tankvolumen =55);

	void vSimulieren() override; // Overrides simulation
	void vAusgeben(ostream& to) const override ; // Overrides output

	double dTanken(double dMenge = numeric_limits <double>::infinity()) override;

	// Override dGeschwindigkeit to always return full speed
	double dGeschwindigkeit() const override;




	void vZeichnen(const Weg& weg) const override;

	~PKW() override = default;
};




#endif /* PKW_H_ */
