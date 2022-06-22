#include "bankAcc.hpp"
#include <iostream>

void BankAcc::printMenu() {
  std::cout << "-----------------" << std::endl;
  std::cout << "Actions:" << std::endl;
  std::cout << "\t1. New transaction" << std::endl;
  std::cout << "\t2. Apply transaction" << std::endl;
  std::cout << "\t3. Pending transaction" << std::endl;
  std::cout << "\t4. Discard pending transaction" << std::endl;
  std::cout << "\t5. Balance" << std::endl;
  std::cout << "\t6. Exit" << std::endl;
}

short BankAcc::getOption() {
  short option;
  do {
    std::cout << "Your choice: " << std::endl;
    std::cin >> option;
    if (option < 1 || option > 6) {
      std::cout << "No such option ! Try again" << std::endl;
    }
  } while (option < 1 || option > 6);
  return option;
}

void BankAcc::newTransaction() {
  Transaction temp;

  std::cout << "Enter the transaction amount: " << std::endl;
  std::cin >> temp.amount;

  std::cout << "Enter the transaction date: " << std::endl;
  std::cin >> temp.date;

  std::cout << "Enter the transaction time: " << std::endl;
  std::cin >> temp.time;

  trans_queue.push(temp);

  std::cout << "Successfull !" << std::endl;
}

void BankAcc::applyTransaction() {
  try {
    balance_ += trans_queue.pop().amount;
    std::cout << "Transaction successfully applied" << std::endl;
  } catch (std::underflow_error e) {
    std::cout << "No pending transactions !" << std::endl;
  }
}

void BankAcc::printPendingTransaction() {
  if (trans_queue.empty()) {
    std::cout << "No pending transactions !" << std::endl;
    return;
  }
  Transaction t = trans_queue.top();
  std::cout << "Pending transaction: " << std::endl;
  std::cout << "\tAmount: " << t.amount << std::endl;
  std::cout << "\tDate: " << t.date << std::endl;
  std::cout << "\tTime: " << t.time << std::endl;
}

void BankAcc::discardTransaction(){
  try{
    trans_queue.pop();
    std::cout << "Transaction successfully discarded!" << std::endl;
  }
  catch(std::underflow_error e){
    std::cout << "No pending transactions !" << std::endl;
  }
}

double BankAcc::getBalance(){
  return balance_;
}
