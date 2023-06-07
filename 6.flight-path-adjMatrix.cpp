#include <iostream>
#include <string>
using namespace std;

const int MAX_CITIES = 50;

class CityTravelMatrix {
private:
    int numCities;
    string city[MAX_CITIES];
    int adjMatrix[MAX_CITIES][MAX_CITIES];

public:
    void createMatrix();
    void displayMatrix();
};

void CityTravelMatrix::createMatrix() {
    cout << "Enter the number of cities: ";
    cin >> numCities;
    cin.ignore(); // Ignore the newline character

    for (int i = 0; i < numCities; i++) {
        cout << "Enter the name of city " << i + 1 << ": ";
        getline(cin, city[i]);
    }

    for (int i = 0; i < numCities; i++) {
        for (int j = i + 1; j < numCities; j++) {
            cout << "Enter the time required to travel from city " << city[i] << " to " << city[j] << ": ";
            cin >> adjMatrix[i][j];
            adjMatrix[j][i] = adjMatrix[i][j]; // Assign the same value symmetrically
        }
    }
}

void CityTravelMatrix::displayMatrix() {
    cout << "\nCity Travel Time Matrix:\n";
    cout << "\t";
    for (int i = 0; i < numCities; i++) {
        cout << city[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < numCities; i++) {
        cout << city[i] << "\t";
        for (int j = 0; j < numCities; j++) {
            if (i == j) {
                cout << "0\t";  // Display 0 for travel from city to itself
            } else {
                cout << adjMatrix[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

int main() {
    CityTravelMatrix matrix;
    matrix.createMatrix();
    matrix.displayMatrix();

    return 0;
}
