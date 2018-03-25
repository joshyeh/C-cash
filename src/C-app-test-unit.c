/**********************************************************************************************************
*  --- Automated C-cash unit test driver ---
*  COMP220: Assignment 3
*  Author: Joshua Yeh  
*  Date: Feb. 24, 2018
* 
*  Consider the situation: Abigail, Bob, Camilla and Drake are making transacations with each other. For the 
*  first set of transactions, Abigail pays Bob 29.54 for building a cabinet, Bob pays Camilla 254.79 for a 
*  ticket to Havana, and Camilla pays Drake 300.99 for breaking his phone. For the second set of transactions,
*  Abigail pays Camilla 200.50 for buying food and snacks, and Bob pays Drake 156.50 for drinks.
* 
*  Given the situation, the test driver uses the data given to run basic tests based on the blockchain ADT.  
* 
*********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "trnslist.h"
#include "puzzle.h"
#include "block.h"
#include "blockchain.h"

const int DEFAULT_DIFFICULTY = 2;              // Default difficulty for hashing puzzles, increase to make mining harder

/*
* Run a single test case
* Report on failed test
* Return 0 if test successful, 1 otherwise
*/
int run_test(long int result, long int expected, char* msg) 
{
   if (result != expected)
   {
      printf("\nTest failed: %s \n\tFunction returned %ld but expected %ld\n", msg, result, expected);
      return(1);
   }
   else{
       printf("Test Passed!\n");
       return(0);
   }
}


/*
*   Using the given situation, run basic unit test cases.
*/
void main(){
    int failedCounter = 0;
    printf("Automated C-cash unit test driver\n\n");
   
    // Constructor Test
    printf("Test 1: Blockchain Constructor Test\n");                            // bcNew() test
    BlockChain chain = bcNew();
    printf("(BlockChain should be empty)\n");
    bcPrint(chain);
    failedCounter += run_test(bcLen(chain),0,"Blockchain is not empty");
   
   
    // Transacation list 1
    TransactionList list1 = tlistCreate();                                      // First set of transactions
    tlistAppend(&list1, "Abigail", 29.54, "Bob");
    tlistAppend(&list1, "Bob", 254.79, "Camilla");
    tlistAppend(&list1, "Camilla", 300.99, "Drake");
    Block_t* block1 = blkCreate(list1,DEFAULT_DIFFICULTY,NULL_NONCE);           // Block created with given transactions  
    Puzzle_t puzzle = blkCreatePuzzle(*block1, NULL_HASH);                      // Block mine 
    block1->proof_of_work = puzzleMine(puzzle);                                  
    bool valid = blkIsValid(*block1);                                           // Validate the block  
    assert(valid == true);                                                      
   
    // Transaction list 2
    TransactionList list2 = tlistCreate();                                      // Second set of transactions
    tlistAppend(&list2, "Abigail", 200.50, "Camilla");
    tlistAppend(&list2, "Bob", 156.50, "Drake");
    Block_t* block2 = blkCreate(list1,DEFAULT_DIFFICULTY,NULL_NONCE);           // Block created with given transactions  
    Puzzle_t puzzle2 = blkCreatePuzzle(*block2, NULL_HASH);                     // Block mine 
    block2->proof_of_work = puzzleMine(puzzle2);                                  
    bool valid2 = blkIsValid(*block2);                                          // Validate the block  
    assert(valid2 == true); 
   
    // Append Test
    printf("\nTest 2 Part 1: Blockchain Append Test\n");                                 // Appending block of transacation to the blockchain
    bcAppend(&chain,block1);
    bcPrint(chain);
    failedCounter += run_test(bcLen(chain),1,"Blockchain didn't append block1");
    assert(bcTail(chain) == block1 && chainIsValid(chain));                              // Evaluate append post statements
    printf("Test 2 Part 2: Blockchain Append Test\n");                                   // Appending the second block of transaction to blockchain
    bcAppend(&chain,block2);
    bcPrint(chain);
    failedCounter += run_test(bcLen(chain),2,"Blockchain didn't append block2");
    assert(bcTail(chain) == block2 && chainIsValid(chain));                              // Evaluate append post statements
    
   
    // Validate Test
    printf("\nTest 3 Part 1: Blockchain Validate Test\n");                                                          // Validate the blockchain
    failedCounter += run_test(chainIsValid(chain),true,"The Blockchain isn't validated");
    printf("Test 3 Part 2: Blockchain Validate Test\n");                                                            // Checks if the function can determine a unvalidated block in the blockchain
    TransactionList badList = tlistCreate();                                                                        // create an empty list
    Block_t* badBlock = blkCreate(badList,DEFAULT_DIFFICULTY,NULL_NONCE);                                           // create an unvalidated block
    bcAppend(&chain,badBlock);                                                                                      // add the unvalidated block to the blockchain
    failedCounter += run_test(chainIsValid(chain),false,"The Blockchain didn't detect the unvalidated block");      // statement must be true (function returns false)
    
   
    // Deconstructor Test
    printf("\nTest 4: Blockchain Deconstrcutor Test\n");                                // bcDelete() test
    bcDelete(&chain);
    printf("(BlockChain should be empty)\n");
    bcPrint(chain);
    failedCounter += run_test(bcLen(chain),0,"Blockchain didn't delete properly");
    
    
    printf("\n\nUnit Test Suite Complete: ");                                           // print result
    if (failedCounter == 0){
         printf("ALL TESTS PASSED\n");
    }
    else{ 
        printf("FAILED %d TESTS\n", failedCounter);
    }
    
}