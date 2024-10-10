// #include <gtest/gtest.h>

// #include "account.hpp"
// #include "auditLog.hpp"
// #include "transaction.hpp"
// #include "database.hpp"

// // Validate transaction with a sufficient balance
// TEST(TransactionTest, ValidateTransactionSuccess) {
//     Database db("host=localhost port=5432 dbname=castle user=postgres password=postgresql!");
//     Account sender(db, "V_trans_success_sender", 5000.0, "hashed_password");
//     Account receiver(db,"V_trans_success_receiver", 1000.0, "hashed_password");
//     Transaction transaction(db);

//     // Validate transaction with a sufficient balance
//     ASSERT_TRUE(transaction.ValidateTransaction(sender, receiver, 2000.0));
// }

// // Validate transaction with an insufficient balance
// TEST(TransactionTest, ValidateTransactionFail) {
//     Database db("host=localhost port=5432 dbname=castle user=postgres password=postgresql!");
//     Account sender(db,"V_trans_fail_sender", 500.0, "hashed_password");
//     Account receiver(db,"V_trans_fail_receiver", 1000.0, "hashed_password");
//     Transaction transaction(db);

//     ASSERT_FALSE(transaction.ValidateTransaction(sender, receiver, 2000.0));
// }

// // Process a successful transaction
// TEST(TransactionTest, ProcessTransactionSuccess) {
//     Database db("host=localhost port=5432 dbname=castle user=postgres password=postgresql!");
//     Account sender(db,"P_trans_success_sender", 5000.0, "hashed_password");
//     Account receiver(db,"P_trans_success_receiver", 1000.0, "hashed_password");
//     Transaction transaction(db);

//     transaction.ProcessTransaction(sender, receiver, 2000.0);

//     // Verify balances after the transaction
//     EXPECT_EQ(sender.GetBalance(), 3000.0);  // Sender's balance should decrease
//     EXPECT_EQ(receiver.GetBalance(), 3000.0);  // Receiver's balance should increase
// }

// // Attempt to process a transaction with insufficient funds
// TEST(TransactionTest, ProcessTransactionFail) {
//     Database db("host=localhost port=5432 dbname=castle user=postgres password=postgresql!");
//     Account sender(db,"P_trans_fail_sender", 500.0, "hashed_password");
//     Account receiver(db,"P_trans_fail_receiver", 1000.0, "hashed_password");
//     Transaction transaction(db);

    
//     transaction.ProcessTransaction(sender, receiver, 2000.0);

//     // Verify that balances remain unchanged
//     EXPECT_EQ(sender.GetBalance(), 500.0);
//     EXPECT_EQ(receiver.GetBalance(), 1000.0);
// }


// // // Process the transaction and log it
// // TEST(TransactionTest, LogTransactionTest) {
// //     Database db("host=localhost port=5432 dbname=castle user=postgres password=postgresql!");
// //     Account sender(db,"John Doe", 5000.0, "hashed_password");
// //     Account receiver(db,"Jane Doe", 1000.0, "hashed_password");
// //     Transaction transaction(db);    
// //     transaction.ProcessTransaction(sender, receiver, 1000.0);

// //     SUCCEED();
// // }
