/**
 * Assignment 3 - Wacky Marketing
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
 *
 * Starter code:  (Updated by) Charles Xu, 2024
 *             (Originally by) William Song, Mustafa Quraish, 2020
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1024

#ifndef MAT_SIZE
#define MAT_SIZE 6  // A small graph
#endif

typedef struct user_struct {
    char name[MAX_STR_LEN];
    struct friend_node_struct *friends;
    struct brand_node_struct *brands;
    bool visited;
} User;

typedef struct friend_node_struct {
    User *user;
    struct friend_node_struct *next;
} FriendNode;

typedef struct brand_node_struct {
    char brand_name[MAX_STR_LEN];
    struct brand_node_struct *next;
} BrandNode;

typedef struct queue_struct {
    User* user;
    int length;
} Queue;

// Note: These are global variables.
FriendNode *allUsers = NULL;
int brand_adjacency_matrix[MAT_SIZE][MAT_SIZE];
char brand_names[MAT_SIZE][MAX_STR_LEN];

/**
 * Given the head of a linked list of FriendNode, this function checks if
 * a given user's name exists in the list. Returns true if the user's name
 * is found, and false otherwise.
 *
 * @param head Pointer to the head of the linked list of FriendNode.
 * @param node Pointer to the user whose name is to be searched in the list.
 * @return true if the user's name exists in the list, false otherwise.
 */
bool in_friend_list(FriendNode *head, User *node) {
    for (FriendNode *cur = head; cur != NULL; cur = cur->next) {
        if (strcmp(cur->user->name, node->name) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * Given the head of a linked list of BrandNode, this function checks if
 * a given brand's name exists in the list. Returns true if the brand's name
 * is found, and false otherwise.
 *
 * @param head Pointer to the head of the linked list of BrandNode.
 * @param name Pointer to the brand name to be searched in the list.
 * @return true if the brand's name exists in the list, false otherwise.
 */
bool in_brand_list(BrandNode *head, char *name) {
    for (BrandNode *cur = head; cur != NULL; cur = cur->next) {
        if (strcmp(cur->brand_name, name) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * Given the head of a linked list of FriendNode, this function inserts
 * a given user into the linked list in alphabetical order of names. If
 * the user already exists, no modifications are made and the original
 * list is returned. Returns the head of the new linked list after insertion.
 *
 * @param head Pointer to the head of the linked list of FriendNode.
 * @param node Pointer to the user to be inserted into the list.
 * @return Pointer to the head of the new linked list after insertion.
 */
FriendNode *insert_into_friend_list(FriendNode *head, User *node) {
    if (node == NULL) return head;

    if (in_friend_list(head, node)) {
        printf("User already in list\n");
        return head;
    }

    FriendNode *fn = calloc(1, sizeof(FriendNode));
    fn->user = node;
    fn->next = NULL;

    if (head == NULL) return fn;

    if (strcmp(head->user->name, node->name) > 0) {
        fn->next = head;
        return fn;
    }

    FriendNode *cur;
    for (cur = head;
         cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
         cur = cur->next)
        ;

    fn->next = cur->next;
    cur->next = fn;

    return head;
}

/**
 * Given the head of a linked list of BrandNode, this function inserts
 * a given brand into the linked list in alphabetical order of names. If
 * the brand already exists, no modifications are made and the original
 * list is returned. Returns the head of the new linked list after insertion.
 *
 * @param head Pointer to the head of the linked list of BrandNode.
 * @param node Pointer to the brand name to be inserted into the list.
 * @return Pointer to the head of the new linked list after insertion.
 */
BrandNode *insert_into_brand_list(BrandNode *head, char *node) {
    if (node == NULL) return head;

    if (in_brand_list(head, node)) {
        printf("Brand already in list\n");
        return head;
    }

    BrandNode *fn = calloc(1, sizeof(BrandNode));
    strcpy(fn->brand_name, node);
    fn->next = NULL;

    if (head == NULL) return fn;

    if (strcmp(head->brand_name, node) > 0) {
        fn->next = head;
        return fn;
    }

    BrandNode *cur;
    for (cur = head;
         cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
         cur = cur->next)
        ;

    fn->next = cur->next;
    cur->next = fn;

    return head;
}

/**
 * Given the head of a linked list of FriendNode, this function removes
 * a given user from the linked list. If the user does not exist in the list,
 * no modifications are made and the original list is returned. Returns the
 * head of the new linked list after deletion.
 *
 * @param head Pointer to the head of the linked list of FriendNode.
 * @param node Pointer to the user to be removed from the list.
 * @return Pointer to the head of the new linked list after deletion.
 */
FriendNode *delete_from_friend_list(FriendNode *head, User *node) {
    if (node == NULL) return head;

    if (!in_friend_list(head, node)) {
        printf("User not in list\n");
        return head;
    }

    if (strcmp(head->user->name, node->name) == 0) {
        FriendNode *temp = head->next;
        free(head);
        return temp;
    }

    FriendNode *cur;
    for (cur = head; cur->next->user != node; cur = cur->next)
        ;

    FriendNode *temp = cur->next;
    cur->next = temp->next;
    free(temp);

    return head;
}

/**
 * Given the head of a linked list of BrandNode, this function removes
 * a given brand from the linked list. If the brand does not exist in the list,
 * no modifications are made and the original list is returned. Returns the
 * head of the new linked list after deletion.
 *
 * @param head Pointer to the head of the linked list of BrandNode.
 * @param node Pointer to the brand name to be removed from the list.
 * @return Pointer to the head of the new linked list after deletion.
 */
BrandNode *delete_from_brand_list(BrandNode *head, char *node) {
    if (node == NULL) return head;

    if (!in_brand_list(head, node)) {
        printf("Brand not in list\n");
        return head;
    }

    if (strcmp(head->brand_name, node) == 0) {
        BrandNode *temp = head->next;
        free(head);
        return temp;
    }

    BrandNode *cur;
    for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
        ;

    BrandNode *temp = cur->next;
    cur->next = temp->next;
    free(temp);

    return head;
}

/**
 * Given a user, this function prints their name, friends, and liked brands.
 *
 * @param user Pointer to the user whose data is to be printed.
 */
void print_user_data(User *user) {
    printf("User name: %s\n", user->name);

    printf("Friends:\n");
    for (FriendNode *f = user->friends; f != NULL; f = f->next) {
        printf("   %s\n", f->user->name);
    }

    printf("Brands:\n");
    for (BrandNode *b = user->brands; b != NULL; b = b->next) {
        printf("   %s\n", b->brand_name);
    }
}

void print_friends(FriendNode* node){
    printf("Friends:\n");
    for (FriendNode *f = node; f != NULL; f = f->next) {
        printf("   %s\n", node->user->name);
    }
}

/**
 * Given a brand name, this function returns the index of the brand inside
 * the brand_names array. If the brand doesn't exist in the array, it
 * returns -1.
 *
 * @param name Pointer to the brand name.
 * @return The index of the brand in the brand_names array, or -1
 * if it doesn't exist.
 */
int get_brand_index(char *name) {
    for (int i = 0; i < MAT_SIZE; i++) {
        if (strcmp(brand_names[i], name) == 0) {
            return i;
        }
    }

    printf("Brand '%s' not found\n", name);
    return -1;  // Not found
}

/**
 * Given a brand name, this function prints its name, index inside the
 * brand_names array, and the names of other similar brands.
 *
 * @param brand_name Pointer to the brand name.
 */
void print_brand_data(char *brand_name) {
    int idx = get_brand_index(brand_name);
    if (idx < 0) {
        printf("Brand '%s' not in the list.\n", brand_name);
        return;
    }

    printf("Brand name: %s\n", brand_name);
    printf("Brand idx: %d\n", idx);

    printf("Similar brands:\n");
    for (int i = 0; i < MAT_SIZE; i++) {
        if (brand_adjacency_matrix[idx][i] == 1 &&
            strcmp(brand_names[i], "") != 0) {
            printf("   %s\n", brand_names[i]);
        }
    }
}

/**
 * Given a file name, this function reads from the file and populates the brand
 * list and brand matrix.
 *
 * @param file_name Pointer to the name of the file to be read.
 */
void populate_brand_matrix(char *file_name) {
    // Read the file
    char buff[MAX_STR_LEN];
    FILE *f = fopen(file_name, "r");
    fscanf(f, "%s", buff);
    char *line = buff;
    // Load up the brand_names matrix
    for (int i = 0; i < MAT_SIZE; i++) {
        if (i == MAT_SIZE - 1) {
            strcpy(brand_names[i], line);
            break;
        }
        int index = strchr(line, ',') - line;
        strncpy(brand_names[i], line, index);
        line = strchr(line, ',') + sizeof(char);
    }
    // Load up the brand_adjacency_matrix
    for (int x = 0; x < MAT_SIZE; x++) {
        fscanf(f, "%s", buff);
        for (int y = 0; y < MAT_SIZE; y++) {
            int value = (int)buff[y * 2];
            if (value == 48) {
                value = 0;
            } else {
                value = 1;
            }
            brand_adjacency_matrix[x][y] = value;
        }
    }
}

/**
 * Given a name, this function creates a new user on the platform. The user is
 * then inserted into the allUsers linked list. If a user already existed with
 * the same name, no action is taken, and NULL is returned instead.
 *
 * @param name Pointer to the name of the user to be created.
 * @return Pointer to the created user, or NULL if a user with
 * the same name already exists.
 */
User *create_user(char *name) {
    // 1. Search through the list for the name

    User* friend = (User*) (malloc(sizeof(User)));
    strcpy(friend->name, name);
    friend->friends = NULL;
    friend->brands = NULL;
    friend->visited = false;
    if (in_friend_list(allUsers, friend)){
        
        return NULL;
        
    } else {
        allUsers = insert_into_friend_list(allUsers, friend);
        
    }
    return friend;
}


/**
 * Given a pair of valid users, this function removes their friendship. The
 * user's friends list must remain in alphabetical order. Returns 0 if the pair
 * are no longer friends. Returns -1 if the pair were not friends to begin with.
 *
 * @param user Pointer to the user initiating the removal of friendship.
 * @param friend Pointer to the user to be removed as a friend.
 * @return 0 if the friendship was successfully removed,
 * -1 if the pair were not friends.
 */
int remove_friend(User *user, User *friend) {
    if (!user || !friend) {
        // Invalid user or friend pointer
        return -1;
    }

    if (!in_friend_list(user->friends, friend)) {
        // The friend is not in the user's friend list
        return -1;
    }

    // Remove friend from user's friend list
    user->friends = delete_from_friend_list(user->friends, friend);

    if (!in_friend_list(friend->friends, user)) {
        // The user is not in the friend's friend list
        return -1;
    }

    // Remove user from friend's friend list
    friend->friends = delete_from_friend_list(friend->friends, user);

    return 0;
}

/**
 * Removes a given user from the platform. The user is removed from the allUsers
 * linked list and the friend lists of any users that they belong to. Returns 0
 * if the user was successfully removed. If the user does not exist, returns -1
 * instead.
 *
 * @param user Pointer to the user to be removed.
 * @return 0 if the user was successfully removed,
 * -1 if the user does not exist.
 */
int delete_user(User *user) {
    
    FriendNode* to_remove = NULL;
    if (in_friend_list(allUsers, user) == false){
        return -1;
    }
    FriendNode* cur = user->friends;
    
    while (cur != NULL){
        to_remove = insert_into_friend_list(to_remove, cur->user);
        cur = cur->next;
    }
    while (to_remove != NULL){
        remove_friend(user, to_remove->user);
        to_remove = to_remove->next;
    }
    
    allUsers = delete_from_friend_list(allUsers, user);
    return 0;
}

/**
 * Given a pair of valid users, this function creates a friendship between them.
 * The user's friends list must remain in alphabetical order. Returns 0 if the
 * friendship was successfully created. Returns -1 if the pair were already
 * friends.
 *
 * @param user Pointer to the user initiating the friendship.
 * @param friend Pointer to the user to be added as a friend.
 * @return 0 if the friendship was successfully created,
 * -1 if the pair were already friends.
 */
int add_friend(User *user, User *friend) {
    //Check to see if they are already friends
    if (in_friend_list(user->friends, friend)){
        return -1;
    }
    user->friends = insert_into_friend_list(user->friends, friend);
    friend->friends = insert_into_friend_list(friend->friends, user);

    return 0;
}



/**
 * Given a valid user and the name of a brand, this function creates a link
 * between the user and the brand. The user's brands list must remain in
 * alphabetical order. Returns 0 if the link was successfully created. Returns
 * -1 if the link already existed or if the brand name is invalid.
 *
 * @param user Pointer to the user.
 * @param brand_name Pointer to the name of the brand to follow.
 * @return 0 if the link was successfully created,
 * -1 if the link already existed or the brand name is invalid.
 */
int follow_brand(User *user, char *brand_name) {
    // TODO: Complete this function.
    
    //if already in the brand list or is an invalid brand
    
    if (get_brand_index(brand_name) == -1){
        printf("INVALID BRAND\n");
        return -1;
    }
    //If already followed
    if (in_brand_list(user->brands, brand_name)){
        return -1;
    }
    user->brands = insert_into_brand_list(user->brands, brand_name);
    return 0;
}

/**
 * Given a valid user and the name of a brand, this function removes the link
 * between the user and the brand. The user's brands list must remain in
 * alphabetical order. Returns 0 if the link was successfully removed. Returns
 * -1 if the link did not previously exist or if the brand name is invalid.
 *
 * @param user Pointer to the user.
 * @param brand_name Pointer to the name of the brand to unfollow.
 * @return 0 if the link was successfully removed, -1 if the link did not
 * previously exist or the brand name is invalid.
 */
int unfollow_brand(User *user, char *brand_name) {
    //if link did not exist:

    if (!in_brand_list(user->brands, brand_name)){
        return -1;
    }

    //if link exists and is valid
    
    user->brands = delete_from_brand_list(user->brands, brand_name);
    return 0;
}

/**
 * Given a pair of valid users, this function returns the number of mutual
 * friends between them. A mutual friend is a user that exists in the friends
 * list of both User a and User b.
 *
 * @param a Pointer to the first user.
 * @param b Pointer to the second user.
 * @return The number of mutual friends between the two users.
 */
int get_mutual_friends(User *a, User *b) {
   //Find number of mutual friends

    FriendNode* friendListA = a->friends; 
    FriendNode* friendListB = b->friends;

    FriendNode* cur = friendListA;

    int total_mutuals = 0;

    while (cur != NULL){
        if (in_friend_list(friendListB, cur->user)){
            total_mutuals++;
        }
        cur = cur->next;
    }
    printf("Total mutuals is: %d\n", total_mutuals);
    return total_mutuals;
}

/**
 * Given a pair of valid users, this function returns the degree of connection
 * between both users. The degree of connection is the shortest number of steps
 * it takes to get from one user to the other. If a connection cannot be formed,
 * returns -1.
 *
 * @param a Pointer to the first user.
 * @param b Pointer to the second user.
 * @return The degree of connection between the two users, or -1 if no
 * connection can be formed.
 */

void reset_path(){
    FriendNode* cur = allUsers;
    while (cur != NULL){
        cur->user->visited = false;
        cur = cur->next;
    }
}

FriendNode* add_to_end(FriendNode* queue, FriendNode* node) {
    if (node == NULL){
        return queue;
    }

    if (queue == NULL) {
        return node; // If queue is empty, return node as the new queue
    }

    if (in_friend_list(queue, node->user)) {
        printf("%s is already in queue\n", node->user);
        return queue; // If already in, don't do anything
    }

    FriendNode* cur = queue;
    
    while (cur->next != NULL) {
        cur = cur->next; // Traverse to the end of the queue
    }
    

    cur->next = node; // Attach the new node to the end of the queue
    return queue; // Return the updated queue
}





int num_of_users(){
    int total = 0;
    FriendNode* cur = allUsers;
    while (cur != NULL){
        total++;
        cur = cur->next;
    }
    return total;
}

FriendNode* deque(FriendNode* queue){
    if (queue == NULL){
        return NULL;
    }
    if (queue->next == NULL){
        return NULL;
    }

    return queue->next;
}

int get_degrees_of_connection(User *a, User *b) {
    if (strcmp(a->name, b->name) == 0){
        return 0;
    }
    FriendNode* cur = allUsers;

    reset_path();

    Queue queue[MAX_STR_LEN];
    int front;
    int back;
    front = 0;
    back = 0;
    

    queue[back].user = a;
    queue[back].length = 0;
    back++;
    
    a->visited = true;

    while (front < back){
        Queue curr = queue[front];
        front++;
        if (curr.user == b){
            return curr.length;
        }
        cur = curr.user->friends;
        while (cur != NULL){
            if (cur->user->visited == false){
                cur->user->visited = true;
                queue[back].user = cur->user;
                queue[back].length = curr.length + 1;
                back++;
            }
            cur = cur->next;
        }
    }
    return -1;
    
}

/**
 * Given two brand names, this function marks the two brands as similar in the
 * brand_adjacency_matrix variable. If either brand name is invalid, no action
 * is taken.
 *
 * @param brandNameA Pointer to the first brand name.
 * @param brandNameB Pointer to the second brand name.
 */



void connect_similar_brands(char *brandNameA, char *brandNameB) {
    //Check to see if the brands are valid
    //To see if brands are valid cehck to see if they are in the brandlist
    bool brandAValid = false;
    bool brandBValid = true;
    int indexOfA = 0;
    int indexOfB = 0;
    for (int i = 0; i < MAT_SIZE; ++i){
        if (strcmp(brand_names[i], brandNameA) == 0){
            brandAValid = true;
            indexOfA = i;          
        }

        if (strcmp(brand_names[i], brandNameB) == 0){
            brandBValid = true;
            indexOfB = i;          
        }
    }

    if (brandAValid == false || brandBValid == false){
        return;
    }

    brand_adjacency_matrix[indexOfA][indexOfB] = 1;
    brand_adjacency_matrix[indexOfB][indexOfA] = 1;

    return;
}

/**
 * Given two brand names, this function marks the two brands as different (not
 * similar) in the brand_adjacency_matrix variable. If either brand name is
 * invalid, no action is taken.
 *
 * @param brandNameA Pointer to the first brand name.
 * @param brandNameB Pointer to the second brand name.
 */
void remove_similar_brands(char *brandNameA, char *brandNameB) {

    
    int indexA = get_brand_index(brandNameA);
    int indexB = get_brand_index(brandNameB);

    if (indexA == -1 || indexB == -1){
        return;
    }

    brand_adjacency_matrix[indexA][indexB] = 0;
    brand_adjacency_matrix[indexB][indexA] = 0;
    return;
}

/**
 * Given a user, suggest a new friend for them.
 *
 * To find the best match, the new suggested friend should have the highest
 * number of mutually liked brands amongst all other valid candidates.
 *
 * If a tie needs to be broken, select the user with the name that comes first
 * in reverse-alphanumerical order.
 *
 * The suggested friend must be a valid user, cannot be the user themself, nor
 * cannot be someone that they're already friends with.
 *
 * If the user is already friends with everyone on the platform, returns NULL.
 *
 * At times, a similarity rating of 0 is the best option.
 *
 * @param user Pointer to the user for whom a friend is being suggested.
 * @return Pointer to the suggested friend, or NULL if no suitable friend is
 * found.
 */

int get_common_brands(User* a, User* b){
    int total = 0;
    while(b->brands != NULL){
        if (in_brand_list(a->brands, b->brands->brand_name)){
            total++;
        }
        b->brands = b->brands->next;
    }
    return total;

}
User *get_suggested_friend(User *user) {
    // If the user is already friends with everyone, return NULL
    bool allFriends = true;
    FriendNode* cur = allUsers;
    while (cur != NULL){
        if (!in_friend_list(user->friends, cur->user)){
            allFriends = false;
            break;
        }
        cur = cur->next;
    }

    if (allFriends){
        return NULL;
    }

    //look for brand which is most similar
    int num = 0;
    int mostSimilarBrands = -1;
    User* suggestedFriend = NULL;
    cur = allUsers;

    while (cur != NULL){
        num = get_common_brands(user, cur->user);
        if (num > mostSimilarBrands && !in_friend_list(user->friends, cur->user) && strcmp(user->name, cur->user->name) != 0){
            mostSimilarBrands = num;
            suggestedFriend = cur->user;
        }

        if (num == mostSimilarBrands && !in_friend_list(user->friends, cur->user) && strcmp(user->name, cur->user->name) != 0){
            if (strcmp(suggestedFriend->name, cur->user->name) < 0){
                suggestedFriend = cur->user;
            }
        }
        cur = cur->next;
    }
    printf("we good\n");
    return suggestedFriend;
}

/**
 * Given a user and a positive integer n, this function adds n suggested friends
 * using the get_suggested_friend() function. There might not be enough users on
 * the platform to satisfy n completely, so it returns the amount of friends
 * successfully added.
 *
 * @param user Pointer to the user for whom suggested friends are being added.
 * @param n The number of suggested friends to add.
 * @return The number of friends successfully added.
 */


int add_suggested_friends(User *user, int n) {
    int addedFriends = 0;

    // Iterate until either n friends are added or there are no more suggestions
    while (addedFriends < n) {
        // Get suggested friend
        User *suggestedFriend = get_suggested_friend(user);
        printf("works\n");
        
        // If no more suggested friends are available, break the loop
        if (suggestedFriend == NULL)
            break;
        
        // Add suggested friend to user's friend list
        user->friends = insert_into_friend_list(user->friends, suggestedFriend);

        // Mark suggested friend as visited to avoid suggesting again
        suggestedFriend->visited = true;

        addedFriends++;
    }

    return addedFriends;
}

/**
 * Given a user and a positive integer n, this function suggests and follows n
 * new brands for them.
 *
 * To find the best matches, suggested brands have the most similarities with
 * the brands that the user already follows.
 *
 * If a tie needs to be broken, the brands with the names that comes first in
 * reverse-alphanumerical order is selected.
 *
 * The suggested brand must be a valid brand and cannot be a brand that the user
 * already follows.
 *
 * There might not be enough brands on the platform to satisfy n completely, so
 * the function returns the amount of brands successfully followed.
 *
 * At times, a similarity rating of 0 is the best option.
 *
 * @param user Pointer to the user for whom brands are being suggested.
 * @param n The number of suggested brands to follow.
 * @return The number of brands successfully followed.
 */

//Check if two brands are similar
//return 1 if two brands are similar, 
//return 0 if two brands are not similar.
int brands_similar(char* brand1, char* brand2){
    int brand1Index = 0;
    int brand2Index = 0;
    //Get the index of the brands in the brand matrix
    
    brand1Index = get_brand_index(brand1);
    brand2Index = get_brand_index(brand2);
    

    if (brand_adjacency_matrix[brand1Index][brand2Index] == 1){
        return 1;
    } else {
        return 0;
    }
}

char* get_suggested_brand(User *user) {
    char* suggestedBrand = NULL; // Declare suggestedBrand as a char pointer
    int mostSimilarities = -1; // Initialize to a negative value

    for (int i = 0; i < MAT_SIZE; ++i) { // Iterate over MAT_SIZE, not num_of_users()
        int curSimilarities = 0;
        BrandNode* cur = user->brands;

        while (cur != NULL) {
            if (brands_similar(cur->brand_name, brand_names[i]) == 0 && strcmp(cur->brand_name, brand_names[i]) != 0) {
                curSimilarities++;
            }
            cur = cur->next;
        }

        // Compare the similarity count directly
        if (curSimilarities > mostSimilarities && !in_brand_list(user->brands, brand_names[i])) {
            mostSimilarities = curSimilarities;
            // Assign the suggested brand name to the pointer
            suggestedBrand = brand_names[i];
        }
    }

    // If no brand with similarities found, suggest the lowest alphanumerical brand
    if (mostSimilarities == -1) { // Check if no brand with similarities found
        for (int i = 0; i < MAT_SIZE; ++i) {
            if (!in_brand_list(user->brands, brand_names[i])) {
                // Assign the suggested brand name to the pointer
                suggestedBrand = brand_names[i];
                break;
            }
        }
    }
    return suggestedBrand;
}


int follow_suggested_brands(User *user, int n) {
    if (user == NULL || n <= 0) {
        return 0;
    }

    int total_followed = 0;
    char* current_brand;
    for (int i = 0; i < n; i++) {
        int most_similar = -1;
        char* best_brand = NULL;

        for (int j = 0; j < MAT_SIZE; j++) {
            current_brand = brand_names[j];
            if (!in_brand_list(user->brands, current_brand)) {
                int curr_similarity = 0;
                BrandNode* curr = user->brands;
                while (curr != NULL){

                    int index = get_brand_index(curr->brand_name);
                    if (index != -1 && brand_adjacency_matrix[index][j]) {
                        curr_similarity++;
                    }
                    curr = curr->next;
                }
                
                if (curr_similarity > most_similar || (curr_similarity == most_similar && best_brand != NULL && strcmp(current_brand, best_brand) > 0)) {
                    most_similar = curr_similarity;
                    best_brand = current_brand;
                }
            }
        }

        if (best_brand != NULL && follow_brand(user, best_brand) == 0) {
            total_followed++;
        } 
        else {
            break; 
        }
    }

    return total_followed;
}