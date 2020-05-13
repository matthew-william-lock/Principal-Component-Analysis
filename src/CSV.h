#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace LCKMAT002{

    using namespace std;

    class CSV{

        private:
            string filename;
            vector<string> columns;
            vector<vector<string>> data;

        public:
            CSV();
            CSV( const string & filename);

            bool read();

            string getData(const int & y, const int & x) const;
            int getNumberOfRows() const;
            int getNumberOfColumns() const;

    };

}

#endif
