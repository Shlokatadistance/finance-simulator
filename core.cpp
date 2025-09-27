
#include <iostream>
#include <iomanip>
#include <vector>
#include "lib/AbstractClasses.h"
#include "lib/FinancialProducts.h"
using std::string;

class EquityPortfolio : AbstractInvestmentPortfolio{
    public:
        Equity Product;
        EquityPortfolio(string ticker,double quantity,double execution_price){
            Product.ticker = ticker;
            Product.execution_price = execution_price;
            Product.quantity = quantity;
        }

        double current_valuation(double last_closing_px){
            double current_value = Product.quantity * (last_closing_px - Product.execution_price);
            return current_value;
        }
};

class DerivativesPortfolio : AbstractInvestmentPortfolio{
    public:
        DerivativesContract Product;
        DerivativesPortfolio(string ticker, double strike_price,int contract_size,double time_to_expire ){
            Product.ticker = ticker;
            Product.strike_price = strike_price;
            Product.time_to_expiry = time_to_expire;
            Product.contract_size = contract_size;
        }

        double current_valuation(double last_closing_px){
            // Options have an intrinsic value 
            if (last_closing_px > Product.strike_price){
                return -1.0;
            }else if (last_closing_px == Product.strike_price)
            {
                return 0.0;
            }else{
                return last_closing_px - Product.strike_price;
            }

        }
    };

class InvestmentPortfolio : AbstractInvestmentPortfolio {
    public:
        InvestmentPortfolio( );
};

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