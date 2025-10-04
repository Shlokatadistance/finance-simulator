
#include <iostream>
#include <iomanip>
#include <vector>
#include "lib/AbstractClasses.h"
#include "lib/FinancialProducts.h"
#include <fstream>
using std::string;

class EquityPortfolio : AbstractInvestmentPortfolio{
    public:
        Equity Product;
        EquityPortfolio(string equity_filename){
            std::vector<string> equityProduct;
            if (equity_filename.empty()){
                std::cout << "No equity data has been provided" << std::endl;
            }else{
                std::fstream equityFile;
                equityFile.open(equity_filename,std::ios::in);
                if (equityFile.is_open()){
                    std::string line;
                    while (getline(equityFile,line)){
                        equityProduct.push_back(line);
                    }
                    equityFile.close();
                }
            }
            Product.ticker = equityProduct[0];
            Product.quantity = std::stod(equityProduct[1]);
            Product.execution_price = std::stod(equityProduct[2]);
        }

        double current_valuation(double last_closing_px){
            double current_value = Product.quantity * (last_closing_px - Product.execution_price);
            return current_value;
        }
};

class DerivativesPortfolio : AbstractInvestmentPortfolio{
    public:
        DerivativesContract Product;
        DerivativesPortfolio(string derivatives_filename ){
            std::vector<string> derivativesProduct;
            if (derivatives_filename.empty()){
                std::cout << "No derivatives product has been provide" << std::endl;
            }else{
                std::fstream derivativesFile;
                derivativesFile.open(derivatives_filename,std::ios::in);
                if (derivativesFile.is_open()){
                    std::string line;
                    while(getline(derivativesFile,line)){
                        derivativesProduct.push_back(line);
                    }
                    derivativesFile.close();
                }
            }
            Product.ticker = derivativesProduct[0];
            Product.contract_size = std::stoi(derivativesProduct[1]);
            Product.strike_price = std::stod(derivativesProduct[2]);
            Product.time_to_expiry = std::stod(derivativesProduct[3]);
        }

        double current_valuation(double last_closing_px){
            // Options have an intrinsic value 
            if (last_closing_px > Product.strike_price){
                return -1.0;
            }else if (last_closing_px == Product.strike_price)
            {
                return 0.0;
            }else{
                return Product.strike_price - last_closing_px;
            }

        }
    };

class PersonalSheet : public EquityPortfolio, public DerivativesPortfolio{
    private:
        std::vector<int> InvestmentProducts; 
    public:
        string Name;
        string Occupation;
        double Salary;
        double NetWorth;
        double NetLiabilities;
        int Age;
        Equity EquityProduct;
        DerivativesContract DerivativesProduct;
        PersonalSheet(string name,string occupation,double salary,double netliabilities, int age,string equity_filename,string derivatives_filename):EquityPortfolio(equity_filename),DerivativesPortfolio(derivatives_filename){
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
        double current_valuation(){
            double equity_valuation = EquityPortfolio::current_valuation(100.00);
            std::cout << "Equity valuation is " << equity_valuation << std::endl;
            double derivative_valuation = DerivativesPortfolio::current_valuation(80.00);
            std::cout << "Derivatives valuation is " << derivative_valuation << std::endl;
            std:: cout << "Salary is " << Salary << std::endl;
            std::cout << "Liabilities are " << NetLiabilities << std::endl;
            double net_value = Salary + equity_valuation + derivative_valuation - NetLiabilities;            
            return net_value;
        }

};


int main(){
    PersonalSheet me = PersonalSheet("zyn","swe",120000.85,50000.1,24,"/opt/c++/finance-simulator/equity.txt","/opt/c++/finance-simulator/derivatives.txt");
    double currentNetWorth =  me.current_valuation();
    std::cout << me.Name << " is worth "<< std::fixed << std::setprecision(2) << currentNetWorth << std::endl;
    return 0;
}