#ifndef CARDLINKSSERVICEIMPL_HPP
#define CARDLINKSSERVICEIMPL_HPP

#include "CardLinksService.hpp"
#include <algorithm>
#include <map>

class CardLinksServiceImpl : public CardLinksService {
public:
    bool addCreditCard(const CreditCard &creditCard) override;

    bool linkCreditCards(std::string cardId1, std::string cardId2, std::string reason) override;

    bool delLinkCreditCard(std::string groupId) override;

    bool swap(std::string groupId) override;

    std::vector<CardLink> getLinkChain(std::string groupId) override;

private:
};

#endif
