#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int counter = -1; //introducing a counter to hold the UID number

struct product //creating the sture called product
{
	string productName;
	string description;
	string reason;
	double unitP;
	int qih;
	int PID;
	int UID;
	char productStat;

	struct product *nextPtr; //creating the link that connects to the other linked lists

};

struct queueNode
{
	string productName;
	string description;
	string reason;
	double unitP;
	int qih;
	int PID;
	int UID;
	char productStat;
	

	struct queueNode *nextPtr;
};

struct stackNode 
{
	string productName;
	string description;
	string reason;
	double unitP;
	int qih;
	int PID;
	int UID;
	char productStat;

	struct stackNode *nextPtr;

};

typedef struct product Product;
typedef Product *ProductPtr;

typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;

typedef struct stackNode StackNode;
typedef  StackNode *StackNodePtr;

int productIdArray[100] = { 0 }; //introducing an array to save the PID number
int productUidArray[100] = { 0 }; //introducing an array to save the UID number


//PROTOTYPES
bool searchPID(int searchKey, int PID[], int arraySize);
bool searchUID(int searchKey, int UID[], int arraySIze);
bool setProductIDNum(int PID);
void insert(ProductPtr *sPtr, string productName, string description, double unitP, int qih, int PID, int UID);
void deleteProduct(ProductPtr *sPtr, int PID);
void addProduct(ProductPtr *startPtr);
void removeProduct(ProductPtr *startPtr);
void updateProduct(ProductPtr *sPtr);
void displayProduct(ProductPtr currentPtr);
void displayAllProducts(ProductPtr currentPtr);
void suspendPendingProduct(ProductPtr startPtr, QueueNodePtr *headPtr, QueueNode *tailPtr);
void approveRejectSuspendedProduct(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, StackNodePtr *topPtr);
void updateProductStatus(StackNodePtr stackPtr, Product startPtr);
void displayCompleted(ProductPtr currentPtr);
void displayPending(ProductPtr currentPtr);
void displayRejected(ProductPtr currentPtr);


bool searchPID(int searchKey, int productIdArray[], int arraySize) //function to search the PID
{
	for (int j = 0; j < arraySize; j++) {
		if (productIdArray[j] == searchKey) {
			return true;
		}
	}
	return false;
}
bool searchUID(int searchKey, int productUidArray[], int arraySize) //function to search the UID
{
	for (int k = 0; k < arraySize; k++) {
		if (productUidArray[k] == searchKey) {
			return true;
		}
	}
	return false;
}

void addProduct(ProductPtr *startPtr) //Add Product Function
{
	string productName; //introducing the variables
	string description;
	double unitP;
	int qih = 0;
	int UID = 0;
	int searchKey;
	int arraySize = 100;

	cout << "Enter the product ID without letters" << endl; //searching if the product ID already exists
	cin >> searchKey; //using the searchKey varible to hold the search value to use against the search function

	if (searchPID(searchKey, productIdArray, arraySize) == false) {//input the name
		cout << "\nEnter the product Name: " << endl;
		cin.ignore(); //used to ignore the white spaces inn the input
		getline(cin, productName);

		cout << "\nEnter product description: " << endl; //input the description
		getline(cin, description);

		cout << "\nEnter product Unit Price: " << endl;//input the Unit Price
		cin >> unitP;

		cout << "\nEnter Quantity In Hand: " << endl;//input the quantity in hand
		cin >> qih;

		productUidArray[counter] = ++counter; //increment the counter
		UID = productUidArray[counter]; //save that value in the productUID array
		cout << "\nUnique Product ID is: " << UID << endl;

		if (setProductIDNum(searchKey) == true) {
			insert(startPtr, productName, description, unitP, qih, searchKey, UID);
			cout << "\nProduct successfully added! " << endl;

		}
		else {
			cout << "\nProduct already registered!" << endl;
		}
		cout << "\n" << endl;
	}
}

bool setProductIDNum(int PID) {
		  for (int i = 0; i < 100; i++) {
			  if (productIdArray[i] == 0) {
				  productIdArray[i] = PID;
				  return true;
			  }
		  }
		  return false;
	  }

void removeProduct(ProductPtr *startPtr) { //remove product function
		  int searchKey = 0;
		  int arraySize = 100;
		  cout << "\nEnter Product ID: " << endl; //search the existence of UID
		  cin >> searchKey;

		  if (searchUID(searchKey, productUidArray, arraySize) != 0) {//access the search function
			  deleteProduct(startPtr, searchKey);
			  cout << "Product has been successfully removed!" << endl;
		  }
		  else {
			  cout << "\nProduct ID does not exist" << endl; //output if variable is nonexistent
		  }
	  }

void updateProduct(ProductPtr *sPtr) { //the update product function
	 int tempUpdate = 0;
	 int arraySize = 100;
	 int searchKey = 0;
	 int updateQIH;
	 double updateUnitP;

	 cout << "\nEnter Product ID: " << endl;
	 cin >> searchKey;

	 if (searchUID(searchKey, productUidArray, arraySize) != 0) {
		 cout << "\nEnter the updated Unit Price " << endl;
		 cin.ignore();
		 cin >> updateUnitP;

		 cout << "\nEnter the updated Product quantity in hand" << endl;
		 cin >> updateQIH;

		 ProductPtr currentPtr = NULL;
		 ProductPtr previousPtr = NULL;

		 if (searchKey == (*sPtr)->UID) {
			 (*sPtr)->unitP = updateUnitP;
			 (*sPtr)->qih = updateQIH;

			 cout << "\nProduct Information Successfully Updated!" << endl;
		 }
		 else {
			 previousPtr = *sPtr;
			 currentPtr = (*sPtr)->nextPtr;

			 while (currentPtr != NULL && searchKey != currentPtr->UID) {
				 previousPtr = currentPtr;
				 currentPtr = currentPtr->nextPtr;
			 }
			 if (currentPtr != NULL) {
				 currentPtr->unitP = updateUnitP;
				 currentPtr->qih = updateQIH;
				 cout << "\nProduct Information Updated!" << endl;

			 }
		 }
	 }
	 else {
		 cout << "\nNon Existent Product PID! " << endl;
	 }
	 cout << "\n" << endl;

 }
			     
void suspendPendingProduct(ProductPtr startPtr, QueueNodePtr *headPtr, QueueNodePtr *tailPtr)
 {
	 int searchKey = 0;
	 int arraySize = 100;
	 cout << "\nEnter the Product ID: " << endl;
	 cin >> searchKey;

	 if (searchUID(searchKey, productUidArray, arraySize) == true) {
		 ProductPtr currentProdPtr = startPtr;
		 ProductPtr previousProdPtr = NULL;

		 while (currentProdPtr != NULL && searchKey != currentProdPtr->UID) {
			 previousProdPtr = currentProdPtr;
			 currentProdPtr = currentProdPtr->nextPtr;
		 }

		 if (currentProdPtr->productStat == 'S')
			 cout << "\nProduct has been marked approved!" << endl;
		 else if (currentProdPtr->productStat == 'A')
			 cout << "\nProduct has been marked Rejected!" << endl;
		 else {
			 string reason;
			 cout << "\nPlease provide a proper reason why the product is to be Suspended: " << endl;
			 cin.ignore();
			 getline(cin, reason);

			 currentProdPtr->productStat = 'S';
			 QueueNodePtr newPtr;
			 newPtr = new QueueNode;

			 if (newPtr != NULL) {

				 newPtr->productName = currentProdPtr->productName;
				 newPtr->description = currentProdPtr->description;
				 newPtr->qih = currentProdPtr->qih;
				 newPtr->unitP = currentProdPtr->unitP;
				 newPtr->PID = currentProdPtr->PID;
				 newPtr->UID = currentProdPtr->UID;
				 newPtr->productStat = currentProdPtr->productStat;
				 newPtr->reason = currentProdPtr->productStat;
				 newPtr->nextPtr = NULL;

				 if (*headPtr == NULL) {
					 *headPtr = newPtr;
				 }
				 else {
					 (*tailPtr)->nextPtr = newPtr;

				 }
				 *tailPtr = newPtr;
				 cout << "\nThe Suspended Product has been successfully added to the queue!" << endl;
			 }
			 else
				 cout << "\nCould not be added to the Suspended Product queue! " << endl;
		 }
	 }
	 else {
		 cout << "\nThe Product file does not exist! " << endl;
	 }					
}

void approveRejectSuspendedProduct(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, StackNodePtr *topPtr) {

	 int searchKey = 0;
	 int arraySize = 100;
	 cout << "\nEnter the ProductID: " << endl;
	 cin >> searchKey;

	 if (searchUID(searchKey, productUidArray, arraySize) == true) {
		 QueueNodePtr currentProdPtr = *headPtr;
		 QueueNodePtr previousProdPtr = NULL;

		 while (currentProdPtr != NULL && searchKey != currentProdPtr->UID) {
			 previousProdPtr = currentProdPtr;
			 currentProdPtr = currentProdPtr->nextPtr;
		 }
		 char temp;
		 cout << "\nProduct information found in the queue: " << endl;
		 cout << "\nName of the Product: " << currentProdPtr->productName << endl;
		 cout << "\nProduct ID: " << currentProdPtr->PID << endl;
		 cout << "Product Status: " << currentProdPtr->productStat << endl;
		 cout << "\nEnter updated productStatus: " << endl;
		 cin >> temp;

		 if (temp == 'A' || temp == 'N') {
			 StackNodePtr newPtr;
			 newPtr = new StackNode;

			 if (newPtr != NULL) {
				 newPtr->productName = currentProdPtr->productName;
				 newPtr->description = currentProdPtr->description;
				 newPtr->qih = currentProdPtr->qih;
				 newPtr->unitP = currentProdPtr->unitP;
				 newPtr->PID = currentProdPtr->PID;
				 newPtr->productStat = currentProdPtr->productStat;
				 newPtr->reason = currentProdPtr->productStat;
				 *topPtr = newPtr;

				 cout << "Product data successfully added! " << endl;
			 }
			 else
				 cout << "Product information is not successfully added!" << endl;
		 }
		 else
			 cout << "The entered product status is incorrect" << endl;
	 }
	 else
		 cout << "Non existent product file" << endl;
 }

void displayMenu() //Menu Creation
 {
	 cout << "   EBUY SUPERMARKET     " << endl;
	 cout << "       Menu      " << endl;
	 cout << "1.  Add product" << endl;
	 cout << "2.  Remove product" << endl;
	 cout << "3.  Update product" << endl;
	 cout << "4.  View product" << endl;
	 cout << "5.  View all products" << endl;
	 cout << "6.  Suspend Pending products" << endl;
	 cout << "7.  Approve/Reject suspended product" << endl;
	 cout << "8.  Update Product Status" << endl;
	 cout << "9.  View approved product" << endl;
	 cout << "10. View suspended product" << endl;
	 cout << "11. View rejected product" << endl;
	 cout << "12. Close Program " << endl;

	 cout << "\n" << endl;
 }

void updateProductStatus(StackNodePtr stackPtr, ProductPtr startPtr) {
	 int searchKey = 0;
	 int arraySize = 100;
	 cout << "Enter Product ID: " << endl;
	 cin >> searchKey;

	 if (searchUID(searchKey, productUidArray, arraySize) == true) {
		 StackNodePtr currentProdPtr = stackPtr;
		 StackNodePtr previousProdPtr = NULL;

		 while (currentProdPtr != NULL && searchKey != currentProdPtr->UID) {
			 previousProdPtr = currentProdPtr;
			 currentProdPtr = currentProdPtr->nextPtr;
		 }
		 cout << "Product information found in the LIFO file " << endl;

		 ProductPtr currentPtr = startPtr;
		 ProductPtr previousPtr = NULL;

		 while (currentPtr != NULL && searchKey != currentPtr->UID) {
			 previousPtr = currentPtr;
			 currentPtr = currentPtr->nextPtr;
		 }
		 currentPtr->productStat = currentProdPtr->productStat;
		 cout << "Product records have been updated!" << endl;
	 }
	 else
		 cout << " Non existent product file!" << endl;
 }

 void insert(ProductPtr *sPtr, string productName, string description, double unitP, int qih, int PID, int UID) //Insert function with the different variables which is passed through
 {
	 ProductPtr newPtr = NULL; //creating newPtr
	 ProductPtr currentPtr = NULL; //creating currentPtr
	 ProductPtr previousPtr = NULL; //creating previousPtr

	 newPtr = new Product;

	 if (newPtr != NULL) //saving the  varible in the linked lists
	 {
		 newPtr->productName = productName;
		 newPtr->description = description;
		 newPtr->qih = qih;
		 newPtr->unitP = unitP;
		 newPtr->PID = PID;
		 newPtr->UID = UID;
		 newPtr->nextPtr = NULL;
		 previousPtr = NULL;
		 currentPtr = *sPtr;

		 while (currentPtr != NULL && UID > currentPtr->UID) {//the code which allows the program to move through the linked list
			 previousPtr = currentPtr;
			 currentPtr = currentPtr->nextPtr;
		 }
		 if (previousPtr == NULL) { 
			 newPtr->nextPtr = *sPtr;
			 *sPtr = newPtr;
		 }
		 else {
			 previousPtr->nextPtr = newPtr;
			 newPtr->nextPtr = currentPtr;
		 }
	 }
	 else {
		 cout << "Could not create a product file. " << endl;
	 }
 }

 void deleteProduct(ProductPtr *sPtr, int UID) //delete product function that links to the linked lists and the addProduct function
 {
	 ProductPtr previousPtr = NULL;
	 ProductPtr currentPtr = NULL;
	 ProductPtr tempPtr = NULL;

	 if (UID == (*sPtr)->UID) {
		 tempPtr = *sPtr;
		 *sPtr = (*sPtr)->nextPtr;
		 delete (tempPtr); //temp variable which holds the class until deletion
		 productIdArray[UID] = 0;
		 productUidArray[UID] = 0;
		 return;
	 }
	 else {
		 previousPtr = *sPtr;
		 currentPtr = (*sPtr)->nextPtr;

		 while (currentPtr != NULL && currentPtr->UID != UID) {
			 previousPtr = currentPtr;
			 previousPtr->nextPtr = currentPtr->nextPtr; //moving the connections in the linked lists
		 }
		 if (currentPtr != NULL) {
			 tempPtr = currentPtr;
			 previousPtr->nextPtr = currentPtr->nextPtr;
			 delete (tempPtr);
			 productIdArray[UID] = 0;
			 productUidArray[UID] = 0;

		 }
	 }
 }

 void displayProduct(ProductPtr startPtr) //print product function
 {
	 int searchKey = 0;
	 int arraySize = 100;
	 cout << "Enter the Product ID: " << endl;
	 cin >> searchKey;


	 if (searchUID(searchKey, productUidArray, arraySize)) {
		 ProductPtr currentProdPtr = startPtr;
		 ProductPtr previousProdPtr = NULL;

		 while (currentProdPtr != NULL && searchKey != currentProdPtr->UID) {
			 previousProdPtr = currentProdPtr;
			 currentProdPtr = currentProdPtr->nextPtr;
		 }

		 while (currentProdPtr != NULL) {

			 cout << "Product Name: " << currentProdPtr->productName << endl;
			 cout << "Product Description: " << currentProdPtr->description << endl;
			 cout << "Product Quantity In Hand: " << currentProdPtr->qih << endl;
			 cout << "Product Unit Price: " << currentProdPtr->unitP << endl;
			 cout << "Product ID: " << currentProdPtr->PID << endl;
			 cout << "Product UID Number: " << currentProdPtr->UID << endl;
			 cout << "Product Status" << currentProdPtr->productStat << endl;
			 cout << "\n" << endl;

			 break;
		 }
	 }
	 else
		 cout << "Product ID is invalid " << endl;
 }

 void displayAllProducts(ProductPtr currentPtr) { //print all products function

	 if (currentPtr == NULL) {
		 cout << " Product information is non existent! \n\n" << endl;
		 displayMenu();
	 }
	 else
		 while (currentPtr != NULL) {
			 cout << "Product Name: " << currentPtr->productName << endl;
			 cout << "Product ID number: " << currentPtr->UID << endl;
			 cout << "\n\n Next Product\n\n" << endl;
			 currentPtr = currentPtr->nextPtr;
		 }
 }

 void displayCompleted(ProductPtr currentPtr)
 {
	 if (currentPtr == NULL)
	 {
		 cout << "Product Information does not exist! " << endl;
	 }
	 else {

		 cout << "Product Information is: " << endl;
		 while (currentPtr != NULL)
		 {
			 if (currentPtr->productStat == 'A')
			 {
				 cout << "\nProduct name: " << currentPtr->productName << endl;
				 cout << "\nProduct ID: " << currentPtr->PID << endl;
				 currentPtr = currentPtr->nextPtr;
			 }
			 else {
				 currentPtr = currentPtr->nextPtr;
			 }
		 }
	 }
 }

 void displayPending(ProductPtr currentPtr)
 {
	 if (currentPtr == NULL)
	 {
		 cout << "Product information does not exist!" << endl;
	 }
	 else {
		 cout << "Product information is: " << endl;
			 while (currentPtr != NULL) {
				 if (currentPtr->productStat == 'P') {
					 cout << "\nProduct name: " << currentPtr->productName << endl;
					 cout << "\nProduct ID: " << currentPtr->PID << endl;
					 currentPtr = currentPtr->nextPtr;

				 }
				 else {
					 currentPtr = currentPtr->nextPtr;
				 }
		 }
	 }
 }

 void displayRejected(ProductPtr currentPtr)
 {
	 if (currentPtr == NULL)
	 {
		 cout << "Product information does not exist!" << endl;
	 }
	 else {
		 cout << "Product Information is: " << endl;
		 while (currentPtr != NULL) {
			 if (currentPtr->productStat == 'R') {
				 cout << "\nProduct name: " << currentPtr->productName << endl;
				 cout << "\nProduct ID: " << currentPtr->UID << endl;
				 currentPtr = currentPtr->nextPtr;
			   }
			   else {
				   currentPtr = currentPtr->nextPtr;
			  }
		  }
	  }
   }

 int main() //main function
 {
	 ProductPtr startPtr = NULL;
	 QueueNodePtr headPtr = NULL;
	 QueueNodePtr tailPtr = NULL;
	 StackNodePtr stackPtr = NULL;

	 displayMenu(); //call the menu
	 int choice; //variable to hold the choice input by the user
	 cin >> choice; //input the choice

	 while (choice != 13) {
		 switch (choice) {

		 case 1: 
			 addProduct(&startPtr);
			 break;
		 case 2:
			 removeProduct(&startPtr);
			 break;
		 case 3:
			 updateProduct(&startPtr);
			 break;
		 case 4:
			 displayProduct(startPtr);
			 break;
		 case 5:
			 displayAllProducts(startPtr);
			 break;
		 case 6:
			 suspendPendingProduct(startPtr, &headPtr, &tailPtr);
			 break;
		 case 7:
			 approveRejectSuspendedProduct(&headPtr, &tailPtr, &stackPtr);
			 break;
		 case 8:
			 updateProductStatus(stackPtr, startPtr);
			 break;
		 case 9:
			 displayCompleted(startPtr);
			 break;
		 case 10: 
			 displayPending(startPtr);
			 break;
		 case 11:
			 displayRejected(startPtr);
			 break;
		 case 12:
			 return 0;
			 break;
		 }
		 cout << "\n" << endl;
		 displayMenu();
		 cout << "\n" << endl;
		 cin >> choice;
     //closing the main method
	 }
 }
 




	 




 

