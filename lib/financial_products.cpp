#include <vector>

struct Equity{
    std::string ticker;
    std::string company_name;
    double bid_price;
    double ask_price;
    double close_price;
};

struct Option{
    std::string ticker;
    std::string company_name;
    double strike_price;
    double current_price;
    int time_to_expiry;
};

struct Future{
    std::string ticker;
    std::string company_name;
    double strike_price;
    double current_price;
    int time_to_expiry;
};

struct Deposit{
    std::string bank_name;
    int account_number;
    double current_value;
    double rate_of_interest;
};