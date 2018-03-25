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








