// 1. Reverse a Linked List

ListNode* reverseList(ListNode* head) {
    ListNode *prev = NULL, *curr = head;
    while (curr != NULL) {
        ListNode *next = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}


// 2. Middle of the Linked List
// // We will use the slow and fast pointer approach to find the middle of the linked list. The slow pointer will move one step at a time, while the fast pointer will move two steps at a time. When the fast pointer reaches the end, the slow pointer will be at the middle.


ListNode* middleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast != NULL && fast -> next != NULL) {
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    return slow;
}


// 3. Merge Two Linked Lists


ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode  *temp, *dummy = new ListNode(-1);
    temp = dummy;
    while (list1 != NULL && list2 != NULL) {
        if (list1 -> val < list2 -> val) {
            temp -> next = list1;
            list1 = list1 -> next;
        }
        else {
            temp -> next = list2;
            list2 = list2 -> next;
        }
        temp = temp -> next;
    }
    temp -> next = list1 ? list1 : list2;
    return dummy -> next;
}


// 4. Remove Nth Node From End of List
// We will use the two pointer approach to find the nth node from the end of the list. The first pointer will move n steps ahead, and then both pointers will move one step at a time until the first pointer reaches the end. The second pointer will be at the nth node from the end.
// We will then remove the node by updating the next pointer of the previous node.

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode *temp1, *temp2;
    temp1 = temp2 = head;
    while (n-- && temp2 != NULL) {
        temp2 = temp2 -> next;
    }
    if (temp2 == NULL) {
        ListNode *toDelete = head;
        head = head -> next;
        delete toDelete;
        return head;
    }
    ListNode *prev;
    while (temp2 -> next != NULL) {
        temp1 = temp1 -> next;
        temp2 = temp2 -> next;
    }
    ListNode *toDelete = temp1 -> next;
    temp1 -> next = temp1 -> next -> next;
    delete toDelete;
    return head;
}



// 5. Add Two Numbers

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int c = 0;
    ListNode *temp2 = l2, *temp1 = l1, *prev;
    while (temp1 != NULL || temp2 != NULL) {
        int sum = c;
        if (temp1) {
            sum += temp1 -> val;
            temp1 = temp1 -> next;
        }
        if (temp2) {
            sum += temp2 -> val;
            temp2 -> val = sum % 10;
            c = sum / 10;
            prev = temp2;
            temp2 = temp2 -> next;
        }
        else {
            ListNode *newNode = new ListNode(sum % 10);
            c = sum / 10;
            prev -> next = newNode;
            prev = prev -> next;
        }
    }
    if (c > 0) {
        ListNode *newNode = new ListNode(c);
        prev -> next = newNode;
    }
    return l2;
}


// 6. Delete Node in a Linked List

void deleteNode(ListNode* node) {
    node -> val = node -> next -> val;
    ListNode *toDeleted = node -> next;
    node -> next = node -> next -> next;
    delete toDeleted;
}