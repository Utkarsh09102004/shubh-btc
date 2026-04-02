# [CPP] Credit Card Management System: Card Linking

## Question Description

CRED is a Credit Card Management System, designed for members to link their newly issued credit cards with their previous ones. This feature is especially useful when the new card serves as a replacement for an older card, which may be due to reasons such as theft, loss, or expiration. The system is also equipped to keep track of the statement and payment histories of all linked cards.

The connection between two credit cards in this system is characterized by these details:

- `primary_card_id`: Identifier for the newly issued card.
- `linked_card_id`: Identifier for the previous card that was stolen, lost, or expired.
- `reason`: The cause for the card's replacement, such as stolen, lost, or expired.
- `group_id`: Identifier for the most recent card in the link sequence. For instance, in a link sequence of `A -> B -> C`, `A` is the `group_id` for both links (`A -> B` and `B -> C`).

## Functionalities To Be Supported

- Add Card: Incorporate a new card into the system with its specific details.
- Link Cards: Connect two existing cards in the system, ensuring that `card1` is not already linked to another card and `card2` does not have any other linked cards (to prevent branching).
- Delink Cards: Remove the link of a card if it is the first card in a chain.
- Swap Cards: Exchange a card with the second card in the chain, provided it is the first card in the sequence.
- Fetch Link Chain: Retrieve and display the sequence of linked cards in order, based on a given `group_id`.

It is important to note that user interactions are limited to the first card in a link chain. For example, in a chain `A -> B -> C`, operations on card `B` are restricted, but all operations on card `A` are permissible.

## Expectations

- Please go through the template code which is shared along with the project before you start your implementation.
- Identify all the remaining entities and attributes required for the above functionality.
- Please don't create REST APIs or any UI for the same.
- Please don't use any database or data stores for this. Suitable in-memory data structures can be used such as list, map or dictionary.
- Please test the functionality using unit test cases.
- The focus is on the core functionality and how it is implemented v/s how it is presented (UI or API structure).
- Use coding best practices (SOLID, DRY, etc.) and ensure that code written is modular and extensible (to accommodate any future changes in functionality).

## Important Points

- Template code for the project is present in the repository, please go through the entire code before starting.
- Appropriate comments are added for more context and understanding. Please go through the comments as well before starting.
- All the high level entities are listed down in the template code.
- Interfaces are provided in the template code, please add implementation details for the same.
- Please make sure to run the test cases after the implementation as overall scoring is based on running test cases as well, apart from the quality of code.
- Submissions will be evaluated based on functional correctness, clean code, use of best coding practices and principles.
