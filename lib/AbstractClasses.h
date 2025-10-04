#ifndef FINANCE_H
#define FINANCE_H


class AbstractInvestmentPortfolio{
    virtual double current_valuation() = 0;
};
#endif // FINANCE_H