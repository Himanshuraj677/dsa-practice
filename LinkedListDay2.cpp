// 1. Intersection of Two Linked Lists

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *temp1 = headA, *temp2 = headB;
    while (temp1 != temp2) {
        temp1 = (temp1 == NULL) ? headB : temp1 -> next;
        temp2 = (temp2 == NULL) ? headA : temp2 -> next;
    }
    return temp1;
}


// 2. Linked List Cycle

bool hasCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast != NULL && fast -> next != NULL ) {
        slow = slow -> next;
        fast = fast -> next -> next;
        if (slow == fast) return true;
    }
    return false;
}


// 3.Reverse Nodes in k-Group
ListNode *reverse (ListNode *head) {
    ListNode *temp = head, *prev = NULL, *next;
    while (temp != NULL) {
        next = temp -> next;
        temp -> next = prev;
        prev = temp;
        temp = next;
    }
    return prev;
}
ListNode *findKthNode (ListNode *head, int k) {
    int count = 1;
    ListNode *temp = head;
    while (temp != NULL) {
        if (count == k) {
            return temp;
        }
        temp = temp -> next;
        count++;
    }
    return NULL;
}
ListNode* reverseKGroup(ListNode* head, int k) {
    if (k == 1) return head;
    ListNode *temp = head, *next, *prev = NULL;
    ListNode dummy(0);
    dummy.next = head;
    prev = &dummy;
    while (temp != NULL) {
        ListNode *kthNode = findKthNode(temp, k);
        if (kthNode == NULL) {
            prev -> next = temp;
            break;
        }
        else {
           next = kthNode -> next; 
           kthNode -> next = NULL;
           ListNode *newHead = reverse(temp);
           prev -> next = newHead;
           prev = temp;
           temp = next;
        }
    }
    return dummy.next;
}


// 4. Check Palindrome Linked List
// Fistly we need to find the middle of the linked list, then reverse the second half of the linked list and finally compare both halves.
bool isPalindrome(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast -> next) {
        slow = slow -> next;
        fast = fast -> next -> next;
    }

    ListNode *prev = NULL;
    while (slow != NULL) {
        ListNode *next = slow -> next;
        slow -> next = prev;
        prev = slow;
        slow = next;
    }

    slow = head, fast = prev;
    while (fast) {
        if (slow -> val != fast -> val) return false;
        slow = slow -> next;
        fast = fast -> next;
    }
    return true;
}


// 5. Starting Point of Linked List Cycle
// We can use the same approach as in the "Linked List Cycle" problem to find the starting point of the cycle.

ListNode *detectCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (true) {
        if (fast == NULL || fast -> next == NULL) return NULL;
        slow = slow -> next;
        fast = fast -> next -> next;
        if (slow == fast) break;
    }
    slow = head;
    while (slow != fast) {
        slow = slow -> next;
        fast = fast -> next;
    }
    return slow;
}

// Flattening a Linked List
// we will merge two sorted linked lists at a time. We will use a dummy node to keep track of the head of the merged list. We will then iterate through both lists and merge them in sorted order.

Node *mergeLL (Node *temp1, Node *temp2) {
    Node dummy(-1);
    temp1 -> next = NULL;
    temp2 -> next = NULL;
    Node *copy1 = &dummy;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1 -> data < temp2 -> data) {
            copy1 -> bottom = temp1;
            temp1 = temp1 -> bottom;
        }
        else {
            copy1 -> bottom = temp2;
            temp2 = temp2 -> bottom;
        }
        copy1 = copy1 -> bottom;
    }
    if (temp1 != NULL) copy1 -> bottom = temp1;
    if (temp2 != NULL) copy1 -> bottom = temp2;
    return dummy.bottom;
}
Node *flatten(Node *root) {
    // Your code here
    Node *temp = root;
    while (temp -> next != NULL) {
        Node *next = temp -> next -> next;
        Node *temp1 = mergeLL(temp, temp -> next);
        temp1 -> next = next;
        temp = temp1;
    }
    
    return temp;
}