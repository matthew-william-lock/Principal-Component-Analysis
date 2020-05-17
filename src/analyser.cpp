#include "CSV.h"

#include <Eigen/Dense> // C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms (http://eigen.tuxfamily.org/)
#include <Eigen/Eigenvalues>


int main() {

    using namespace std;
    using namespace Eigen;
    
    string filename = "2018-AvgRainfall_mm.csv";
    LCKMAT002::CSV csvFile = LCKMAT002::CSV(filename);
    csvFile.read();

    int Y = csvFile.getNumberOfRows();
    int X = csvFile.getNumberOfColumns();

    MatrixXd data(csvFile.getNumberOfRows(), csvFile.getNumberOfColumns()-1);

    // Initialise matrix
    for (size_t y = 0; y < csvFile.getNumberOfRows(); y++){
        for (size_t x = 0; x < csvFile.getNumberOfColumns()-1; x++){
            data(y,x)=atof(csvFile.getData(y,x+1).c_str());
        }
    }
    
    // Determine mean for Jan
    auto jan = data.col(0);
    double janMean = jan.mean();
    cout <<"January Mean Rainfall: "<<janMean<<endl;

    // Determine mean for July
    auto july = data.col(1);
    double julyMean = july.mean();
    cout <<"July Mean Rainfall: "<<julyMean<<endl<<endl;

    // Step 1 - Subtract the mean
    data = data.rowwise()-data.colwise().mean();

    // cout<<"Mean subtracted data "<<endl; // Print the data
    // cout<<data<<endl<<endl;

    // Step 2 - Calculate the covariance matrix
    MatrixXd intCov = data.rowwise()-data.colwise().mean();
    MatrixXd cov = (intCov.adjoint() * intCov) / double(data.rows() - 1);

    cout<<"Covariance Matrix"<<endl;
    cout<<cov<<endl<<endl;

    // Step 3 - Calculate the eigenvectors and eigenvalues of the covariance matrix
    Eigen::SelfAdjointEigenSolver<MatrixXd>eig(cov);
    auto eigenVec = eig.eigenvectors();
    auto eigenVal = eig.eigenvalues();

    cout<<"Eigen Vectors"<<endl;
    cout<<eigenVec<<endl<<endl;

    // cout<<"Eigen Values"<<endl;
    // cout<<eigenVal<<endl<<endl;

    // Step 4 - Reorder EigenVectors and Values
    eigenVec.col(0).swap(eigenVec.col(1));
    eigenVal.row(0).swap(eigenVal.row(1));

    cout<<"Ordered Eigen Vectors"<<endl;
    cout<<eigenVec<<endl<<endl;

    // cout<<"Ordered Values"<<endl;
    // cout<<eigenVal<<endl<<endl;

    // Total Variance
    double totalVar = cov(0,0) + cov(1,1);

    // Write Results to text file
    ofstream myfile;
    myfile.open ("../output.txt");

    // 1
    myfile<<"1.\tPrincipal Component \t1\t\t\t2"<<endl;
    myfile<<"\tEigenvalue\t\t\t\t"<<eigenVal(0)<<"\t\t"<<eigenVal(1)<<endl;

    // 2
    myfile<<"2.\tPrincipal Component 1 Eigenvector:"<<endl;
    myfile<<eigenVec.col(0)<<endl;
    myfile<<"\tPrincipal Component 2 Eigenvector:"<<endl;
    myfile<<eigenVec.col(1)<<endl;

    // 3 
    myfile<<"3.\tCovariance Matrix"<<endl;
    myfile<<cov<<endl;

    // 4
    myfile<<"4.\tTotal Variance : "<<totalVar<<endl;

    //5
    myfile<<"5.Proportion of variance due to PC 1 : "<<eigenVal(0)/totalVar*100<<" %"<<endl;
    myfile<<"Proportion of variance due to PC 2 : "<<eigenVal(1)/totalVar*100<<" %"<<endl;

    myfile.close();
    return 0;   

}