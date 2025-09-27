
#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <vector>

struct Equity{
    std::string ticker;
    double quantity;
    double execution_price;
};

struct DerivativesContract{
    std::string ticker;
    double strike_price;
    int contract_size;
    double time_to_expiry;
};


struct Deposit{
    std::string bank_name;
    int account_number;
    double current_value;
    double rate_of_interest;
};

#endif