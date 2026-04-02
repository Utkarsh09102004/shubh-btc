#include "include/CardLinksServiceImpl.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

namespace {
bool expect(bool condition, const std::string &message) {
    if (!condition) {
        std::cerr << "FAILED: " << message << std::endl;
        return false;
    }

    return true;
}
}

int main()
{
    CardLinksServiceImpl service;

    const bool addedA = service.addCreditCard(CreditCard("A", "4111111111111111", "VISA", Card::active));
    const bool addedB = service.addCreditCard(CreditCard("B", "4222222222222222", "VISA", Card::inactive));
    const bool addedC = service.addCreditCard(CreditCard("C", "4333333333333333", "MASTERCARD", Card::inactive));
    const bool linkedBC = service.linkCreditCards("B", "C", "expired");
    const bool linkedAB = service.linkCreditCards("A", "B", "lost");

    std::vector<CardLink> linkChain = service.getLinkChain("A");

    const bool smokePassed =
        expect(addedA, "card A should be added") &&
        expect(addedB, "card B should be added") &&
        expect(addedC, "card C should be added") &&
        expect(linkedBC, "B should link to C") &&
        expect(linkedAB, "A should link to B") &&
        expect(linkChain.size() == 2, "chain headed by A should contain two links") &&
        expect(linkChain[0] == CardLink("A", "B", "A", "lost"), "first link should be A -> B") &&
        expect(linkChain[1] == CardLink("B", "C", "A", "expired"), "second link should be B -> C with updated group");

    if (!smokePassed) {
        return EXIT_FAILURE;
    }

    std::cout << "Smoke run passed" << std::endl;
    return EXIT_SUCCESS;
}
