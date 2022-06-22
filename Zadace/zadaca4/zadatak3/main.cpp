#include <iostream>
#include "bankAcc.hpp"

int main(void) {
  BankAcc account;

  while (1) {
    account.printMenu();

    switch (account.getOption()) {
      case 1:
        account.newTransaction();
        break;

      case 2:
        account.applyTransaction();
        break;

      case 3:
        account.printPendingTransaction();
        break;

      case 4:
        account.discardTransaction();
        break;

      case 5:
        std::cout << "Current balance" << account.getBalance() << std::endl;

      case 6:
        return 0;
        break;
    }
  }
  return 0;
}
