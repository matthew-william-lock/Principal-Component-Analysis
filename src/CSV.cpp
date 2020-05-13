#include "CSV.h"

namespace LCKMAT002 {

    CSV::CSV(){
        std::cout<<"New CSV object"<<std::endl;
    }

    CSV::CSV(const string & filename){
        this->filename=string(filename);
        this->columns=vector<string>();
        this->data=vector<vector<string>>();
    }

    bool CSV::read(){
        std::ifstream in(filename);
        if (!in.is_open()){
            cout<<"Error opening "<<filename<<endl;
            return false;
        } else{

            string line;
            getline(in,line);

            std::string columnData;
            std::istringstream token(line);

            while (token){
                string columnData;
                std::getline(token,columnData,',');
                if (!columnData.empty()) columns.push_back(columnData);
            }

            while (std::getline(in, line)) {
                std::istringstream token(line);
                std::string dataPoints;
                vector<string> newPoint;
                for (size_t i = 0; i < columns.size(); i++){
                    std::getline(token,dataPoints,',');
                    newPoint.push_back(dataPoints);
                }
                data.push_back(newPoint);                
            }     
        } 
        return true;      
    }

    string CSV::getData(const int & y, const int & x) const {
        return data.at(y).at(x);
    }

    int CSV::getNumberOfRows() const{
        return data.size();
    }

    int CSV::getNumberOfColumns() const{
        return columns.size();
    }


}