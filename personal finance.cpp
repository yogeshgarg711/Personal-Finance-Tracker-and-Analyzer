#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    TrieNode* links[26]; 
    bool flag; 

    TrieNode() {
        flag = false;
        for (int i = 0; i < 26; i++) {
            links[i] = nullptr;
        }
    }

    bool containsKey(char ch) {
        return (links[ch - 'a'] != nullptr);
    }

    void put(char ch, TrieNode* node) {
        links[ch - 'a'] = node;
    }

    TrieNode* get(char ch) {
        return links[ch - 'a'];
    }

    void setEnd() { 
        flag = true;
    }

    bool isEnd() {
        return flag;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the trie
    void insert(string word) {
        TrieNode* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new TrieNode());
            }
            node = node->get(word[i]);
        }
        node->setEnd();
    }

    // Search for a word in the trie
    bool search(string word) {
        TrieNode* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                return false;
            }
            node = node->get(word[i]);
        }
        return node->isEnd();
    }

    // Find all words that start with a given prefix
    bool startsWith(string prefix, vector<string>& foundWords) {
        TrieNode* node = root;

        // Traverse the trie with the given prefix
        for (int i = 0; i < prefix.length(); i++) {
            if (!node->containsKey(prefix[i])) {
                return false; // Prefix doesn't exist
            }
            node = node->get(prefix[i]);
        }

        // Start DFS to find all words with the given prefix
        dfs(node, prefix, foundWords);
        return true;
    }

    // Remove a word from the trie
    bool remove(string word) {
        TrieNode* node = root;
        stack<TrieNode*> path;
        
        // Traverse the trie to find the word
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                return false; // Word doesn't exist
            }
            path.push(node);
            node = node->get(word[i]);
        }

        // If the word doesn't end at this node, return false
        if (!node->isEnd()) {
            return false;
        }
        node->flag = false;  // Mark the end of the word as false

        // Remove nodes if they are no longer needed
        for (int i = word.length() - 1; i >= 0; i--) {
            node = path.top();
            path.pop();
            char ch = word[i];

            if (!node->get(ch)->isEnd() && isEmpty(node->get(ch))) {
                node->put(ch, nullptr);  // Remove the link
            } else {
                break;
            }
        }
        return true;
    }

    // Clear all words from the trie
    void clear() {
        deleteNodes(root);  // Recursively delete all nodes starting from root
        root = new TrieNode();  // Reinitialize the root node
    }

private:
    // Depth-First Search (DFS) to find all words starting with the given prefix
    void dfs(TrieNode* node, string word, vector<string>& foundWords) {
        if (node->isEnd()) {
            foundWords.push_back(word);  // Add word if it's a complete word
        }

        // Recursively search all child nodes
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (node->containsKey(ch)) {
                dfs(node->get(ch), word + ch, foundWords);  // Continue DFS
            }
        }
    }

    // Helper function to check if a node is empty (has no children)
    bool isEmpty(TrieNode* node) {
        for (int i = 0; i < 26; i++) {
            if (node->links[i] != nullptr) {
                return false;  // The node has a child
            }
        }
        return true;  // The node has no children
    }

    // Recursively delete all nodes starting from the given node
    void deleteNodes(TrieNode* node) {
        for (int i = 0; i < 26; i++) {
            if (node->links[i] != nullptr) {
                deleteNodes(node->links[i]);  // Recursively delete child nodes
                node->links[i] = nullptr;  // Set the link to nullptr after deletion
            }
        }
        delete node;  // Delete the current node
    }
};

class Budget{
    public:
    
    unordered_map<string,pair<double,string>> data;
    double total=0;
    void add(vector<string>categories,vector<double> amounts, vector<string> descriptions)
    {
        for(int i=0;i<categories.size();i++){
            data.insert({categories[i],{amounts[i],descriptions[i]}});
            total+=amounts[i];
        }
    }

    void display(){
        cout << "==========================================" << endl;
        cout << "           Personal Budget Overview       " << endl;
        cout << "==========================================" << endl;
        cout << "Total Budget: Rs" << total << endl; 
        cout << "------------------------------------------" << endl;
        cout << "Categories Breakdown:" << endl;
        cout << "------------------------------------------" << endl<<endl;
        for(auto it:data){
            cout<<"Category : "<<it.first<<endl;
            cout<<"Amount : "<<it.second.first<<endl;
            cout<<"Description : "<<it.second.second<<endl<<endl;
        }
        cout << "------------------------------------------" << endl;
    }

    void update(){
        cout<<"CURRENT BUDGET IS SHOWN BELOW"<<endl<<endl;
        display();
        while(true){
        cout<<"1. Update existing category"<<endl;
        cout<<"2. Add new category "<<endl;
        cout<<"3. Delete existing category"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter your choice : ";
        int choice;
        cin>>choice;

        if(choice==1){
            string n,des,name;
            double amt;
            cout<<"Category name you want to update : ";
            cin>>name;
            cout<<"Updated Name : ";
            cin>>n;
            cout<<"Updated Amount : ";
            cin>>amt;
            cout<<"Updated description : ";
            cin.ignore();
            getline(cin,des);
            if (data.find(name) == data.end()) {
                    cout << "Category not found!" << endl;
                    continue;
            }
            data.erase(name);
            data.insert({n,{amt,des}});
        }
        else if(choice==2){
            string n,des;
            double amt;
            cout<<"Category Name : ";
            cin>>n;
            cout<<"Amount : ";
            cin>>amt;
            cout<<"Description : ";
            cin.ignore();
            getline(cin,des);
            data.insert({n,{amt,des}});
        }
        else if(choice==3){
            string name;
            cout<<"Category name you want to update : ";
            cin>>name;
            if (data.find(name) == data.end()) {
                cout << "Category not found!" << endl;
                continue;
            }
            data.erase(name);
            cout<<"Deleted Successfully!!!"<<endl;
        }
        else if(choice==4){
            break;
        }
        else {
            cout<<"Invalid choice!!!"<<endl;
        }
        
        }


    }
};

class Node // Expenses are stored in LL 
{
public:
    string date;
    string category;
    string subcategory;
    string details;
    double amount;
    Node *next;

    Node(string dt, string ctgry, string sub, string dtls, double amt)
    {
        date = dt;
        category = ctgry;
        subcategory=sub;
        details = dtls;
        amount = amt;
        next = nullptr;
    }
};

class TreeNodeExpenseAmount //expenses are stored in form of bst too where each node contains a pointer to expense node and sorting done on basis of expense amount
{
    public:
    TreeNodeExpenseAmount *left;
    TreeNodeExpenseAmount *right;
    Node *expenseNode;

    TreeNodeExpenseAmount(Node *n){
        left=nullptr;
        right=nullptr;
        expenseNode=n;
    }
    
};

class TreeNodeExpenseDate//expenses are stored in form of bst too where each node contains a pointer to expense node and sorting done on basis of expense date
{
    public:
    TreeNodeExpenseDate *left;
    TreeNodeExpenseDate *right;
    Node *expenseNode;
    
    TreeNodeExpenseDate(Node* n){
        left=nullptr;
        right=nullptr;
        expenseNode=n;
    }

};

// these two functions will add expenses in the bst 
void addExpenseAmountUsingBST(TreeNodeExpenseAmount *&head,Node *newNode){
    if(head==nullptr){
        head=new TreeNodeExpenseAmount(newNode);
        return;
    }
    else if(head->expenseNode->amount>=newNode->amount){
        if(head->right==nullptr){
            head->right=new TreeNodeExpenseAmount(newNode);
            return;
        }
        else{
            addExpenseAmountUsingBST(head->right,newNode);
        }
    }
    else if(head->expenseNode->amount<newNode->amount){
        if(head->left==nullptr){
        head->left=new TreeNodeExpenseAmount(newNode);
        return;       
        }
        else{
            addExpenseAmountUsingBST(head->left,newNode);
        }
    }
    
}
void addExpenseDateUsingBST(TreeNodeExpenseDate *&head, Node* newNode){
    if(head==nullptr){
        head=new TreeNodeExpenseDate(newNode);
        return;
    }
     else if(head->expenseNode->date>=newNode->date){
        if(head->right==nullptr){
            head->right=new TreeNodeExpenseDate(newNode);
            return;
        }
        else{
            addExpenseDateUsingBST(head->right,newNode);
        }
    }
    else if(head->expenseNode->date<newNode->date){
        if(head->left==nullptr){
        head->left=new TreeNodeExpenseDate(newNode);
        }
        else{
            addExpenseDateUsingBST(head->left,newNode);
        }
    }
}
void deleteEntireExpenseAmountTree(TreeNodeExpenseAmount *&node){
        if(node==nullptr){
            return;
        }
        deleteEntireExpenseAmountTree(node->left);
        deleteEntireExpenseAmountTree(node->right);
        delete node;
        node=nullptr;
    }
void deleteEntireExpenseDateTree(TreeNodeExpenseDate *&node){
        if(node==nullptr){
            return;
        }
        deleteEntireExpenseDateTree(node->left);
        deleteEntireExpenseDateTree(node->right);
        delete node;
        node=nullptr;
    }

class LinkedListExpense
{
public:
    Node *head = nullptr;
    double total=0;
    TreeNodeExpenseAmount *head_amount=nullptr;
    TreeNodeExpenseDate *head_date=nullptr;
    
    void add(string date, string category, string sub, double amount, string details)
    {
        if (head == nullptr)
        {   
            Node *newNode = new Node(date, category, sub, details, amount);
            head=newNode;
            total+=amount;
            
            addExpenseAmountUsingBST(head_amount,newNode);
            addExpenseDateUsingBST(head_date,newNode);
        }
        else
        {
            Node *move = head;
            Node *newNode = new Node(date, category, sub, details, amount);
            while (move->next != nullptr)
            {
                move = move->next;
            }
            move->next = newNode;
            addExpenseAmountUsingBST(head_amount,newNode);
            addExpenseDateUsingBST(head_date,newNode);
            total+=amount;
        }
    }

    void removeLast(Trie &catTrie,Trie& subTrie)
    {
        if (head == nullptr)
        {
            cout << "No Expense Transaction to undo!!!" << endl;
        }
        else if (head->next == nullptr)
        {
            total -= head->amount;
            catTrie.remove(head->category);
            subTrie.remove(head->subcategory);

            deleteNodeInAmountTree(head);
            deleteNodeInDateTree(head);
            delete head;
            head = nullptr; 
            cout << "Successfully removed the last transaction!" << endl;
        }
        else
        {
            Node *move = head;
            while (move->next->next != nullptr)
            {
                move = move->next;
            }
            total=total-move->next->amount;
            catTrie.remove(move->next->category);
            subTrie.remove(move->next->subcategory);
            deleteNodeInAmountTree(move->next);
            deleteNodeInDateTree(move->next);

            move->next = nullptr;
            cout << "Successfully removed the last transaction!!!" << endl;
        }
    }

    void displayAllTime()
    {
        Node *move = head;
        cout << endl;
        while (move)
        {
            cout << "Date : " << move->date << endl;
            cout << "Category : " << move->category << endl;
            cout<<"Subcategory : "<<move->subcategory<<endl;
            cout << "Amount : " << move->amount << endl;
            cout << "Details : " << move->details << endl<<endl;
            move = move->next;
        }
        cout << endl;
    }

    void display(string s_date, string e_date)
    {
        Node *move = head;
        queue<Node *> q;

        while (move)
        {
            if (move->date >= s_date && move->date <= e_date)
            {
                q.push(move);
            }
            move=move->next;
        }
        cout << endl;
        while (!q.empty())
        {
            cout << "Date : " << q.front()->date << endl;
            cout << "Category : " << q.front()->category << endl;
            cout<<"Subcategory : "<<q.front()->subcategory<<endl;
            cout << "Amount : " << q.front()->amount << endl;
            cout << "Details : " << q.front()->details << endl;
            q.pop();
            cout << endl;
        }
    }

    void clearAllExpense(){
        total=0;
            Node *move1=head;
            while(move1){
                Node *temp=move1;
                move1=move1->next;
                delete temp;
            }
            head=nullptr;
            TreeNodeExpenseAmount *move2=head_amount;
            deleteEntireExpenseAmountTree(head_amount);
            head_amount=nullptr;
            TreeNodeExpenseDate *move3=head_date;
            deleteEntireExpenseDateTree(head_date);
            head_date=nullptr;
    }

    void deleteNodeInAmountTree(Node* nodeToDelete) 
{
    TreeNodeExpenseAmount* current = head_amount;
    TreeNodeExpenseAmount* parent = nullptr;

    while (current != nullptr && current->expenseNode != nodeToDelete) {
        parent = current;
        if (nodeToDelete->amount < current->expenseNode->amount)
            current = current->left;
        else
            current = current->right;
    }

    if (current == nullptr) {
        return;
    }

    if (current->left == nullptr && current->right == nullptr) {
        if (parent == nullptr) {
            head_amount = nullptr;
        } else if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
    } 
    else if (current->left == nullptr || current->right == nullptr) {
        TreeNodeExpenseAmount* child = (current->left != nullptr) ? current->left : current->right;
        if (parent == nullptr) {
            head_amount = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;
    } 
    else {
        TreeNodeExpenseAmount* successor = current->right;
        TreeNodeExpenseAmount* successorParent = current;
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        current->expenseNode = successor->expenseNode;

        if (successorParent->left == successor)
            successorParent->left = successor->right;
        else
            successorParent->right = successor->right;

        delete successor;
    }
}

    void deleteNodeInDateTree(Node* nodeToDelete) {
    TreeNodeExpenseDate* current = head_date;
    TreeNodeExpenseDate* parent = nullptr;

    while (current != nullptr && current->expenseNode != nodeToDelete) {
        parent = current;
        if (nodeToDelete->date < current->expenseNode->date)
            current = current->left;
        else
            current = current->right;
    }

    if (current == nullptr) {
        
        return;
    }

    if (current->left == nullptr && current->right == nullptr) {
        if (parent == nullptr) {
            head_date = nullptr;
        } else if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
    } 
    else if (current->left == nullptr || current->right == nullptr) {
        TreeNodeExpenseDate* child = (current->left != nullptr) ? current->left : current->right;
        if (parent == nullptr) {
            head_date = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;
    } 
    else {
        TreeNodeExpenseDate* successor = current->right;
        TreeNodeExpenseDate* successorParent = current;
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        current->expenseNode = successor->expenseNode;

        if (successorParent->left == successor)
            successorParent->left = successor->right;
        else
            successorParent->right = successor->right;

        delete successor;
    }
}

    void deleteDateCriteria(string startDate, string endDate, Trie &catTrie, Trie &subcatTrie) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->date >= startDate && current->date <= endDate) {
            if (prev == nullptr) { 
                head = current->next;
            } else {
                prev->next = current->next;
            }

            deleteNodeInAmountTree(current);
            deleteNodeInDateTree(current);
            catTrie.remove(current->category);
            subcatTrie.remove(current->subcategory);
            delete current;
            current = (prev == nullptr) ? head : prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

    void deleteAmountCriteria(double startAmount, double endAmount, Trie &catTrie, Trie &subcatTrie) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->amount >= startAmount && current->amount <= endAmount) {
            if (prev == nullptr) { 
                head = current->next;
            } else {
                prev->next = current->next;
            }

            deleteNodeInAmountTree(current);
            deleteNodeInDateTree(current);
            catTrie.remove(current->category);
            subcatTrie.remove(current->subcategory);
            delete current;
            current = (prev == nullptr) ? head : prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

    void deleteCategoryCriteria(vector<string> categories) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (find(categories.begin(), categories.end(), current->category) != categories.end()) {
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }

            deleteNodeInAmountTree(current);
            deleteNodeInDateTree(current);

            delete current;
            current = (prev == nullptr) ? head : prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

    void deleteSubcategoryCriteria(vector<string> subcategories) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (find(subcategories.begin(), subcategories.end(), current->subcategory) != subcategories.end()) {
            if (prev == nullptr) { 
                head = current->next;
            } else {
                prev->next = current->next;
            }

            deleteNodeInAmountTree(current);
            deleteNodeInDateTree(current);

            delete current;
            current = (prev == nullptr) ? head : prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

    void deleteMultipleCriteria(vector<string> categories, vector<string> subcategories, 
                             string startDate, string endDate, double startAmount, 
                             double endAmount, Trie &catTrie, Trie &subcatTrie) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        bool deleteNode = false;

        // Check if node meets all delete criteria
        if (find(categories.begin(), categories.end(), current->category) != categories.end() &&
            find(subcategories.begin(), subcategories.end(), current->subcategory) != subcategories.end() &&
            current->date >= startDate && current->date <= endDate) {
            // Adjust for startAmount and endAmount
            bool startAmountValid = (startAmount == -1 || current->amount >= startAmount);
            bool endAmountValid = (endAmount == -1 || current->amount <= endAmount);

            if (startAmountValid && endAmountValid) {
                deleteNode = true;
            }
        }

        // If the node meets the criteria, delete it
        if (deleteNode) {
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }

            // Call helper functions to delete from trees and trie's
            deleteNodeInAmountTree(current);
            deleteNodeInDateTree(current);
            catTrie.remove(current->category);
            subcatTrie.remove(current->subcategory);

            // Deallocate memory for the node
            delete current;
            current = (prev == nullptr) ? head : prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}
};

// Following comparators are used while searching transactions (see search viewExpenseTransaction function in PersonalFinanceTracker class)
struct compSortExpenseByAmountAsc
{
    bool operator()(Node *o1, Node *o2)
    {
        return o1->amount <= o2->amount;
    }
};
struct compSortExpenseByAmountDesc
{
    bool operator()(Node *o1, Node *o2)
    {
        return o1->amount >= o2->amount;
    }
};
struct compSortExpenseByDateAsc
{
    bool operator()(Node *o1, Node *o2)
    {
        return o1->date <= o2->date;
    }
};
struct compSortExpenseByDateDesc
{
    bool operator()(Node *o1, Node *o2)
    {
        return o1->date >= o2->date;
    }
};
struct compSortExpenseByDateDescAmountDesc
{
    bool operator()(Node *o1, Node *o2)
    {
        if (o1->date == o2->date) {
            return o1->amount >= o2->amount; 
        }
        return o1->date >= o2->date;   
    }
};
struct compSortExpenseByDateAscAmountAsc
{
    bool operator()(Node *o1, Node *o2)
    {
        if (o1->date == o2->date) {
            return o1->amount <= o2->amount; 
        }
        return o1->date <= o2->date;
    }
};
struct compSortExpenseByDateAscAmountDesc
{
    bool operator()(Node *o1, Node *o2)
    {
        if (o1->date == o2->date) {
            return o1->amount > o2->amount;
        }
        return o1->date < o2->date;
    }
};
struct compSortExpenseByDateDescAmountAsc
{
    bool operator()(Node *o1, Node *o2)
    {
        if (o1->date == o2->date) {
            return o1->amount <= o2->amount;
        }
        return o1->date >= o2->date;
    }
};

class PersonalFinanceTracker
{
private:
    LinkedListExpense expense; 
    Budget budget;
    Trie catTrie;
    Trie subcatTrie;

public:
    void addExpense(string date, string category,string sub, double amount, string details)
    {
        expense.add(date, category, sub,amount, details);
        catTrie.insert(category);
        subcatTrie.insert(sub);
    }

    void undoTransaction()
    {
        expense.removeLast(catTrie,subcatTrie);

    }

    void viewExpenseTransaction()
    {
        string s_date;
        string e_date;
        cout << "Starting Date (YYYY-MM-DD) (all for alltime): ";
        cin >> s_date;
        if (s_date == "all")
        {
            expense.displayAllTime();
        }
        else
        {
            cout << "End Date (YYYY-MM-DD) : ";
            cin >> e_date;
            expense.display(s_date, e_date);
        }
    }

    void setBudget(vector<string> cat,vector<double> amt,vector<string> des){
        budget.add(cat,amt,des);
    }

    void seeBudget(){
        budget.display();
    }

    void updateBudget(){
        budget.update();
    }
    
    void searchTransactions()
    {
         int choice;

        cout<<"1. Display Expense Transactions (All Time / Given Date Range)"<<endl; 
        cout<<"2. Search Expenses by specific Date"<<endl; 
        cout<<"3. Search Expenses by specific Amount"<<endl; 
        cout<<"4. Search Expenses by Category "<<endl;
        cout<<"5. Search Expenses by subcategory "<<endl;
        cout<<"6. Search if a category / subcategory starts with a prefix "<<endl;
        cout<<"7. Multiple / Mixed / More Filters"<<endl; 
        cout<<"Select your choice : ";

        cin>>choice;
        if(choice==1)
        {
            viewExpenseTransaction();
        }
        else if(choice==2)
        {
            TreeNodeExpenseDate *move=expense.head_date;
            string d;

            cout<<"Date : ";
            cin>>d;
            stack<TreeNodeExpenseDate *>st;
            
            while(true)
            {
                if(move==nullptr) break;
                else if(move->expenseNode->date>d){
                    
                    move=move->left;
                }
                else if(move->expenseNode->date<d){
                   
                    move=move->right;
                }   
                else{
                    st.push(move);
                    move=move->right;
                }
            }
            cout<<endl;
            while(!st.empty()){
                cout<<"Category : "<<st.top()->expenseNode->category<<endl;
                cout<<"Subcategory : "<<st.top()->expenseNode->subcategory<<endl;
                cout<<"Amount : "<<st.top()->expenseNode->amount<<endl;
                cout<<"Details : "<<st.top()->expenseNode->details<<endl<<endl;
                cout<<endl;
                st.pop();
            }
        }
        else if(choice==3){
            TreeNodeExpenseAmount *move=expense.head_amount;
            double amt;

            cout<<"Amount : ";
            cin>>amt;
            stack<TreeNodeExpenseAmount *>st;
            
            while(true)
            {
                if(move==nullptr) break;
                else if(move->expenseNode->amount>amt){
                    
                    move=move->left;
                }
                else if(move->expenseNode->amount<amt){
                    
                    move=move->right;
                }   
                else{
                    st.push(move);
                    move=move->right;
                }
            }
            cout<<endl;
            while(!st.empty()){
                cout<<"Date : "<<st.top()->expenseNode->date<<endl;
                cout<<"Category : "<<st.top()->expenseNode->category<<endl;
                cout<<"Subcategory : "<<st.top()->expenseNode->subcategory<<endl;
                cout<<"Details : "<<st.top()->expenseNode->details<<endl<<endl;
                cout<<endl;
                st.pop();
            }
        }
        else if(choice==4){
            cout<<"Enter Categories : "<<endl;
            vector<string> ctg;
            while(true){
                string s;
                cout<<"Category (type no if done): ";
                cin>>s;
                if(s=="no") break;
                ctg.push_back(s);
            }
            Node *move=expense.head;
            queue<Node*>q;
            while(move){
                for(auto it:ctg){
                    if(move->category==it){
                        q.push(move);
                    }
                }
                move=move->next;
            }
            cout<<"======================================================"<<endl;
            cout<<"Following are records falling under entered categories"<<endl;
            cout<<"======================================================"<<endl;
            while(!q.empty()){
                cout<< "Category : "<<q.front()->category<<endl;
                cout<<"Subcategory : "<<q.front()->subcategory<<endl;
                cout<<"Date : "<<q.front()->date<<endl;
                cout<<"Amount : "<<q.front()->amount<<endl;
                cout<<"Details : "<<q.front()->details<<endl;
            cout<<"------------------------------------------------------"<<endl;
                q.pop();
            }
        }
        else if(choice==5){
            cout<<"Enter Subcategories : "<<endl;
            vector<string> subctg;
            while(true){
                string s;
                cout<<"Subcategory (type no if done): ";
                cin>>s;
                if(s=="no") break;
                subctg.push_back(s);
            }
            Node *move=expense.head;
            queue<Node*>q;
            while(move){
                for(auto it:subctg){
                    if(move->subcategory==it){
                        q.push(move);
                    }
                }
                move=move->next;
            }
            cout<<"========================================================="<<endl;
            cout<<"Following are records falling under entered subcategories"<<endl;
            cout<<"========================================================="<<endl;
            while(!q.empty()){
                cout<< "Category : "<<q.front()->category<<endl;
                cout<<"Subcategory : "<<q.front()->subcategory<<endl;
                cout<<"Date : "<<q.front()->date<<endl;
                cout<<"Amount : "<<q.front()->amount<<endl;
                cout<<"Details : "<<q.front()->details<<endl;
            cout<<"------------------------------------------------------==="<<endl;
                q.pop();
            }
        }
        else if(choice==6){
            cout<<"1. Category prefix search"<<endl<<"2. Subcategory prefix search"<<endl<<"Enter your choice : ";
            int choice ;
            cin>>choice;
            cout<<"Enter the prefix (Category): ";
            string s;
            cin>>s;
            vector<string> result;
            if(choice==1){
                cout<<endl<<"Following Categories start with given prefix"<<endl;
                catTrie.startsWith(s,result);
                for(auto it:result){
                    cout<<it<<endl;
                }
                cout<<endl;
            }
            else if(choice==2){
                cout<<endl<<"Following Subcategories start with given prefix"<<endl;
                subcatTrie.startsWith(s,result);
                for(auto it:result){
                    cout<<it<<endl;
                }
                cout<<endl;
            }
            else{
                cout<<"Invalid choice "<<endl;
            }
            
        }
        else{
        string search_s_date;
        string search_e_date;
        vector<string> search_category;
        vector<string> search_subcategory;
        double search_s_amount;
        double search_e_amount;
        string sortDate;
        string sortAmt;

        cout << "===================================================" << endl;
        cout << "You can Filter on Basis of Date / Category / Amount" << endl;
        cout << "      Enter n For Filters You Dont Want           " << endl;
        cout << "     You Can Also Choose Sorting If You Want      " << endl;
        cout << "===================================================" << endl;

        cout << "Starting Date (YYYY-MM-DD) (or n): ";
        cin >> search_s_date;
        cout << "Ending Date (YYYY-MM-DD) (or n): ";
        cin >> search_e_date;
        cout << "Sort on basis of Date (yDes/yAsc/n) : ";
        cin >> sortDate;
        cout << "You can give multiple categories (enter no to stop giving categories)" << endl;
        while (true)
        {
            cout << "Category (no to stop) : ";
            string choice;
            cin >> choice;
            if (choice != "no")
            {
                search_category.push_back(choice);
            }
            else
            {
                break;
            }
        }

        cout << "You can give multiple sub categories (enter no to stop giving categories)" << endl;
        while (true)
        {
            cout << "Sub category (no to stop) : ";
            string choice;
            cin >> choice;
            if (choice != "no")
            {
                search_subcategory.push_back(choice);
            }
            else
            {
                break;
            }
        }

        cout << "Min Amount (or -1): ";
        cin >> search_s_amount;
        cout << "Max Amount (or -1) : ";
        cin >> search_e_amount;
        cout << "Sort on basis of Amount (yDes/yAsc/n) : ";
        cin >> sortAmt;
        priority_queue<Node *, vector<Node *>, compSortExpenseByDateDescAmountAsc> pq1;
        priority_queue<Node *, vector<Node *>, compSortExpenseByDateDescAmountDesc> pq2;
        priority_queue<Node *, vector<Node *>, compSortExpenseByDateDesc> pq3;
        priority_queue<Node *, vector<Node *>, compSortExpenseByDateAscAmountAsc> pq4;
        priority_queue<Node *, vector<Node *>, compSortExpenseByDateAscAmountDesc> pq5;
        priority_queue<Node *, vector<Node *>, compSortExpenseByDateAsc> pq6;
        priority_queue<Node *, vector<Node *>, compSortExpenseByAmountAsc> pq7;
        priority_queue<Node *, vector<Node *>, compSortExpenseByAmountDesc> pq8;
        queue<Node *> q;

        Node *move = expense.head;
    while (move) {
    // Check if the date and amount filters match
    if ((search_s_date == "n" || move->date >= search_s_date) && 
        (search_e_date == "n" || move->date <= search_e_date) && 
        (search_s_amount == -1 || move->amount >= search_s_amount) && 
        (search_e_amount == -1 || move->amount <= search_e_amount)) {
        
        bool x = false, y = false;
        
        // Check if the category filter matches
        if (search_category.empty() || 
            find(search_category.begin(), search_category.end(), move->category) != search_category.end()) {
            x = true;
        }

        // Check if the subcategory filter matches
        if (search_subcategory.empty() || 
            find(search_subcategory.begin(), search_subcategory.end(), move->subcategory) != search_subcategory.end()) {
            y = true;
        }

        // If both category and subcategory match
        if (x && y) {
            // Sorting logic (checking if the filters match for the amount and date)
            if (sortDate == "yDesc" && sortAmt == "yAsc") {
                pq1.push(move);
            } else if (sortDate == "yDesc" && sortAmt == "yDesc") {
                pq2.push(move);
            } else if (sortDate == "yAsc" && sortAmt == "yAsc") {
                pq4.push(move);
            } else if (sortDate == "yAsc" && sortAmt == "yDesc") {
                pq5.push(move);
            } else if (sortAmt == "yAsc") {
                pq7.push(move);
            } else if (sortAmt == "yDesc") {
                pq8.push(move);
            } else if (sortDate == "yAsc") {
                pq6.push(move);
            } else if (sortDate == "yDesc") {
                pq3.push(move);
            } else {
                q.push(move);
            }
        }
    }
    move = move->next;
}
        cout<<endl;
        while (!pq1.empty()) {
        cout << "Date: " << pq1.top()->date << endl<< "Category: " << pq1.top()->category << endl<<"Subcategory : "<<pq1.top()->subcategory<<endl<< "Amount: " << pq1.top()->amount << endl<< "Details: " << pq1.top()->details << endl << endl;
        pq1.pop(); 
        }
        while (!pq2.empty()) {
        cout << "Date: " << pq2.top()->date << endl<< "Category: " << pq2.top()->category << endl<<"Subcategory : "<<pq2.top()->subcategory<<endl<< "Amount: " << pq2.top()->amount << endl<< "Details: " << pq2.top()->details << endl << endl;
        pq2.pop(); 
        }
        while (!pq3.empty()) {
        cout << "Date: " << pq3.top()->date << endl<< "Category: " << pq3.top()->category << endl<<"Subcategory : "<<pq3.top()->subcategory<<endl<< "Amount: " << pq3.top()->amount << endl<< "Details: " << pq3.top()->details << endl << endl;
        pq3.pop(); 
        }
        while (!pq4.empty()) {
        cout << "Date: " << pq4.top()->date << endl<< "Category: " << pq4.top()->category << endl<<"Subcategory : "<<pq4.top()->subcategory<< endl<<"Amount: " << pq4.top()->amount << endl<< "Details: " << pq4.top()->details << endl << endl;
        pq4.pop(); 
        }
        while (!pq5.empty()) {
        cout << "Date: " << pq5.top()->date << endl<< "Category: " << pq5.top()->category << endl<<"Subcategory : "<<pq5.top()->subcategory<<endl<< "Amount: " << pq5.top()->amount << endl<< "Details: " << pq5.top()->details << endl << endl;
        pq5.pop(); 
        }
        while (!pq6.empty()) {
        cout << "Date: " << pq6.top()->date << endl<< "Category: " << pq6.top()->category << endl<<"Subcategory : "<<pq6.top()->subcategory<<endl<< "Amount: " << pq6.top()->amount << endl<< "Details: " << pq6.top()->details << endl << endl;
        pq6.pop(); 
        }
        while (!pq7.empty()) {
        cout << "Date: " << pq7.top()->date << endl<< "Category: " << pq7.top()->category << endl<<"Subcategory : "<<pq7.top()->subcategory<<endl<< "Amount: " << pq7.top()->amount << endl<< "Details: " << pq7.top()->details << endl << endl;
        pq7.pop(); 
        }
        while (!pq8.empty()) {
        cout << "Date: " << pq8.top()->date << endl<< "Category: " << pq8.top()->category << endl<<"Subcategory : "<<pq8.top()->subcategory<<endl<< "Amount: " << pq8.top()->amount << endl<< "Details: " << pq8.top()->details << endl << endl;
        pq8.pop(); 
        }
        while (!q.empty()) {
        cout << "Date: " << q.front()->date << endl<< "Category: " << q.front()->category <<endl<<"Subcategory : "<<q.front()->subcategory<< endl<< "Amount: " << q.front()->amount << endl<< "Details: " << q.front()->details << endl << endl;
        q.pop(); 
        }

        
        }
       
    }

    void deleteTransactions()
{
    cout << "=============================================" << endl;
    cout << "          Expense Deletion Options           " << endl;
    cout << "=============================================" << endl;

    cout << "1. Clear All Expenses" << endl;
    cout << "   - Remove all recorded expenses from the system." << endl;
    cout << "---------------------------------------------" << endl;

    cout << "2. Delete Based on Category" << endl;
    cout << "   - Remove all expenses associated with a specific category." << endl;
    cout << "---------------------------------------------" << endl;

    cout << "3. Delete Based on Date" << endl;
    cout << "   - Remove expenses from a specific date or date range." << endl;
    cout << "---------------------------------------------" << endl;

    cout << "4. Delete Based on Subcategory" << endl;
    cout << "   - Remove expenses associated with a specific subcategory." << endl;
    cout << "---------------------------------------------" << endl;

    cout << "5. Delete Based on Amount" << endl;
    cout << "   - Remove expenses equal to, above, or below a specified amount." << endl;
    cout << "---------------------------------------------" << endl;

    cout << "6. Delete Based on Multiple Criteria" << endl;
    cout << "   - Combine filters like category, date, and amount for precise deletion." << endl;
    cout << "=============================================" << endl;
    cout<<"Enter choice : ";
    int choice;
    cin>>choice;
    switch(choice){
        case 1 :{
            expense.clearAllExpense();
            cout<<"Successfully Deleted !!!"<<endl;
            catTrie.clear();
            subcatTrie.clear();
            break;
        }
        case 2 :{
            cout<<"Select Categories : "<<endl;
            vector<string> categories;
            while(true){
                string s;
                cout<<"Category (type no if done) : ";
                cin>>s;
                if(s=="no") break;
                catTrie.remove(s);
                categories.push_back(s);
            }
            expense.deleteCategoryCriteria(categories);
            cout<<"Successfully Deleted!!!"<<endl;
            break;
        }
        case 3 :{
            string s_date,e_date;
            cout<<"Starting Date (YYYY-MM-DD) (or no) : ";
            cin>>s_date;
            cout<<"Ending Date (YYYY-MM-DD) (or no) : ";
            cin>>e_date;
            expense.deleteDateCriteria(s_date,e_date,catTrie,subcatTrie);
            break;
        }
        
        case 4 :{
            cout<<"Select Subcategories : "<<endl;
            vector<string> subcategories;
            while(true){
                string s;
                cout<<"Subcategory (type no if done) : ";
                cin>>s;
                if(s=="no") break;
                subcatTrie.remove(s);
                subcategories.push_back(s);
            }
            expense.deleteSubcategoryCriteria(subcategories);
            cout<<"Successfully Deleted!!!"<<endl;
            break;
        }
        case 5 :{
            double s_amount,e_amount;
            cout<<"Starting Amount  (or -1) : ";
            cin>>s_amount;
            cout<<"Ending Amount  (or -1) : ";
            cin>>e_amount;
            expense.deleteAmountCriteria(s_amount,e_amount,catTrie,subcatTrie);
            break;
        }
        case 6 :{
            cout<<"Select Categories : "<<endl;
            vector<string> categories;
            while(true){
                string s;
                cout<<"Category (type no if done) : ";
                cin>>s;
                if(s=="no") break;
                categories.push_back(s);
            }
            cout<<"Select Subcategories : "<<endl;
            vector<string> subcategories;
            while(true){
                string s;
                cout<<"Subcategory (type no if done) : ";
                cin>>s;
                if(s=="no") break;
                subcategories.push_back(s);
            }

            string s_date,e_date;
            cout<<"Starting Date (YYYY-MM-DD) (or no) : ";
            cin>>s_date;
            cout<<"Ending Date (YYYY-MM-DD) (or no) : ";
            cin>>e_date;

            double s_amount,e_amount;
            cout<<"Starting Amount  (or -1) : ";
            cin>>s_amount;
            cout<<"Ending Amount  (or -1) : ";
            cin>>e_amount;

            expense.deleteMultipleCriteria(categories,subcategories,s_date,e_date,s_amount,e_amount,catTrie,subcatTrie);
            cout<<"Successfully Deleted!!!"<<endl;
            break;

        }
        default :{
            cout<<"Invalid choice"<<endl;
        }

    }
}

    void checkBalance()
    {
    cout << "=============================================" << endl;
    cout << "             Budget Summary                 " << endl;
    cout << "=============================================" << endl;
    
    cout << "Current Budget       : Rs" << budget.total << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Total Expenses       : Rs" << expense.total << endl;
    cout << "---------------------------------------------" << endl;
    
    double netBalance = budget.total - expense.total;
    cout << "Net Balance          : Rs" << netBalance << endl;
    cout << "=============================================" << endl;
    }

};

void displayMenu()
{
    cout << endl;
    cout << "==========================================" << endl;
    cout << "               FinTrack                  " << endl;
    cout << "       Your Personal Finance Manager     " << endl;
    cout << "==========================================" << endl;

    cout << "Menu Options:" << endl;
    cout << "1. Set Budget" << endl;
    cout << "2. Record a New Expense" << endl;
    cout << "3. View Current Balance" << endl;
    cout << "4. Update Budget" << endl;
    cout << "5. See Budget"<<endl;
    cout << "6. Undo Recent Transaction" << endl;
    cout << "7. Search Transaction Records" << endl;
    cout << "8. Delete Transactions" << endl;
    cout << "9. Exit Application" << endl<<endl;

    cout << "Please select an option (1-9): ";
}

int main()
{
    PersonalFinanceTracker fintrack;
    

    while(true)
    {   int choice;
        displayMenu(); 
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            vector<string> categories;
            vector<double> amounts;
            vector<string> descriptions;

            cout << "===========================" << endl;
            cout << "      Add Categories       " << endl;
            cout << "===========================" << endl;

            cout << "Enter the details for each category. Type 'no' when you are done adding categories." << endl;

            while (true)
            {
                cout << "Category (or 'no' to finish): ";
                string categoryInput;
                cin >> categoryInput;

                if (categoryInput == "no")
                {
                    cout << "Category entry completed successfully!" << endl;
                    break;
                }

                categories.push_back(categoryInput);

                cout << "Enter Amount for category '" << categoryInput << "': ";
                double amountInput;
                cin >> amountInput;
                amounts.push_back(amountInput);

                cout << "Enter Description for category '" << categoryInput << "': ";
                cin.ignore(); 
                string descriptionInput;
                getline(cin, descriptionInput);
                descriptions.push_back(descriptionInput);

                cout << "Category '" << categoryInput << "' added successfully!" << endl<<endl;
            }

            cout << "All categories recorded successfully!" << endl;
            fintrack.setBudget(categories,amounts,descriptions);
            break;
        }

        case 2:
        {
            string date, category,subcategory, details;
            double amount;

            cout << "Enter Date (YYYY-MM-DD): ";
            cin >> date;

            cout << "Enter Expense Category: ";
            cin >> category;

            cout << "Enter Expense subcategory: ";
            cin >> subcategory;

            cout << "Enter Amount: ";
            cin >> amount;

            cout << "Enter Description: ";
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

            getline(cin, details);

            fintrack.addExpense(date, category,subcategory, amount, details);
            cout << "Expense added successfully!" << endl;
            break;
        }

        case 3:
        {
            fintrack.checkBalance();
            break;
        }
        
        case 4 : 
        {
            fintrack.updateBudget();
            break;
        }
        
        case 5 :
        {
            fintrack.seeBudget();
            break;
        }

        case 6:
        {
            fintrack.undoTransaction();
            cout << "Last transaction undone successfully!" << endl;
            break;
        }

        case 7:
        {
            fintrack.searchTransactions();
            break;
        }
        
        case 8:
        {
            fintrack.deleteTransactions();
            break;
        }

        case 9:
        {
            cout << "Thank you for using FinTrack. Exiting..." << endl;
            return 0;
            break;
        }

        default:
        {
            cout << "Invalid choice. Please select a valid option (1-9)." << endl;
            break;
        }
        }
    } 

    return 0;
}