#include "CardLinksServiceImpl.hpp"

#include <stdexcept>

bool CardLinksServiceImpl::addCreditCard(const CreditCard &creditCard) {
    throw std::runtime_error("Not implemented");
    return true;
}

bool CardLinksServiceImpl::linkCreditCards(std::string cardId1, std::string cardId2, std::string reason) {
    throw std::runtime_error("Not implemented");
    return true;
}

bool CardLinksServiceImpl::delLinkCreditCard(std::string groupId) {
    throw std::runtime_error("Not implemented");
    return true;
}

bool CardLinksServiceImpl::swap(std::string groupId) {
    throw std::runtime_error("Not implemented");
    return true;
}

std::vector<CardLink> CardLinksServiceImpl::getLinkChain(std::string groupId) {
    throw std::runtime_error("Not implemented");
    return {};
}
