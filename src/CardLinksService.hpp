#ifndef CARDLINKSSERVICE_HPP
#define CARDLINKSSERVICE_HPP

#include "CardLink.hpp"
#include "CreditCard.hpp"

#include <stdexcept>
#include <string>
#include <vector>

class CardLinksService {
public:
    /**
     * Adds a card to the linking system.
     * Returns true if successful, else returns false
     */
    virtual bool addCreditCard(const CreditCard &creditCard) = 0;

    /**
     * Links two cards.
     * Returns true if successful, else returns false
     */
    virtual bool linkCreditCards(std::string cardId1, std::string cardId2, std::string reason) = 0;

    /**
     * Deletes link record.
     * Returns true if successful, else returns false
     */
    virtual bool delLinkCreditCard(std::string groupId) = 0;

    /**
     * Swaps the two most top level cards of a link group.
     * Returns true if successful, else returns false
     */
    virtual bool swap(std::string groupId) = 0;

    /**
     * Get list of links in order top to bottom.
     * Returns list of card links if successful, else returns empty vector
     */
    virtual std::vector<CardLink> getLinkChain(std::string groupId) = 0;
};

#endif
