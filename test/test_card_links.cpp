#define BOOST_TEST_MODULE card_links_tests

#include <boost/test/included/unit_test.hpp>

#include "../src/include/CardLinksServiceImpl.hpp"

#include <vector>

BOOST_AUTO_TEST_SUITE(tests_suite)

BOOST_AUTO_TEST_CASE(testAddSingleCreditCard)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard("1", "1234", "HDFC Bank", Card::active);

    BOOST_CHECK_EQUAL(true, cardLinksService.addCreditCard(creditCard));
}

BOOST_AUTO_TEST_CASE(testAddTwoCardsWithDifferentIdsDifferentCardNumbers)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);

    BOOST_CHECK_EQUAL(true, cardLinksService.addCreditCard(creditCard1));
    BOOST_CHECK_EQUAL(true, cardLinksService.addCreditCard(creditCard2));
}

BOOST_AUTO_TEST_CASE(testAddTwoCardsWithSameIdsSameCardNumbers)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("1", "1234", "HDFC Bank", Card::active);

    BOOST_CHECK_EQUAL(true, cardLinksService.addCreditCard(creditCard1));
    BOOST_CHECK_EQUAL(false, cardLinksService.addCreditCard(creditCard2));
}

BOOST_AUTO_TEST_CASE(testAddTwoCardsWithSameIdsDifferentCardNumbers)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("1", "2345", "HDFC Bank", Card::active);

    BOOST_CHECK_EQUAL(true, cardLinksService.addCreditCard(creditCard1));
    BOOST_CHECK_EQUAL(false, cardLinksService.addCreditCard(creditCard2));
}

BOOST_AUTO_TEST_CASE(testAddTwoCardsWithDifferentIdsSameCardNumbers)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "1234", "HDFC Bank", Card::active);

    BOOST_CHECK_EQUAL(true, cardLinksService.addCreditCard(creditCard1));
    BOOST_CHECK_EQUAL(false, cardLinksService.addCreditCard(creditCard2));
}

BOOST_AUTO_TEST_CASE(testLinkCreditCardsWithSameIssuer)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);

    BOOST_CHECK_EQUAL(true, cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random"));
}

BOOST_AUTO_TEST_CASE(testLinkCreditCardsWithDifferentIssuer)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "SBI Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);

    BOOST_CHECK_EQUAL(false, cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random"));
}

BOOST_AUTO_TEST_CASE(testLinkThreeCardsWithSameIssuer)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);
    CreditCard creditCard3("3", "3456", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.addCreditCard(creditCard3);

    BOOST_CHECK_EQUAL(true, cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random"));
    BOOST_CHECK_EQUAL(true, cardLinksService.linkCreditCards(creditCard3.getId(), creditCard1.getId(), "Random"));
}

BOOST_AUTO_TEST_CASE(testLinkThreeCardsWithSameIssuerButLinkBottom)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);
    CreditCard creditCard3("3", "3456", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.addCreditCard(creditCard3);

    BOOST_CHECK_EQUAL(true, cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random"));
    BOOST_CHECK_EQUAL(false, cardLinksService.linkCreditCards(creditCard3.getId(), creditCard2.getId(), "Random"));
}

BOOST_AUTO_TEST_CASE(testLinkFourCardsWithLastLinkAsInvalidLink)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);
    CreditCard creditCard3("3", "3456", "HDFC Bank", Card::active);
    CreditCard creditCard4("4", "4567", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.addCreditCard(creditCard3);
    cardLinksService.addCreditCard(creditCard4);

    BOOST_CHECK_EQUAL(true, cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random"));
    BOOST_CHECK_EQUAL(true, cardLinksService.linkCreditCards(creditCard3.getId(), creditCard4.getId(), "Random"));
    BOOST_CHECK_EQUAL(false, cardLinksService.linkCreditCards(creditCard2.getId(), creditCard3.getId(), "Random"));
}

BOOST_AUTO_TEST_CASE(testDelLinkingCard)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random");

    BOOST_CHECK_EQUAL(true, cardLinksService.delLinkCreditCard(creditCard1.getId()));
}

BOOST_AUTO_TEST_CASE(testDelLinkingByInvalidGroupId)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random");

    BOOST_CHECK_EQUAL(false, cardLinksService.delLinkCreditCard(creditCard2.getId()));
}

BOOST_AUTO_TEST_CASE(testDelLinkingWithNoExistingLinks)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);

    BOOST_CHECK_EQUAL(false, cardLinksService.delLinkCreditCard(creditCard1.getId()));
    BOOST_CHECK_EQUAL(false, cardLinksService.delLinkCreditCard(creditCard2.getId()));
}

BOOST_AUTO_TEST_CASE(testDelLinkingWithThreeCards)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);
    CreditCard creditCard3("3", "3456", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.addCreditCard(creditCard3);

    cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random");
    cardLinksService.linkCreditCards(creditCard3.getId(), creditCard1.getId(), "Random");

    BOOST_CHECK_EQUAL(false, cardLinksService.delLinkCreditCard(creditCard1.getId()));
    BOOST_CHECK_EQUAL(true, cardLinksService.delLinkCreditCard(creditCard3.getId()));
}

BOOST_AUTO_TEST_CASE(testDelLinkingAllThreeCards)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);
    CreditCard creditCard3("3", "3456", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.addCreditCard(creditCard3);

    cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random");
    cardLinksService.linkCreditCards(creditCard3.getId(), creditCard1.getId(), "Random");

    BOOST_CHECK_EQUAL(true, cardLinksService.delLinkCreditCard(creditCard3.getId()));
    BOOST_CHECK_EQUAL(true, cardLinksService.delLinkCreditCard(creditCard1.getId()));
}

BOOST_AUTO_TEST_CASE(testCardLinkSwap)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random");

    BOOST_CHECK_EQUAL(true, cardLinksService.swap(creditCard1.getId()));
}

BOOST_AUTO_TEST_CASE(testCardLinkSwapByInvalidGroupId)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random");

    BOOST_CHECK_EQUAL(false, cardLinksService.swap(creditCard2.getId()));
}

BOOST_AUTO_TEST_CASE(testSwapWithNoLinkedCard)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);

    BOOST_CHECK_EQUAL(false, cardLinksService.swap(creditCard1.getId()));
}

BOOST_AUTO_TEST_CASE(testGetLinkChainForNoLinkedCard)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);

    BOOST_CHECK_EQUAL(0U, cardLinksService.getLinkChain(creditCard1.getId()).size());
}

BOOST_AUTO_TEST_CASE(testGetSimpleLinkedChainForTwoCards)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random");

    std::vector<CardLink> expectedCardLinks = {CardLink("1", "2", "1", "Random")};

    BOOST_CHECK_EQUAL(true, (expectedCardLinks == cardLinksService.getLinkChain(creditCard1.getId())));
    BOOST_CHECK_EQUAL(0U, cardLinksService.getLinkChain(creditCard2.getId()).size());
}

BOOST_AUTO_TEST_CASE(testGetLinkedChainForThreeCards)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);
    CreditCard creditCard3("3", "3456", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.addCreditCard(creditCard3);
    cardLinksService.linkCreditCards(creditCard2.getId(), creditCard3.getId(), "Random");
    cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random");

    BOOST_CHECK_EQUAL(0U, cardLinksService.getLinkChain(creditCard2.getId()).size());
    BOOST_CHECK_EQUAL(0U, cardLinksService.getLinkChain(creditCard3.getId()).size());

    std::vector<CardLink> expectedCardLinks = {
        CardLink("1", "2", "1", "Random"),
        CardLink("2", "3", "1", "Random")
    };

    BOOST_CHECK_EQUAL(true, (expectedCardLinks == cardLinksService.getLinkChain(creditCard1.getId())));
}

BOOST_AUTO_TEST_CASE(testGetLinkChainWhenLinksAreLinkedAndDeLinked)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random");
    cardLinksService.delLinkCreditCard(creditCard1.getId());

    BOOST_CHECK_EQUAL(0U, cardLinksService.getLinkChain(creditCard1.getId()).size());
}

BOOST_AUTO_TEST_CASE(testGetLinkChainForLinkedAndSwappedCards)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random");

    cardLinksService.swap(creditCard1.getId());

    BOOST_CHECK_EQUAL(0U, cardLinksService.getLinkChain(creditCard1.getId()).size());

    std::vector<CardLink> expectedCardLinks = {CardLink("2", "1", "2", "Random")};
    std::vector<CardLink> actualCardLinks = cardLinksService.getLinkChain(creditCard2.getId());

    BOOST_CHECK_EQUAL(true, (expectedCardLinks == actualCardLinks));
}

BOOST_AUTO_TEST_CASE(testGetLinkChainForLinkedThenSwappedThenDeLinkedThenSwappedCards)
{
    CardLinksServiceImpl cardLinksService;
    CreditCard creditCard1("1", "1234", "HDFC Bank", Card::active);
    CreditCard creditCard2("2", "2345", "HDFC Bank", Card::active);
    CreditCard creditCard3("3", "3456", "HDFC Bank", Card::active);
    CreditCard creditCard4("4", "4567", "HDFC Bank", Card::active);

    cardLinksService.addCreditCard(creditCard1);
    cardLinksService.addCreditCard(creditCard2);
    cardLinksService.addCreditCard(creditCard3);
    cardLinksService.addCreditCard(creditCard4);
    cardLinksService.linkCreditCards(creditCard3.getId(), creditCard4.getId(), "Random");
    cardLinksService.linkCreditCards(creditCard2.getId(), creditCard3.getId(), "Random");
    cardLinksService.linkCreditCards(creditCard1.getId(), creditCard2.getId(), "Random");

    BOOST_CHECK_EQUAL(0U, cardLinksService.getLinkChain(creditCard2.getId()).size());
    BOOST_CHECK_EQUAL(0U, cardLinksService.getLinkChain(creditCard3.getId()).size());
    BOOST_CHECK_EQUAL(0U, cardLinksService.getLinkChain(creditCard4.getId()).size());

    std::vector<CardLink> expectedCardLinks = {
        CardLink("1", "2", "1", "Random"),
        CardLink("2", "3", "1", "Random"),
        CardLink("3", "4", "1", "Random")
    };
    std::vector<CardLink> actualCardLinks = cardLinksService.getLinkChain(creditCard1.getId());
    BOOST_CHECK_EQUAL(true, (expectedCardLinks == actualCardLinks));

    cardLinksService.swap(creditCard1.getId());
    expectedCardLinks = {
        CardLink("2", "1", "2", "Random"),
        CardLink("1", "3", "2", "Random"),
        CardLink("3", "4", "2", "Random")
    };
    actualCardLinks = cardLinksService.getLinkChain(creditCard2.getId());
    BOOST_CHECK_EQUAL(true, (expectedCardLinks == actualCardLinks));

    cardLinksService.delLinkCreditCard(creditCard2.getId());
    expectedCardLinks = {
        CardLink("1", "3", "1", "Random"),
        CardLink("3", "4", "1", "Random")
    };
    actualCardLinks = cardLinksService.getLinkChain(creditCard1.getId());
    BOOST_CHECK_EQUAL(true, (expectedCardLinks == actualCardLinks));

    cardLinksService.swap(creditCard1.getId());
    expectedCardLinks = {
        CardLink("3", "1", "3", "Random"),
        CardLink("1", "4", "3", "Random")
    };
    actualCardLinks = cardLinksService.getLinkChain(creditCard3.getId());
    BOOST_CHECK_EQUAL(true, (expectedCardLinks == actualCardLinks));
}

BOOST_AUTO_TEST_SUITE_END()
