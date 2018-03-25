/**
 *  BlockChain ADT and Test : private implementation / algorithms
 *  
 *  COMP220: Assignment 3
 *  Author: Joshua Yeh  
 *  Date: Feb. 24, 2018
 */

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

/***********************
 * BLOCKCHAIN private implementation details
 ***********************/
const int DEFAULT_DIFFICULTY = 2;              // Default difficulty for hashing puzzles, increase to make mining harder

/*typedef struct {
    Block_t* head;
    Block_t* tail;
} BlockChain;
*/

/*
 * Constructor - return a new, empty BlockChain 
 * POST:  bcLen(chain) == 0
 */
BlockChain bcNew( ){
    BlockChain chain;
    chain.head=NULL;
    chain.tail=NULL;
}

/*
 * Destructor - remove all data and free all memory associated with the chain 
 * POST: bcLen(chain) == 0
 */
void bcDelete( BlockChain *chain ){
    Block_t* cur = chain->head;
    while (cur != NULL){
        cur = cur->next;
        free(chain->head);     //free memory and data
        chain->head=cur;
    }
    chain->head=NULL;
    chain->tail=NULL;
} 


/*
 * Print a text representation of this chain on STDOUT
 */
void bcPrint( const BlockChain chain ){
    Block_t* cur = chain.head;
    printf("---BlockChain---\n");
	while(cur!=NULL)
	{
		printf("[Block %d]-->",cur->id);
		cur = cur->next;
	}
	printf("\n----------------\n");
}

/*
 * Return the number of Blocks in the chain
 */
int bcLen( const BlockChain chain ){
    int count=0;
    Block_t* cur = chain.head;
    while (cur != NULL){
        count++;
        cur = cur->next;
    }
    return count;
}


/*
 *  Return true iff blkIsValid(block) for every block in the chain
 */
bool chainIsValid(const BlockChain chain){
    Block_t* cur = chain.head;
    while (cur != NULL){
        if(blkIsValid(*cur)==false){
            return false;
        }
        cur = cur->next;
    }
    return true;
}


/*
 * Return a pointer to the chain's tail Block
 */
Block_t* bcTail(const BlockChain chain){
    Block_t* ptr = chain.tail;
    return ptr;
}


/*
 * Append the given block to the chain 
 *    iff blkValidates(new_block, bcTail->hash, new_block->proof_of_work)
 * POST: bcTail(*chain) == new_block && chainIsValid(*new_block)
 */
void bcAppend( BlockChain *chain, Block_t* new_block ){
    if(chain->head==NULL){
        chain->head = new_block;
        chain->tail = chain->head;
    }
    else{
        Block_t* cur = chain->tail;
        cur->next = new_block;
        chain->tail = cur->next;
    }
}

/**********************************************************************************************************
 *  ---Blockchain test driver---
 *  Consider the situation: Abigail, Bob, Camilla and Drake are making transacations with each other. For the 
 *  first set of transactions, Abigail pays Bob 29.54 for building a cabinet, Bob pays Camilla 254.79 for a 
 *  ticket to Havana, and Camilla pays Drake 300.99 for breaking his phone.
 * 
 *********************************************************************************************************/


void main(){
    printf("C-Cash Test Driver\n\n");
    // Constructor Test
    printf("Test 1: Blockchain Constructor Test\n");                            // bcNew() test
    BlockChain chain = bcNew();
    printf("(BlockChain should be empty)\n");
    bcPrint(chain);
    assert(bcLen(chain)==0);
    printf("Test 1 Passed!\n\n");
    // Transacation list 1
    TransactionList list1 = tlistCreate();                                      // Recording a list of transactions
    tlistAppend(&list1, "Abigail", 29.54, "Bob");
    tlistAppend(&list1, "Bob", 254.79, "Camilla");
    tlistAppend(&list1, "Camilla", 300.99, "Drake");
    Block_t* block1 = blkCreate(list1,DEFAULT_DIFFICULTY,NULL_NONCE);           // Block created with given transactions  
    Puzzle_t puzzle = blkCreatePuzzle(*block1, NULL_HASH);                      // Block mine 
    block1->proof_of_work = puzzleMine(puzzle);                                  
    bool valid = blkIsValid(*block1);                                           // Validate the block  
    assert(valid == true);                                                      
    // Transaction list 2
    TransactionList list2 = tlistCreate();                                      // Another list of transactions
    tlistAppend(&list2, "Abigail", 200.50, "Camilla");
    tlistAppend(&list2, "Bob", 156.50, "Drake");
    Block_t* block2 = blkCreate(list1,DEFAULT_DIFFICULTY,NULL_NONCE);           // Block created with given transactions  
    Puzzle_t puzzle2 = blkCreatePuzzle(*block2, NULL_HASH);                     // Block mine 
    block2->proof_of_work = puzzleMine(puzzle2);                                  
    bool valid2 = blkIsValid(*block2);                                          // Validate the block  
    assert(valid2 == true); 
    // Append Test
    printf("Test 2: Blockchain Append Test\n");                                 // Appending block of transacation to the blockchain
    bcAppend(&chain,block1);
    bcPrint(chain);
    assert(bcLen(chain)==1);                                        
    assert(bcTail(chain) == block1 && chainIsValid(chain));
    bcAppend(&chain,block2);
    bcPrint(chain);
    assert(bcLen(chain)==2);
    assert(bcTail(chain) == block2 && chainIsValid(chain));
    printf("Test 2 Passed!\n\n");
    // Validate Test
    printf("Test 3: Blockchain Validate Test\n");                               // Validate the blockchain
    assert(chainIsValid(chain)==true);                                          // statement must be true (function returns true)
    TransactionList badList = tlistCreate();                                    // create an empty list
    Block_t* badBlock = blkCreate(badList,DEFAULT_DIFFICULTY,NULL_NONCE);       // create an unvalidated block
    bcAppend(&chain,badBlock);                                                  // add the unvalidated block to the blockchain
    assert(chainIsValid(chain)==false);                                         // statement must be true (function returns false)
    printf("Test 3 Passed!\n\n");
    // Deconstructor Test
    printf("Test 4: Blockchain Deconstrcutor Test\n");                          // bcDelete() test
    bcDelete(&chain);
    printf("(BlockChain should be empty)\n");
    bcPrint(chain);
    assert(bcLen(chain)==0);
    printf("Test 4 Passed!\n\n");
    
}






