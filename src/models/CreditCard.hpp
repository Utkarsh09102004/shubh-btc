#ifndef CREDITCARD_HPP
#define CREDITCARD_HPP

#include "../constants/Card.hpp"

#include <string>

class CreditCard {
public:
    CreditCard();

    CreditCard(const std::string &id, const std::string &cardNumber, const std::string &issuer, Card::CreditCardState state);

    std::string getId() const;

    std::string getCardNumber() const;

    std::string getIssuer() const;

    Card::CreditCardState getState() const;

    void setId(const std::string &id);

    void setCardNumber(const std::string &cardNumber);

    void setIssuer(const std::string &issuer);

    void setState(Card::CreditCardState state);

private:
    std::string id;

    std::string cardNumber;

    std::string issuer;

    Card::CreditCardState state;
};

#endif
