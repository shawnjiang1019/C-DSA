/**
 * Assignment 1 - The Wacky Store
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * There are also additional notes and clarifications on Quercus.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

// No additional imports are allowed. You can make helper functions if you wish.
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 1024

typedef struct ItemNode ItemNode;
struct ItemNode {
    char name[MAX_NAME_LENGTH];
    int count;
    ItemNode* next;
};

typedef struct Customer Customer;
struct Customer {
    char name[MAX_NAME_LENGTH];
    ItemNode* cart;
};

typedef struct CheckoutLaneNode CheckoutLaneNode;
struct CheckoutLaneNode {
    Customer* customer;

    CheckoutLaneNode* front;
    CheckoutLaneNode* back;
};

typedef struct CheckoutLane CheckoutLane;
struct CheckoutLane {
    CheckoutLaneNode* first;
    CheckoutLaneNode* last ;
};

/**
 * Function: new_item_node
 * -----------------------
 * Allocate a new ItemNode. Allocation must be done manually (with malloc or
 * calloc). Initialize all variables using the arguments provided. Assume that
 * count will always be greater than 0.
 */
ItemNode* new_item_node(char* name, int count) {
    // TODO: Complete this function.

    
    ItemNode* newNode = (ItemNode*)malloc(sizeof(ItemNode));
    newNode->count = count;
    newNode->next = NULL;
    strcpy(newNode->name, name);
    return newNode;
    
}

/**
 * Function: new_customer
 * ----------------------
 * Allocate a new Customer. Allocation must be done manually (with malloc or
 * calloc). Initialize all variables using the arguments provided.
 */
Customer* new_customer(char* name) {
    // TODO: Complete this function.

    Customer* person = (Customer*)malloc(sizeof(Customer));
    person->cart = NULL;
    strcpy(person->name, name);
    
    return person;
}

/**
 * Function: free_customer
 * -----------------------
 * Release all memory associated with a Customer back to the system. This
 * includes any items they may have had in their cart.
 */
void free_customer(Customer* customer) {
    // TODO: Complete this function.
    ItemNode* cur_item = customer->cart;
    ItemNode* next_item;

    
    cur_item = customer->cart;
    while (cur_item != NULL){
        next_item = cur_item->next;
        free(cur_item);
        cur_item = next_item;
    }
    free(customer);
    return;
}

/**
 * Function: open_new_checkout_line
 * --------------------------------
 * Allocate a new empty checkout lane. Allocation must be done manually (with
 * malloc or calloc).
 */
CheckoutLane* open_new_checkout_line() {
    CheckoutLane* new_checkout_lane = (CheckoutLane*) malloc(sizeof(CheckoutLane));
    new_checkout_lane->first = NULL;
    new_checkout_lane->last = NULL;    
    return new_checkout_lane;
}

/**
 * Function: new_checkout_node
 * ---------------------------
 * Allocate a new CheckoutLaneNode. Allocation must be done manually (with
 * malloc or calloc). Initialize all variables using the arguments provided. Do
 * not allocate a new customer; instead copy the existing reference over.
 */
    CheckoutLaneNode* new_checkout_node(Customer* customer) {
    // TODO: Complete this function.
    CheckoutLaneNode* checkout_node = (CheckoutLaneNode*) malloc(sizeof(CheckoutLaneNode));
    checkout_node->customer = customer;
    checkout_node->back = NULL;
    checkout_node->front = NULL;
    return checkout_node;
}

/**
 * Function: add_item_to_cart
 * --------------------------
 * Add an item to a customer's cart, given its name and amount.
 *
 * If the given amount is 0 or less, do nothing.
 *
 * IMPORTANT: The items in a customer's cart should always be arranged in
 * lexicographically smallest order based on the item names. Consider the use of
 * the ASCII strcmp() function from <string.h>.
 *
 * No two ItemNodes in a customer's cart can have the same name.
 * If the customer already has an ItemNode with the same item name in their
 * cart, increase the node's count by the given amount instead.
 */
void add_item_to_cart(Customer* customer, char* item_name, int amount) {
    ItemNode* item_ptr;
    ItemNode* cur_item = customer->cart;
    //if already in the cart

    if (amount <= 0){
        return;
    }
    
    while (cur_item != NULL){
        if (strcmp(cur_item->name, item_name) == 0){
            cur_item->count = cur_item->count + amount;
            return;
        }
        cur_item = cur_item->next;
    }
    
    //if cart is empty
    
    if (customer->cart == NULL){
        customer->cart = new_item_node(item_name, amount);
        return;
    }

    //if new item becomes the head of the cart

    if (strcmp(customer->cart->name, item_name) > 0){
        item_ptr = customer->cart;
        customer->cart = new_item_node(item_name, amount);
        customer->cart->next = item_ptr;
        return;
    }

    //if new item becomes tail of cart
    ItemNode* tail;
    cur_item = customer->cart;
    while (cur_item != NULL){
        
        if (cur_item->next == NULL){
            tail = cur_item;
            break;
        }
        cur_item = cur_item->next;
    }
    

    if (strcmp(tail->name, item_name) < 0){
        tail->next = new_item_node(item_name, amount);
        
        return;
    }


    //If new item is between two items

    ItemNode* newItem;
    cur_item = customer->cart;
    while (cur_item->next != NULL){
        if (strcmp(cur_item->next->name, item_name) > 0 && strcmp(cur_item->name, item_name) < 0){
            item_ptr = cur_item->next;
            newItem = new_item_node(item_name, amount);
            cur_item->next = newItem;
            newItem->next = item_ptr;
            
        }
        cur_item = cur_item->next;
        
    }
    return;
}

/**
 * Function: remove_item_from_cart
 * -------------------------------
 * Attempt to reduce the quantity of an item in a customer's cart, given its
 * name and amount.
 *
 * If no ItemNode in the customer's cart match the given item name, or the
 * amount given is <= 0, do nothing.
 *
 * If the quantity is reduced to a value less than or equal to 0, remove the
 * ItemNode from the customer's cart. This means you will need to do memory
 * cleanup as well.
 */
void remove_item_from_cart(Customer* customer, char* item_name, int amount) {
    // TODO: Complete this function.

    ItemNode* current = customer->cart;
    ItemNode* remove_this;
    bool inCart = false;

    if (amount <= 0){
        return;
    }

    while (current != NULL){
        if (strcmp(current->name, item_name) == 0 ){
            inCart = true;
            remove_this = current;
            break;
        }
        current = current->next;
    }

    
    //if item that needs to be removed is not in cart do nothing
    if (inCart == false){
        return;
    }

    //if we just need to lower the count
    if (current->count > amount){
        current->count = current->count - amount;
        return;
    }
    //if we need to remove the first item
    if (remove_this->count <= amount && remove_this == customer->cart){
        customer->cart = customer->cart->next;
        free(remove_this);
        return;
    }

    //if we need to remove anything else
    current = customer->cart;
    while (current->next != NULL){
        if (strcmp(current->next->name, item_name) == 0){
            //remove the item
            remove_this = current->next;
            current->next = remove_this->next;
            free(remove_this);
            return;
        }
        current = current->next;
    }
    return;

    //Else we need to remove

    
    

    
}

/**
 * Function: total_number_of_items
 * -------------------------------
 * Count the total number of items in a customer's cart by summing all ItemNodes
 * and their associated quantities.
 */
int total_number_of_items(Customer* customer) {
    // TODO: Complete this function.
    int total_num = 0;
    ItemNode* current;
    current = customer->cart;

    while (current != NULL){
        total_num = total_num + current->count;
        current = current->next;
    }
    return total_num;
}

/**
 * Function: queue
 * ---------------
 * A customer has finished shopping and wishes to checkout. Add the given
 * customer to the end of the given checkout lane.
 */
void queue(Customer* customer, CheckoutLane* lane) {

    
    CheckoutLaneNode* newNode = new_checkout_node(customer);
    
    //If the lane is empty
    if (lane->first == NULL && lane->last == NULL){
        lane->first = newNode;
        lane->last = newNode;
        newNode->back = NULL;
        newNode->front = NULL;
        return;
    }

    /* If the lane is non-empty

    1. set the last to the newNode
    2.make the front of the new last the old last
    */
   
    CheckoutLaneNode* oldlast = lane->last;
    lane->last = newNode;
    newNode->front = oldlast;
    

    oldlast->back = newNode;
    return;
}

/**
 * Function: process
 * -----------------
 * Serve the customer at the head of the checkout lane and return the
 * total_number_of_items() the customer had in their cart.
 *
 * The customer leaves the store after being processed. Therefore, you must also
 * free any memory associated with them.
 *
 * If this function is called on an empty lane, return 0.
 */
int process(CheckoutLane* lane) {
    int total = 0;
    if (lane->first == NULL){
        return 0;
    }


    total = total_number_of_items(lane->first->customer);
    //lane has one person:
    if (lane->first == lane->last){
        free_customer(lane->first->customer);
        
        free(lane->first);
        lane->first = NULL;
        lane->last = NULL;
        
        
        return total;
    }

    CheckoutLaneNode* ptr;
    CheckoutLaneNode* newFirst;
    //lane has multiple people
    ptr = lane->first;
    newFirst = lane->first->back;
    newFirst->front = NULL;
    lane->first = newFirst;
    free_customer(ptr->customer);
    free(ptr);




    return total;



    
}

/**
 * Function: balance_lanes
 * -----------------------
 * Move a single customer from the end of the most busy checkout lane to the end
 * of the least busy checkout lane.
 *
 * Busyness is defined as the total number of customers in a checkout lane.
 *
 * If multiple lanes have the same busyness, select the lane that comes first in
 * the CheckoutLane* array.
 *
 * If the difference between the MAX and MIN checkout lanes is <= 1, do nothing.
 *
 * If there are less than 2 lanes, do nothing.
 *
 * Return true if and only if a customer was moved; otherwise false.
 */

int get_lane_length(CheckoutLane* lane){
    int length = 0;

    CheckoutLaneNode* current = lane->last;

    while (current != NULL){
        length++;
        current = current->front;
    }

    return length;
    

}

bool balance_lanes(CheckoutLane* lanes[], int number_of_lanes) {
    
    CheckoutLane* busiest_lane;
    CheckoutLane* calmest_lane;
    int max_length = 0;
    int min_length;
    int current_length;
    //Find the busiest and calmest lanes;
    //See if there are any empty lanes


    
    for (int i = 0; i < number_of_lanes; ++i){
        current_length = get_lane_length(lanes[i]);
        if (current_length > max_length){
            max_length = current_length;
            busiest_lane = lanes[i];
        } 
    }

    min_length = max_length;
    

    for (int i = 0; i < number_of_lanes; ++i){
        current_length = get_lane_length(lanes[i]);
        if (current_length < min_length){
            min_length = current_length;
            calmest_lane = lanes[i];
        } 
    }

    
   

    if (max_length - min_length <= 1){
        return false;
    }

    
    CheckoutLaneNode* calm_old_last = calmest_lane->last; 
    CheckoutLaneNode* newLast = busiest_lane->last->front;
    if (number_of_lanes >= 2 && max_length - min_length > 1){

        if (calmest_lane->first == NULL){
            calmest_lane->last = busiest_lane->last;
            calmest_lane->first = busiest_lane->last;
            calmest_lane->last->front = NULL;
            calmest_lane->first->front = NULL;
            busiest_lane->last = newLast;
            busiest_lane->last->back = NULL;           
            return true;
        }
        calmest_lane->last = busiest_lane->last;
        
        calmest_lane->last->front = calm_old_last;
        calm_old_last->back = calmest_lane->last;
        
        calmest_lane->last->back = NULL;

        busiest_lane->last = newLast;
        
        busiest_lane->last->back = NULL;
        
        

        return true;
    }
    return false;
}

/**
 * Function: process_all_lanes
 * ---------------------------
 * Given an array of CheckoutLane*, process() each CheckoutLane a single time
 * and return the the sum of the result.
 */
int process_all_lanes(CheckoutLane* lanes[], int number_of_lanes) {
    // TODO: Complete this function.
    int total = 0;

    for (int i = 0; i < number_of_lanes; ++i){
        total = total + process(lanes[i]);
        
    }
    return total;
}

/**
 * Function: close_store
 * ---------------------
 * It's closing time. Given an array of CheckoutLane*, free all memory
 * associated with them. Any customers still left in the queue is kicked out and
 * also freed from memory.
 */

void close_lane(CheckoutLane* lane){
    CheckoutLaneNode* next = lane->last;
    CheckoutLaneNode* cur = lane->last;
    while (cur != NULL){
        next = cur->front;
        free_customer(cur->customer);
        free(cur);
        cur = next;
    }

    free(lane);
}
void close_store(CheckoutLane* lanes[], int number_of_lanes) {
    for (int i =0; i < number_of_lanes; ++i){
        close_lane(lanes[i]);
    }
}
