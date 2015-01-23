#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


struct Item {
  Item(int v, Item* n) { val = v; next = n; }
  int val;
  Item* next;
};

void append (Item *&head, int n) { //Copied from lecture
  Item *newElement = new Item (n, NULL);
  if (head == NULL) {
    head = newElement;
  }
  else {
    Item *p = head;
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = newElement;
  }
}


Item* concathelper(Item*& output, Item* input){
  
  if (input == NULL){
    return output;
  }
  else{
    append(output, input->val);
    return concathelper(output, input->next);
  }
}

Item* concatenate(Item* head1, Item* head2){
  if (head1 == NULL && head2 == NULL)
    return NULL;
  else if (head1 == NULL)
    return head2;
  else if (head2 == NULL)
    return head1;
  
  else{
    Item* output = NULL;
    output = concathelper(output, head1); //Recursion
    output = concathelper(output, head2);
    return output;
  }
}
void rmhelper(Item* curr){

  if (curr->next == NULL)
    return;
  
  else {
    int x = curr->next->val;
    if (x%2 == 0){
      Item* q = curr->next;
      curr->next = curr->next->next;
      delete q;
      rmhelper(curr); //Recursion
    }
    else{
      rmhelper(curr->next);
    }
  }
}
    
      
void removeEvens(Item*& head){

  if (head == NULL)
    return;
    
  else {
    Item* p = head;
    int x = p->val;
    if (x%2 == 0){
      head = head->next;
      delete p;
    }
    rmhelper(p);
  }
}

void fahelper (int &count, int &sum, Item* curr){
  
  if (curr == NULL)
    return;
  else {
    
    count += 1;
    sum += curr->val;
    fahelper(count, sum, curr->next); //Recursion
  }
}
double findAverage(Item* head){

  if (head == NULL)
    return 0;
  else {
    int count = 0;
    int sum = 0;
    fahelper(count, sum, head);
    double result = ((double)sum)/count;
    return result;
  }
}

//Return string of values in linked list    
string printout (Item* input){  
  Item* p = input;
  ostringstream oss;
  while (p != NULL){
    oss << p->val << " ";
    p = p->next;
  }
  oss << '\n';
  return oss.str();
}

void deletelist (Item* head){ //Free memory

  if (head == NULL)
    return;
    
  else{
  
    while (head != NULL){
      Item* p = head;
      head = head->next;
      delete p;
    }
  }
}    
    
int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Wrong argument count" << endl;
    return 1;
  }

  ifstream ifile(argv[1]);
  string list1, list2;
  getline(ifile, list1);
  getline(ifile, list2);
  
  Item* head1 = NULL;
  Item* head2 = NULL;
  
  istringstream iss1 (list1);
  istringstream iss2 (list2);
  
  int val1;
  iss1 >> val1;
  while (!iss1.fail()){ //Create list1
    append (head1, val1);    
    iss1 >> val1;  
  }
  
  
  int val2;
  iss2 >> val2;
  while (!iss2.fail()){ //Create list2
    append (head2, val2);
    iss2 >> val2;
  }
  
  
  ofstream ofile(argv[2]);
  
  
  Item* head3 = concatenate(head1, head2); //Concat function
  string concatted = printout(head3);
  ofile << concatted;
  
  
  removeEvens(head3); //Remove evens function
  string removedE = printout(head3); 
  ofile << removedE;
  
  
  double average = findAverage(head3); //Find average
  string averaged = printout(head3);
  ofile << averaged;
  ofile << average;
  
  deletelist(head1); //Free memories
  deletelist(head2);
  deletelist(head3);
  
  return 0;
}
