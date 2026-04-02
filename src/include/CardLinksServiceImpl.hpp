#ifndef CARDLINKSSERVICEIMPL_HPP
#define CARDLINKSSERVICEIMPL_HPP

#include "CardLinksService.hpp"
#include <map>
#include <string>
#include <vector>

class CardLinksServiceImpl : public CardLinksService {
public:
    bool addCreditCard(const CreditCard &creditCard) override;

    bool linkCreditCards(std::string cardId1, std::string cardId2, std::string reason) override;

    bool delLinkCreditCard(std::string groupId) override;

    bool swap(std::string groupId) override;

    std::vector<CardLink> getLinkChain(std::string groupId) override;

private:
    bool isKnownCard(const std::string &cardId) const;

    bool hasIncomingLink(const std::string &cardId) const;

    bool hasOutgoingLink(const std::string &cardId) const;

    bool isHeadCard(const std::string &cardId) const;

    void updateGroupIdsFromHead(const std::string &groupId);

    std::map<std::string, CreditCard> cardsById;

    std::map<std::string, std::string> cardIdByCardNumber;

    std::map<std::string, CardLink> linkByPrimaryCardId;

    std::map<std::string, std::string> primaryCardIdByLinkedCardId;
};

#endif
