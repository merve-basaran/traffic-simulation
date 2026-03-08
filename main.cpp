/*
 * main.cpp
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "Fahren.h"
#include "Parken.h"
#include "Tempolimit.h"
#include "Fahrausnahme.h"
#include "SimuClient.h"
#include "SimuClientSocket.h"
#include "Simulationsobjekt.h"
#include "vertagt_liste.h"
#include "Kreuzung.h"

#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <utility>



using namespace std;

void vAufgabe_1() {
    // Static allocation of Fahrzeuge
    Fahrzeug Bugatti("Bugatti",500);
    Fahrzeug Mclaren("Mclaren",350);
    // Dynamic allocation of Fahrzeuge
    Fahrzeug* BMW = new Fahrzeug("BMW");
    Fahrzeug* Lamborghini = new Fahrzeug("Lamborghini");

    delete BMW;
    delete Lamborghini;

    // Creating smart pointers for Fahrzeuge
    auto f1 = make_unique<Fahrzeug>("BMW");
    auto f2 = make_unique<Fahrzeug>("Lamborghini");

    // Creating smart pointers for Fahrzeuge
    auto s1 = make_shared<Fahrzeug>("Mclaren");
    auto s2 = make_shared<Fahrzeug>("Bugatti");

    // Displaying the reference count
    cout << "The Number of references s2 before: " << s2.use_count() << endl;
    cout << "The Number of references s1 before: "<< s1.use_count() << endl;

    // Storing a shared_ptr in another shared_ptr
    shared_ptr<Fahrzeug> s3 = s2;

    // Displaying the reference count
    cout << "The Number of references s2 after: " << s2.use_count() << endl;
    cout << "The Number of references s3 after: " << s3.use_count() << endl;

    // Creating a vector of unique_ptr
    vector<unique_ptr<Fahrzeug>> Vec1;
    Vec1.push_back(move(f1));
    Vec1.push_back(move(f2));

    // Clear the vector and observe destruction
    Vec1.clear();

    // Creating a vector of shared_ptr
    vector<shared_ptr<Fahrzeug>> Vec2;
    Vec2.push_back(move(s1));
    Vec2.push_back(s3); // Shared ownership

    // Display reference count in vector
    cout << "The Number of references s2 in vector: " << s1.use_count() << endl;
    cout << "The Number of references s1 in vector: " << s3.use_count() << endl;


    //----------------------------------------------------------------------------------------------------------------------------------
    cout << "____________________________________________________________________________________________________"<< endl;
    //----------------------------------------------------------------------------------------------------------------------------------


    // Print the table header
    Fahrzeug::vKopf();

    // Display vehicle data for all created objects
    Bugatti.vAusgeben(cout);
    cout << endl;
    Mclaren.vAusgeben(cout);
    cout << endl;


}


void vAufgabe_1a() {
    // Vector to store the unique pointers to vehicles
    vector<unique_ptr<Fahrzeug>> vecFahr;

    // Read data for 3 vehicles from the console
    for (int i = 0; i < 3; ++i) {
        string name;
        double maxGeschwindigkeit;

        cout << "Geben Sie den Namen des Fahrzeugs ein: ";
        cin >> name;
        cout << "Geben Sie die maximale Geschwindigkeit des Fahrzeugs ein: ";
        cin >> maxGeschwindigkeit;

        // Create the vehicle and add to the vector
        vecFahr.push_back(make_unique<Fahrzeug>(name, maxGeschwindigkeit));
    }

    // Output the header for the vehicle table
    Fahrzeug::vKopf();

    // Simulate the vehicles
    for (dGlobaleZeit = 0.0; dGlobaleZeit <= 3.0; dGlobaleZeit += 0.5) {
    	cout << "Time: " << dGlobaleZeit << " hours" << endl;
        for (size_t i = 0; i < vecFahr.size(); i++) {
            vecFahr[i]->vSimulieren();
            vecFahr[i]->vAusgeben(cout);
            cout << endl ;

        }
        cout << "--------------------------------------------------------------------------------------" << endl;

    }
}


void vAufgabe_2() {
	    int numPKW ;
	    int numFahrrad ;

	    cout << "Enter the number of PKWs: ";
	    cin >> numPKW;
	    cout << "Enter the number of Fahrräder: ";
	    cin >> numFahrrad;

	    // Creating vector of unique_ptr
	    vector<unique_ptr<Fahrzeug>> vecFahrzeuge;

/*Question 1:
If we store Fahrzeug objects directly, we lose the unique properties of the derived classes like PKW or Fahrrad.
It limits us to only the features of the base class Fahrzeug.

Question 2:
We can store them in the same vector because both PKW and Fahrrad are types of Fahrzeug.*/

/*Frage 1: Wenn wir Fahrzeugobjekte direkt speichern, verlieren wir die einzigartigen Eigenschaften der abgeleiteten Klassen wie Auto oder Fahrrad.
Wir sind dann nur auf die Merkmale der Basisklasse Fahrzeug beschränkt.

Frage 2: Wir können sie im selben Vektor speichern, da sowohl Autos als auch Fahrräder Fahrzeugtypen sind.*/

	    // Construct PKWs
	    for (int i = 0; i < numPKW; ++i) {

	        string name = "PKW_" + to_string(i + 1);

	        double maxSpeed = 100 + i * 10;  // Just an example of speed so it is diffrent for each car
	        double consumption = 8 + i;     // just an example of consumption so it is diffrent for each car
	        double Tankvolumen = 30 + i*5;  //// just an example for Tankvolumen so it is diffrent for each car

	        vecFahrzeuge.push_back(make_unique<PKW>(name, maxSpeed, consumption,Tankvolumen));
	    }

	    // Construct Fahrräder
	    for (int i = 0; i < numFahrrad; ++i) {

	        string name = "Fahrrad_" + to_string(i + 1);
	        double maxSpeed = 25 + i * 5;  // Just an example of speed

	        vecFahrzeuge.push_back(make_unique<Fahrrad>(name, maxSpeed));
	    }

	    double toleranz = 1e-4 ;  // Tolerance for floating-point comparison
	    int T=7 ;
	    int b=0 ;
		Fahrzeug::vKopf();      // Output the header

		//ensures the loop continues until dGlobaleZeit is close to or slightly over 5H
		for (dGlobaleZeit = 0; dGlobaleZeit - toleranz <= T; dGlobaleZeit += 0.5) {
			cout << "Time: " << dGlobaleZeit << " hours" << endl;

			int a=static_cast<int>(dGlobaleZeit);

			for (unsigned int i = 0; i < vecFahrzeuge.size(); i++) {
				vecFahrzeuge[i]->vSimulieren();

				// Refuel PKWs exactly at 3 hours
				for (int j=1 ; j<=T/3 ; j++) {
					if ((fabs(dGlobaleZeit - 3.0*j) < toleranz ) || ((a!=b) and a %3 ==0)) { // It ensures that dGlobaleZeit is close enough to 3.0 or to any multipels of 3, even if it isn t exactly 3H
						vecFahrzeuge[i]->dTanken();
					}
				}

				vecFahrzeuge[i]->vAusgeben(cout);

				cout << endl;
			}
			b=static_cast<int>(dGlobaleZeit);

			cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
}

void vAufgabe_3 (){
		PKW PKW1("Mclaren",300,8,50);
		PKW PKW2("Koenigsegg",520,9,50);
		Fahrzeug fahrzeug2("Lamborgini",320);
		Fahrrad Fahrrad1("JustaBike",20);

		Fahrzeug::vKopf();
		cout << PKW1 << endl << Fahrrad1 << endl << fahrzeug2 << endl;
		cout<<"---------------------------------------------------------"<< endl;

		// Simulate some distance traveled
		dGlobaleZeit = 5.0;
		PKW1.vSimulieren();
 		PKW2.vSimulieren();
		if (PKW1 < PKW2){
				cout<< endl << "PKW2 has traveled more distance than PKW1."<<endl<<endl;
			}
		else{
				cout<< endl << "PKW1 has traveled more distance than PKW2."<<endl<<endl;
			}
		cout<<"---------------------------------------------------------"<< endl;

		PKW PKW8("Fiat", 50,0.5,20);
		PKW PKW3("Nothing", 0,0,0);
		Fahrzeug fahrzeug20("nothing",0);

		fahrzeug20=fahrzeug2;
		PKW3 = PKW8;
		dGlobaleZeit = 5.0;
		PKW3.vSimulieren();
		PKW8.vSimulieren();
		fahrzeug20.vSimulieren();
		fahrzeug2.vSimulieren();

		Fahrzeug::vKopf();

		cout << "The original PKW8 : " << endl << PKW8 << endl;
		cout << "The copied PKW3 : " << endl << PKW3 <<endl;


		cout << endl << "The original fahrzeug2 : " << endl << fahrzeug2 << endl;
		cout << "The copied fahrzeug20 : " << endl << fahrzeug20 <<endl<<endl;
}




/*extern double dGlobaleZeit;
double dEpsilon = 0.001;

void vAufgabe_Probe() {
    Fahrzeug* pF1 = new PKW("Audi", 150, 8);
    dGlobaleZeit = 0.0;
    Fahrzeug::vKopf();
    dGlobaleZeit = 5.0;
    cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
    pF1->vSimulieren();
    std::cout << *pF1 << endl;
    delete pF1;
    char c;
    std::cin >> c;
}*/


extern double dGlobaleZeit;
double dEpsilon = 0.001;
void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{13};
    double dTakt = 0.4;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 217, 10.7));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 21.4));
    for (dGlobaleZeit = 0; dGlobaleZeit < 6; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < (int) vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}

/*__________________________________________________________________________________________________________________*/
void vAufgabe4() {

    // Create a Weg object
    Weg Weg1("Hauptstraße", 12.5, Tempolimit::Innerorts);
//ken man hotech static nwali lezem nekteb weg1.vKopf
    Weg::vKopf();
    cout << Weg1 << endl;
    Weg1.vSimulieren();

}

void vAufgabe5() {
    dGlobaleZeit = 0.0;


    Weg highway10("Highway_10", 600.0, Tempolimit::Autobahn);

    auto bmw = make_unique<Fahrzeug>("BMW", 200.0);
    auto audi = make_unique<Fahrzeug>("Audi", 130.0);
    auto tesla = make_unique<Fahrzeug>("Tesla", 200.0);
    auto fiat = make_unique<Fahrzeug>("Fiat", 100.0);

    highway10.vAnnahme(move(bmw));
    highway10.vAnnahme(move(audi));
    highway10.vAnnahme(move(fiat), 2);
    highway10.vAnnahme(move(tesla), 1);


	for (int i = 0; i < 10; ++i) {
		double ti=dGlobaleZeit;
		cout << "Time: " << ti << endl;

		// Simulate the Weg
		highway10.vSimulieren();
        // Output the Weg details
        Weg::vKopf();
        highway10.vAusgeben(cout);
        cout<<endl;

        // Increment global simulation time
        dGlobaleZeit += 1.0;

    }
}

void vAufgabe6(){

	bool okInit = bInitialisiereGrafik(800, 500, "127.0.0.1", "7654");
	    std::cout << std::boolalpha << "init=" << okInit << "\n";
	    if (!okInit) return;

	dGlobaleZeit = 0.0;

	// Create two paths
	Weg highway("HighwayX", 500.0, Tempolimit::Autobahn); // No speed limit
	Weg c_Road("Jandouba", 500.0, Tempolimit::Landstrasse); // Speed limit of 100 km/h

    // Set coordinates for roads
	int koordinaten[] = {700, 250, 100, 250};

    // Draw roads on the graphics interface
    bZeichneStrasse("HighwayX", "Jandouba", 500, 2, koordinaten);

	// Create vehicles
    auto bmw = make_unique<PKW>("BMW", 51.0, 3.0);
    auto audi = make_unique<PKW>("Audi", 220.0, 1.5);
    auto fiat = make_unique<PKW>("Fiat", 60.0, 2.0);
    auto tesla = make_unique<PKW>("Tesla", 210.0, 2.0);

	// Add vehicles to paths
	highway.vAnnahme(move(bmw));
	highway.vAnnahme(move(audi), 2.0); // Parked, start at time 2.0
	c_Road.vAnnahme(move(fiat));
	c_Road.vAnnahme(move(tesla), 3.0); // Parked, start at time 3.0

	// Simulate both paths
	for (int i = 0; i < 50; ++i) {
		cout <<"\n"<< "Global Time: " << dGlobaleZeit <<"\n" << endl;

		// Set simulation time in graphics
		vSetzeZeit(dGlobaleZeit);

		// Simulate highway
		cout << "Simulating Highway" << endl;
		highway.vSimulieren();
		Weg::vKopf();
		highway.vAusgeben(cout);
		cout << endl;

		// Simulate country road
		cout << "Simulating Country Road" << endl;
		c_Road.vSimulieren();
		Weg::vKopf();
		c_Road.vAusgeben(cout);
		cout << endl;

		// Increment global time
		dGlobaleZeit += 0.25;
		// Pause for visualization
		vSleep(250);
	}
	// Close graphics
	vBeendeGrafik();


}


void vAufgabe_6a() {

    vertagt::VListe<int> list;
    static mt19937 device(0);
    uniform_int_distribution<int> dist(1, 10);

    for (int i = 0; i < 10; ++i) {
        list.push_back(dist(device));
    }

    cout << "Initial list ( before vAktualisieren ) :  " << endl;
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    list.vAktualisieren();

    cout << "List ( after vAktualisieren ) :  " ;
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    for (auto it = list.begin(); it != list.end(); ++it) {
        if (*it > 5) {
            list.erase(it);
        }
    }

       cout << "List after erase ( before vAktualisieren ) :  " ;
       for (auto it = list.begin(); it != list.end(); ++it) {
           cout << *it << " ";
       }
       cout << endl;

       list.vAktualisieren();

       cout << "List after erase ( after vAktualisieren ) :  " ;
       for (auto it = list.begin(); it != list.end(); ++it) {
           cout << *it << " ";
       }
       cout << endl;
       list.push_front(0);
       list.push_back(11);

       cout << "List after adding random numbers ( before vAktualisieren ) :  " ;
       for (auto it = list.begin(); it != list.end(); ++it) {
           cout << *it << " ";
       }
       cout << endl;

       list.vAktualisieren();

       cout << "List after adding random numbers ( after vAktualisieren ) :  " ;
       for (auto it = list.begin(); it != list.end(); ++it) {
           cout << *it << " ";
       }
       cout << endl;
   }

void vAufgabe_7(){

	// 1) Graphics init (your setup)
	    bInitialisiereGrafik(800, 500, "127.0.0.1", "7654");

	    // Figure 5.4 roughly fits into 1000x600 area (max ~970x570).
	    // Use a uniform scale so everything fits into 800x500 nicely.
	    constexpr double scale = 0.80;     // 1000 -> 800
	    constexpr int offsetX = 10;        // small margin
	    constexpr int offsetY = 10;

	    auto sx = [&](int x) { return static_cast<int>(x * scale) + offsetX; };
	    auto sy = [&](int y) { return static_cast<int>(y * scale) + offsetY; };

	    // 2) Draw intersections (Kreuzungen)
	    bZeichneKreuzung(sx(680), sy(40));   // Kr1
	    bZeichneKreuzung(sx(680), sy(300));  // Kr2
	    bZeichneKreuzung(sx(680), sy(570));  // Kr3
	    bZeichneKreuzung(sx(320), sy(300));  // Kr4

	    // 3) Create crossings; only Kr2 has a gas station (tank capacity = 1000L)
	    auto Kr1 = std::make_shared<Kreuzung>("Kr1");
	    auto Kr2 = std::make_shared<Kreuzung>("Kr2", 1000);
	    auto Kr3 = std::make_shared<Kreuzung>("Kr3");
	    auto Kr4 = std::make_shared<Kreuzung>("Kr4");

	    // 4) Street names (must match between vVerbinde and bZeichneStrasse!)
	    const std::string W12  = "W12";
	    const std::string W21  = "W21";
	    const std::string W23a = "W23a";
	    const std::string W32a = "W32a";
	    const std::string W23b = "W23b";
	    const std::string W32b = "W32b";
	    const std::string W24  = "W24";
	    const std::string W42  = "W42";
	    const std::string W34  = "W34";
	    const std::string W43  = "W43";
	    const std::string W44a = "W44a";
	    const std::string W44b = "W44b";

	    // 5) Connect crossings (lengths from the figure text)
	    // Street1: 40km
	    Kreuzung::vVerbinde(W12,  W21,  40.0,  Kr1, Kr2, Tempolimit::Landstrasse);

	    // Street2: 115km
	    Kreuzung::vVerbinde(W23a, W32a, 115.0, Kr2, Kr3, Tempolimit::Autobahn);

	    // Street3: 40km
	    Kreuzung::vVerbinde(W23b, W32b, 40.0,  Kr2, Kr3, Tempolimit::Innerorts);

	    // Street4: 55km
	    Kreuzung::vVerbinde(W24,  W42,  55.0,  Kr2, Kr4, Tempolimit::Innerorts);

	    // Street5: 85km
	    Kreuzung::vVerbinde(W34,  W43,  85.0,  Kr3, Kr4, Tempolimit::Landstrasse);

	    // Street6: 130km (loop from Kr4 back to Kr4)
	    Kreuzung::vVerbinde(W44a, W44b, 130.0, Kr4, Kr4, Tempolimit::Landstrasse);

	    // 6) Draw streets (polylines) - scaled coordinates
	    // Street1: Kr1(680,40) -> Kr2(680,300)
	    int koordStrasse1[] = { sx(680), sy(40),  sx(680), sy(300) };
	    bZeichneStrasse("W12", "W21", 40, 2, koordStrasse1);

	    // Street2: Kr2 -> right loop -> Kr3
	    int koordStrasse2[] = {
	        sx(680), sy(300),
	        sx(850), sy(300),
	        sx(970), sy(390),
	        sx(970), sy(500),
	        sx(850), sy(570),
	        sx(680), sy(570)
	    };
	    bZeichneStrasse("W23a", "W32a", 115, 6, koordStrasse2);

	    // Street3: Kr2(680,300) -> Kr3(680,570)
	    int koordStrasse3[] = { sx(680), sy(300), sx(680), sy(570) };
	    bZeichneStrasse("W23b", "W32b", 40, 2, koordStrasse3);

	    // Street4: Kr2(680,300) -> Kr4(320,300)
	    int koordStrasse4[] = { sx(680), sy(300), sx(320), sy(300) };
	    bZeichneStrasse("W24", "W42", 55, 2, koordStrasse4);

	    // Street5: Kr3 -> left bottom curve -> Kr4
	    int koordStrasse5[] = {
	        sx(680), sy(570),
	        sx(500), sy(570),
	        sx(350), sy(510),
	        sx(320), sy(420),
	        sx(320), sy(300)
	    };
	    bZeichneStrasse("W34", "W43", 85, 5, koordStrasse5);

	    // Street6: Kr4 -> up/left loop -> back to Kr4
	    int koordStrasse6[] = {
	        sx(320), sy(300),
	        sx(320), sy(150),
	        sx(200), sy(60),
	        sx(80),  sy(90),
	        sx(70),  sy(250),
	        sx(170), sy(300),
	        sx(320), sy(300)
	    };
	    bZeichneStrasse("W44a", "W44b", 130, 7, koordStrasse6);

	    // 7) Vehicles -> accept at Kr1
	    auto car1  = std::make_unique<PKW>("Fiat",    80, 1.0);
	    auto car2  = std::make_unique<PKW>("Audi",   100, 2.5);
	    auto car3  = std::make_unique<PKW>("Bugatti",300, 6.0);
	    auto bike1 = std::make_unique<Fahrrad>("BMX", 40);
	    auto bike2 = std::make_unique<Fahrrad>("Bike",18);

	    Kr1->vAnnahme(std::move(car1), 3.0);
	    Kr1->vAnnahme(std::move(car2), 0.0);
	    Kr1->vAnnahme(std::move(car3), 1.0);
	    Kr1->vAnnahme(std::move(bike1), 0.0);
	    Kr1->vAnnahme(std::move(bike2), 5.0);

    double Ti = 0.0;
    double Step = 0.1;
    double SimulationDuration = 20;
    for (dGlobaleZeit = 0.0; dGlobaleZeit < SimulationDuration; dGlobaleZeit += Step) {
    	Ti=dGlobaleZeit;
        cout << "Zeit : " << Ti << endl;
        Kr1->vSimulieren();
        Kr2->vSimulieren();
        Kr3->vSimulieren();
        Kr4->vSimulieren();
        vSetzeZeit(dGlobaleZeit);
        // Pause for visualization
		vSleep(100);
    }


}



int main() {

	//vAufgabe_old6();

	//vAufgabe_1();

    //vAufgabe_1a();

    //vAufgabe_2();

    //vAufgabe_3();

	//vAufgabe_Probe();

	//vAufgabe_AB1();

	//vAufgabe4();

//vAufgabe5();

	//vAufgabe6();

	//vAufgabe_6a();

	vAufgabe_7();

    return 0;
}




