#include "CardLink.hpp"

CardLink::CardLink() {
}

CardLink::CardLink(const std::string &primaryCardId, const std::string &linkedCardId, const std::string &groupId, const std::string &reason) {
    this->primaryCardId = primaryCardId;
    this->linkedCardId = linkedCardId;
    this->groupId = groupId;
    this->reason = reason;
}

std::string CardLink::getPrimaryCardId() const {
    return this->primaryCardId;
}

std::string CardLink::getLinkedCardId() const {
    return this->linkedCardId;
}

std::string CardLink::getGroupId() const {
    return this->groupId;
}

std::string CardLink::getReason() const {
    return this->reason;
}

void CardLink::setPrimaryCardId(const std::string &primaryCardId) {
    this->primaryCardId = primaryCardId;
}

void CardLink::setLinkedCardId(const std::string &linkedCardId) {
    this->linkedCardId = linkedCardId;
}

void CardLink::setGroupId(const std::string &groupId) {
    this->groupId = groupId;
}

void CardLink::setReason(const std::string &reason) {
    this->reason = reason;
}

bool CardLink::operator==(const CardLink &cardLink) const {
    return (this->primaryCardId == cardLink.primaryCardId) &&
        (this->linkedCardId == cardLink.linkedCardId) &&
        (this->groupId == cardLink.groupId) &&
        (this->reason == cardLink.reason);
}
