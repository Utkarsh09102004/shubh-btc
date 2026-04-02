#include "CreditCard.hpp"

CreditCard::CreditCard() {
}

CreditCard::CreditCard(const std::string &id, const std::string &cardNumber, const std::string &issuer, Card::CreditCardState state) {
    this->id = id;
    this->cardNumber = cardNumber;
    this->issuer = issuer;
    this->state = state;
}

std::string CreditCard::getId() const {
    return this->id;
}

std::string CreditCard::getCardNumber() const {
    return this->cardNumber;
}

std::string CreditCard::getIssuer() const {
    return this->issuer;
}

Card::CreditCardState CreditCard::getState() const {
    return this->state;
}

void CreditCard::setId(const std::string &id) {
    this->id = id;
}

void CreditCard::setCardNumber(const std::string &cardNumber) {
    this->cardNumber = cardNumber;
}

void CreditCard::setIssuer(const std::string &issuer) {
    this->issuer = issuer;
}

void CreditCard::setState(Card::CreditCardState state) {
    this->state = state;
}
