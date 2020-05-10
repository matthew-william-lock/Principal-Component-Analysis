#include "CSV.h"

#include <Eigen/Dense> // C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms (http://eigen.tuxfamily.org/)


int main() {

    using namespace std;
    
    string filename = "2018-AvgRainfall_mm.csv";
    LCKMAT002::CSV csvFile = LCKMAT002::CSV(filename);
    csvFile.read();

    cout<<csvFile.getData(4,0);


    return 0;

}