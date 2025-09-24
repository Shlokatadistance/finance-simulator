
#include <iostream>
#include <iomanip>
#include <vector>
#include "lib/AbstractClasses.h"
using std::string;

class FinancialSheet : AbstractFinancialStatements{
    private:
        std::vector<int> InvestmentProducts; 
    public:
        string Name;
        string Occupation;
        double Salary;
        double NetWorth;
        double NetLiabilities;
        int Age;

        FinancialSheet(string name,string occupation,double salary,double netliabilities, int age){
            Name = name;
            Occupation = occupation;
            Salary = salary;
            NetLiabilities = netliabilities;
            Age = age;
        }

        double returnNetWorth(){
            NetWorth = Salary - NetLiabilities;
            return NetWorth;
        }

};


int main(){
    FinancialSheet me = FinancialSheet("zyn","swe",120000.85,50000.1,24);
    double currentNetWorth =  me.returnNetWorth();
    std::cout << me.Name << " is worth "<< std::fixed << std::setprecision(2) << currentNetWorth << std::endl;
    return 0;
}