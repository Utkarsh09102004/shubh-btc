#include "CardLinksServiceImpl.hpp"

bool CardLinksServiceImpl::addCreditCard(const CreditCard &creditCard) {
    if (creditCard.getId().empty()) {
        return false;
    }

    if (this->cardsById.count(creditCard.getId()) > 0) {
        return false;
    }

    this->cardsById[creditCard.getId()] = creditCard;
    return true;
}

bool CardLinksServiceImpl::linkCreditCards(std::string cardId1, std::string cardId2, std::string reason) {
    if (cardId1.empty() || cardId2.empty() || reason.empty() || cardId1 == cardId2) {
        return false;
    }

    if (!this->isKnownCard(cardId1) || !this->isKnownCard(cardId2)) {
        return false;
    }

    if (this->hasIncomingLink(cardId1) || this->hasOutgoingLink(cardId1)) {
        return false;
    }

    if (this->hasIncomingLink(cardId2)) {
        return false;
    }

    this->linkByPrimaryCardId[cardId1] = CardLink(cardId1, cardId2, cardId1, reason);
    this->primaryCardIdByLinkedCardId[cardId2] = cardId1;
    this->updateGroupIdsFromHead(cardId1);
    return true;
}

bool CardLinksServiceImpl::delLinkCreditCard(std::string groupId) {
    if (!this->isHeadCard(groupId) || !this->hasOutgoingLink(groupId)) {
        return false;
    }

    const CardLink firstLink = this->linkByPrimaryCardId[groupId];
    const std::string newHead = firstLink.getLinkedCardId();

    this->linkByPrimaryCardId.erase(groupId);
    this->primaryCardIdByLinkedCardId.erase(newHead);
    this->updateGroupIdsFromHead(newHead);
    return true;
}

bool CardLinksServiceImpl::swap(std::string groupId) {
    if (!this->isHeadCard(groupId) || !this->hasOutgoingLink(groupId)) {
        return false;
    }

    const CardLink firstLink = this->linkByPrimaryCardId[groupId];
    const std::string firstCardId = groupId;
    const std::string secondCardId = firstLink.getLinkedCardId();

    const bool hasThirdCard = this->hasOutgoingLink(secondCardId);
    CardLink secondLink;
    if (hasThirdCard) {
        secondLink = this->linkByPrimaryCardId[secondCardId];
    }

    this->linkByPrimaryCardId.erase(firstCardId);
    this->primaryCardIdByLinkedCardId.erase(secondCardId);

    if (hasThirdCard) {
        this->linkByPrimaryCardId.erase(secondCardId);
        this->primaryCardIdByLinkedCardId.erase(secondLink.getLinkedCardId());
    }

    this->linkByPrimaryCardId[secondCardId] = CardLink(
        secondCardId,
        firstCardId,
        secondCardId,
        firstLink.getReason());
    this->primaryCardIdByLinkedCardId[firstCardId] = secondCardId;

    if (hasThirdCard) {
        this->linkByPrimaryCardId[firstCardId] = CardLink(
            firstCardId,
            secondLink.getLinkedCardId(),
            secondCardId,
            secondLink.getReason());
        this->primaryCardIdByLinkedCardId[secondLink.getLinkedCardId()] = firstCardId;
    }

    this->updateGroupIdsFromHead(secondCardId);
    return true;
}

std::vector<CardLink> CardLinksServiceImpl::getLinkChain(std::string groupId) {
    std::vector<CardLink> linkChain;
    if (!this->isHeadCard(groupId)) {
        return linkChain;
    }

    std::string currentCardId = groupId;
    while (this->hasOutgoingLink(currentCardId)) {
        const CardLink &currentLink = this->linkByPrimaryCardId[currentCardId];
        linkChain.push_back(currentLink);
        currentCardId = currentLink.getLinkedCardId();
    }

    return linkChain;
}

bool CardLinksServiceImpl::isKnownCard(const std::string &cardId) const {
    return this->cardsById.count(cardId) > 0;
}

bool CardLinksServiceImpl::hasIncomingLink(const std::string &cardId) const {
    return this->primaryCardIdByLinkedCardId.count(cardId) > 0;
}

bool CardLinksServiceImpl::hasOutgoingLink(const std::string &cardId) const {
    return this->linkByPrimaryCardId.count(cardId) > 0;
}

bool CardLinksServiceImpl::isHeadCard(const std::string &cardId) const {
    return this->isKnownCard(cardId) && !this->hasIncomingLink(cardId);
}

void CardLinksServiceImpl::updateGroupIdsFromHead(const std::string &groupId) {
    if (!this->isKnownCard(groupId)) {
        return;
    }

    std::string currentCardId = groupId;
    while (this->hasOutgoingLink(currentCardId)) {
        CardLink &currentLink = this->linkByPrimaryCardId[currentCardId];
        currentLink.setGroupId(groupId);
        currentCardId = currentLink.getLinkedCardId();
    }
}
