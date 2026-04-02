#ifndef CARDLINK_HPP
#define CARDLINK_HPP

#include <string>

class CardLink {
public:
    CardLink();

    CardLink(const std::string &primaryCardId, const std::string &linkedCardId, const std::string &groupId, const std::string &reason);

    std::string getPrimaryCardId() const;

    std::string getLinkedCardId() const;

    std::string getGroupId() const;

    std::string getReason() const;

    void setPrimaryCardId(const std::string &primaryCardId);

    void setLinkedCardId(const std::string &linkedCardId);

    void setGroupId(const std::string &groupId);

    void setReason(const std::string &reason);

    bool operator==(const CardLink &cardLink) const;

private:
    std::string primaryCardId;

    std::string linkedCardId;

    std::string groupId;

    std::string reason;
};

#endif
