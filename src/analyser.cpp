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

    cout<<"DATA"<<endl;
    cout<<data<<endl<<endl;

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

    cout<<"Eigen Values"<<endl;
    cout<<eigenVal<<endl<<endl;

    // Step 4 - Reorder EigenVectors and Values
    eigenVec.col(0).swap(eigenVec.col(1));
    eigenVal.row(0).swap(eigenVal.row(1));

    cout<<"Ordered Eigen Vectors"<<endl;
    cout<<eigenVec<<endl<<endl;

    cout<<"Ordered Values"<<endl;
    cout<<eigenVal<<endl<<endl;

    // Total Variance
    double totalVar = cov(0,0) + cov(1,1);

    cout<<"Total Variance : "<<totalVar<<endl<<endl;

    // Variance from components 1
    auto featVec = eigenVec.col(0).transpose();
    auto rowAdj = data.transpose();
    MatrixXd finalData = (featVec*rowAdj);
    finalData=finalData.transpose();

    double std_dev1 ;
    finalData= (finalData.rowwise() - finalData.colwise().mean());
    for (size_t i = 0; i < finalData.size(); i++){
        std_dev1=finalData(i,0)*finalData(i,0);
    }
    std_dev1=std_dev1/(finalData.size()-1);   
    cout<<"Component 1 Varience : "<< std_dev1<<endl<<endl;

    // Variance from components 2
    featVec = eigenVec.col(1).transpose();
    finalData = (featVec*rowAdj);
    finalData=finalData.transpose();

    double std_dev2 ;
    finalData= (finalData.rowwise() - finalData.colwise().mean());
    for (size_t i = 0; i < finalData.size(); i++){
        std_dev2=finalData(i,0)*finalData(i,0);
    }
    std_dev2=std_dev2/(finalData.size()-1);
    cout<<"Component 2 Varience : "<< std_dev2<<endl<<endl;






    


    return 0;

}