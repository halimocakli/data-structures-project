#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define TXT_SIZE 500000
#define STUDENT_SIZE 9492

struct arrayNode {
	int ID;
	char name[20];
	char surname[20];
	int year;
	int totalECTS;
	double grade;
};
typedef struct arrayNode StudentArray;

struct binarySearchTreeNode {
	int ID;
	char name[20];
	char surname[20];
	int year;
	int totalECTS;
	double grade;
	struct binarySearchTreeNode* rightNode;
	struct binarySearchTreeNode* leftNode;
};
typedef struct binarySearchTreeNode StudentBTREE;

struct avlNode {
	int ID;
	char name[20];
	char surname[20];
	int year;
	int totalECTS;
	double grade;
	int height;
	struct avlNode* rightNode;
	struct avlNode* leftNode;
};
typedef struct avlNode StudentAVL;

void CreateStudentArray(FILE*, StudentArray[], int*);
void CreateStudentBST(FILE*, StudentBTREE**, int*);
void CreateStudentAVL(FILE*, StudentAVL**, int*);
StudentArray SearchStudentArray(StudentArray[], int, int*, int*);
StudentBTREE* InitializationBST(int, char*, char*, int, int, double);
StudentBTREE* InsertBST(StudentBTREE*, int, char*, char*, int, int, double);
StudentAVL* InitializationAVL(int, char*, char*, int, int, double);
StudentAVL* InsertAVL(StudentAVL*, int, char*, char*, int, int, double);
StudentAVL* RightRotation(StudentAVL*);
StudentAVL* LeftRotation(StudentAVL*);
StudentBTREE* DeleteStudentBST(StudentBTREE*, int);
StudentAVL* DeleteStudentAVL(StudentAVL*, int);
StudentBTREE* SearchStudentBST(StudentBTREE*, int, int*);
StudentAVL* SearchStudentAVL(StudentAVL*, int, int*);
int HeightBST(StudentBTREE*);
int HeightAVL(StudentAVL*);
int NodeHeightAVL(StudentAVL*);
int MaxValue(int, int);
int BalanceCalc(StudentAVL* _root, int, int);
int SizeBST(StudentBTREE*);
int SizeAVL(StudentAVL*);
int LeafNodeCounterBST(StudentBTREE*);
int LeafNodeCounterAVL(StudentAVL*);
StudentBTREE* MinNodeBST(StudentBTREE*);
StudentBTREE* MaxNodeBST(StudentBTREE*);
StudentAVL* MinNodeAVL(StudentAVL*);
StudentAVL* MaxNodeAVL(StudentAVL*);
void PrintStudentArray(StudentArray);
void PrintStudentBST(StudentBTREE*);
void PrintStudentAVL(StudentAVL*);
double CpuTimeCal(int, int);
void MainMenu();
void ArrayDTMenu();
void BSTMenu();
void AVLMenu();
void ClearScreen();

int main()
{
	FILE* ptrFile = NULL;

	StudentArray student[STUDENT_SIZE];
	StudentBTREE* mainRootBST = NULL;
	StudentAVL* mainRootAVL = NULL;

	int mainSelection;
	int arraySelection;
	int bstSelection;
	int avlSelection;
	int ID;
	int deleteID;
	int createFlag = 0;
	int heightBST;
	int heightAVL;
	int sizeBST;
	int sizeAVL;
	int leafNodesBST;
	int leafNodesAVL;
	clock_t start;
	clock_t end;
	double cpuTimeUsed;

	do {
		MainMenu();

		printf(" Insert the option number of data structure which you are going to implement: ");
		scanf("%d", &mainSelection);

		switch (mainSelection)
		{
		case 0:
			printf("\n Process has been ended.\n");
			break;

		case 1:
			do {
				StudentArray tempStudentArray;
				int studentLine = 1;
				int searchFlag = 0;

				ArrayDTMenu();

				printf(" Insert the option number of data structure which you are going to implement: ");
				scanf("%d", &arraySelection);

				switch (arraySelection)
				{
				case 0:
					printf("\n Array structure implementation process has been ended.\n");
					break;

				case 1:
					start = clock();
					CreateStudentArray(ptrFile, student, &createFlag);
					end = clock();

					cpuTimeUsed = CpuTimeCal(start, end);

					printf("\n Student array has been created. Process time: %lf seconds", cpuTimeUsed);
					break;

				case 2:
					if (createFlag != 0)
					{
						printf("\n Insert the student's ID number that you want to search: ");
						scanf("%d", &ID);

						start = clock();
						tempStudentArray = SearchStudentArray(student, ID, &studentLine, &searchFlag);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						if (searchFlag == 1)
						{
							printf("\n Student has been found at %d. line. Process time is %lf seconds\n", studentLine, cpuTimeUsed);
							PrintStudentArray(tempStudentArray);
						}
						else
						{
							printf("\n There is no student that has %d ID number. Process time is %lf seconds", ID, cpuTimeUsed);
						}
					}
					else
					{
						printf("\n You did not create any structure array yet that collects students information so, you can not able to search any data...\n");
					}
					break;

				case 3:
					ClearScreen();
					break;

				default:
					printf("\n Undefined number, please insert a number that stated at the menu.");
					break;
				}
			} while (arraySelection != 0 && arraySelection != 3);
			break;

		case 2:
			do {
				StudentBTREE* tempStudentBST;
				int searchFlag = 0;

				BSTMenu();

				printf(" Insert the option number of data structure which you are going to implement: ");
				scanf("%d", &bstSelection);

				switch (bstSelection)
				{
				case 0:
					printf("\n Binary search tree implementation process has been ended.\n");
					break;

				case 1:
					start = clock();
					CreateStudentBST(ptrFile, &mainRootBST, &createFlag);
					end = clock();

					cpuTimeUsed = CpuTimeCal(start, end);

					printf("\n Student binary search tree has been created. Process time: %lf seconds\n", cpuTimeUsed);
					break;

				case 2:
					if (createFlag != 0)
					{
						printf("\n Insert the student's ID number that you want to search: ");
						scanf("%d", &ID);

						start = clock();
						tempStudentBST = SearchStudentBST(mainRootBST, ID, &searchFlag);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						if (searchFlag == 1)
						{
							printf("\n Student has been found. Process time is %lf seconds", cpuTimeUsed);
							PrintStudentBST(tempStudentBST);
						}
						else
						{
							printf("\n There is no student that has %d ID number. Process time is %lf seconds", ID, cpuTimeUsed);
						}
					}
					else
					{
						printf("\n You did not create any binary search tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 3:
					if (createFlag != 0)
					{
						printf("\n Insert the student's ID number that you want to delete from BST: ");
						scanf("%d", &deleteID);

						start = clock();
						mainRootBST = DeleteStudentBST(mainRootBST, deleteID);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Student deleted. Process time is %lf seconds", cpuTimeUsed);
					}
					else
					{
						printf("\n You did not create any binary search tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 4:
					if (createFlag != 0)
					{
						start = clock();
						heightBST = HeightBST(mainRootBST);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Height of BST is %d. Process time is %lf seconds\n", heightBST, cpuTimeUsed);
					}
					else
					{
						printf("\n You did not create any binary search tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 5:
					if (createFlag != 0)
					{
						start = clock();
						sizeBST = SizeBST(mainRootBST);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Size of the BST is %d. Process time is %lf seconds\n", sizeBST, cpuTimeUsed);
					}
					else
					{
						printf("\n You did not create any binary search tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 6:
					if (createFlag != 0)
					{
						start = clock();
						leafNodesBST = LeafNodeCounterBST(mainRootBST);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Number of leaf nodes in the BST is %d. Process time is %lf seconds\n", leafNodesBST, cpuTimeUsed);
					}
					else
					{
						printf("\n You did not create any binary search tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 7:
					if (createFlag != 0)
					{
						start = clock();
						tempStudentBST = MinNodeBST(mainRootBST);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Lowest ID-student's information listed below... Process time is %lf seconds", cpuTimeUsed);
						PrintStudentBST(tempStudentBST);
					}
					else
					{
						printf("\n You did not create any binary search tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 8:
					if (createFlag != 0)
					{
						start = clock();
						tempStudentBST = MaxNodeBST(mainRootBST);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Highest ID-student's information listed below... Process time is %lf seconds", cpuTimeUsed);
						PrintStudentBST(tempStudentBST);
					}
					else
					{
						printf("\n You did not create any binary search tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 9:
					ClearScreen();
					break;

				default:
					printf("\n Undefined number, please insert a number that stated at the menu.");
					break;
				}
			} while (bstSelection != 0 && bstSelection != 9);
			break;

		case 3:
			do {
				StudentAVL* tempStudentAVL;
				int searchFlag = 0;

				AVLMenu();

				printf(" Insert the option number of data structure which you are going to implement: ");
				scanf("%d", &avlSelection);

				switch (avlSelection)
				{
				case 0:
					printf("\n AVL tree implementation process has been ended.\n");
					break;

				case 1:
					start = clock();
					CreateStudentAVL(ptrFile, &mainRootAVL, &createFlag);
					end = clock();

					cpuTimeUsed = CpuTimeCal(start, end);

					printf("\n Student AVL tree has been created. Process time: %lf seconds\n", cpuTimeUsed);
					break;

				case 2:
					if (createFlag != 0)
					{
						printf("\n Insert the student's ID number that you want to search: ");
						scanf("%d", &ID);

						start = clock();
						tempStudentAVL = SearchStudentAVL(mainRootAVL, ID, &searchFlag);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						if (searchFlag == 1)
						{
							printf("\n Student has been found. Process time is %lf seconds", cpuTimeUsed);
							PrintStudentAVL(tempStudentAVL);
						}
						else
						{
							printf("\n There is no student that has %d ID number. Process time is %lf seconds", ID, cpuTimeUsed);
						}
					}
					else
					{
						printf("\n You did not create any AVL tree structure yet that collects students information so, you can not able to search any data...\n");
					}
					break;

				case 3:
					if (createFlag != 0)
					{
						printf("\n Insert the student's ID number that you want to delete from AVL tree: ");
						scanf("%d", &deleteID);

						start = clock();
						mainRootAVL = DeleteStudentAVL(mainRootAVL, deleteID);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Student deleted. Process time is %lf seconds", cpuTimeUsed);
					}
					else
					{
						printf("\n You did not create any AVL tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 4:
					if (createFlag != 0)
					{
						start = clock();
						heightAVL = HeightAVL(mainRootAVL);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Height of AVL tree is %d. Process time is %lf seconds\n", heightAVL, cpuTimeUsed);
					}
					else
					{
						printf("\n You did not create any AVL tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 5:
					if (createFlag != 0)
					{
						start = clock();
						sizeAVL = SizeAVL(mainRootAVL);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Size of the AVL tree is %d. Process time is %lf seconds\n", sizeAVL, cpuTimeUsed);
					}
					else
					{
						printf("\n You did not create any binary search tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 6:
					if (createFlag != 0)
					{
						start = clock();
						leafNodesAVL = LeafNodeCounterAVL(mainRootAVL);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Number of leaf nodes in the AVL tree is %d. Process time is %lf seconds\n", leafNodesAVL, cpuTimeUsed);
					}
					else
					{
						printf("\n You did not create any AVL tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 7:
					if (createFlag != 0)
					{
						start = clock();
						tempStudentAVL = MinNodeAVL(mainRootAVL);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Lowest ID-student's information listed below... Process time is %lf seconds", cpuTimeUsed);
						PrintStudentAVL(tempStudentAVL);
					}
					else
					{
						printf("\n You did not create any AVL tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 8:
					if (createFlag != 0)
					{
						start = clock();
						tempStudentAVL = MaxNodeAVL(mainRootAVL);
						end = clock();

						cpuTimeUsed = CpuTimeCal(start, end);

						printf("\n Highest ID-student's information listed below... Process time is %lf seconds", cpuTimeUsed);
						PrintStudentAVL(tempStudentAVL);
					}
					else
					{
						printf("\n You did not create any AVL tree structure yet that collects student information so, you can not able to search any data...\n");
					}
					break;

				case 9:
					ClearScreen();
					break;

				default:
					printf("\n Undefined number, please insert a number that stated at the menu.");
					break;
				}
			} while (avlSelection != 0 && avlSelection != 9);
			break;

		default:
			printf("\n Undefined number, please insert a number that stated at the menu.\n");
			break;
		}
	} while (mainSelection != 0);

	getch();
	return 0;
}

void CreateStudentArray(FILE* ptrFile, StudentArray student[], int* _createFlag)
{
	char* buffer = NULL;
	char* token = NULL;
	char* columns[6];
	int studentCnt = 0;
	int columnCnt;

	ptrFile = fopen("Project.txt", "r");

	if (ptrFile == NULL)
	{
		printf("\n FILE OPENING ERROR!\n");
		return;
	}

	(*_createFlag) = 1;

	buffer = malloc(sizeof(char) * TXT_SIZE);

	while (fgets(buffer, TXT_SIZE, ptrFile) != NULL)
	{
		buffer[strlen(buffer) - 1] = '\0';
		columnCnt = 0;
		token = strtok(buffer, ",");

		while (token != NULL)
		{
			columns[columnCnt] = token;
			columnCnt++;
			token = strtok(NULL, ",");
		}

		student[studentCnt].ID = atoi(columns[0]);
		strcpy(student[studentCnt].name, columns[1]);
		strcpy(student[studentCnt].surname, columns[2]);
		student[studentCnt].year = atoi(columns[3]);
		student[studentCnt].totalECTS = atoi(columns[4]);
		student[studentCnt].grade = atof(columns[5]);

		studentCnt++;
	}
	free(buffer);
	fclose(ptrFile);
}

void CreateStudentBST(FILE* ptrFile, StudentBTREE** _root, int* _createFlag)
{
	char* buffer = NULL;
	char* token = NULL;
	char* columns[6];
	int columnCnt;

	ptrFile = fopen("Project.txt", "r");

	if (ptrFile == NULL)
	{
		printf("\n FILE OPENING ERROR!\n");
		return;
	}

	(*_createFlag) = 1;

	buffer = malloc(sizeof(char) * TXT_SIZE);

	while (fgets(buffer, TXT_SIZE, ptrFile) != NULL)
	{
		buffer[strlen(buffer) - 1] = '\0';
		columnCnt = 0;
		token = strtok(buffer, ",");

		while (token != NULL)
		{
			columns[columnCnt] = token;
			columnCnt++;
			token = strtok(NULL, ",");
		}

		*_root = InsertBST((*_root), atoi(columns[0]), columns[1], columns[2], atoi(columns[3]), atoi(columns[4]), atof(columns[5]));
	}
	free(buffer);
	fclose(ptrFile);
}

void CreateStudentAVL(FILE* ptrFile, StudentAVL** _root, int* _createFlag)
{
	char* buffer = NULL;
	char* token = NULL;
	char* columns[6];
	int columnCnt;

	ptrFile = fopen("Project.txt", "r");

	if (ptrFile == NULL)
	{
		printf("\n FILE OPENING ERROR!\n");
		return;
	}

	(*_createFlag) = 1;

	buffer = malloc(sizeof(char) * TXT_SIZE);

	while (fgets(buffer, TXT_SIZE, ptrFile) != NULL)
	{
		buffer[strlen(buffer) - 1] = '\0';
		columnCnt = 0;
		token = strtok(buffer, ",");

		while (token != NULL)
		{
			columns[columnCnt] = token;
			columnCnt++;
			token = strtok(NULL, ",");
		}

		*_root = InsertAVL((*_root), atoi(columns[0]), columns[1], columns[2], atoi(columns[3]), atoi(columns[4]), atof(columns[5]));
	}
	free(buffer);
	fclose(ptrFile);
}

StudentArray SearchStudentArray(StudentArray student[], int _id, int* _cnt, int* _searchFlag)
{
	int i;
	for (i = 0; i < STUDENT_SIZE; i++, (*_cnt)++)
	{
		if (student[i].ID == _id)
		{
			(*_searchFlag) = 1;
			break;
		}
	}
	return student[i];
}

StudentBTREE* InitializationBST(int _id, char _name[], char _surname[], int _year, int _totalECTS, double _grade)
{
	StudentBTREE* newNode = (StudentBTREE*)malloc(sizeof(StudentBTREE));

	newNode->ID = _id;
	strcpy(newNode->name, _name);
	strcpy(newNode->surname, _surname);
	newNode->year = _year;
	newNode->totalECTS = _totalECTS;
	newNode->grade = _grade;

	newNode->leftNode = NULL;
	newNode->rightNode = NULL;

	return newNode;
}

StudentBTREE* InsertBST(StudentBTREE* _root, int _id, char _name[], char _surname[], int _year, int _totalECTS, double _grade)
{
	if (_root == NULL)
	{
		_root = InitializationBST(_id, _name, _surname, _year, _totalECTS, _grade);
	}
	else
	{
		if (_id < (_root->ID))
		{
			_root->leftNode = InsertBST(_root->leftNode, _id, _name, _surname, _year, _totalECTS, _grade);
		}
		else
		{
			_root->rightNode = InsertBST(_root->rightNode, _id, _name, _surname, _year, _totalECTS, _grade);
		}
	}
	return _root;
}

StudentAVL* InitializationAVL(int _id, char _name[], char _surname[], int _year, int _totalECTS, double _grade)
{
	StudentAVL* newNode = (StudentAVL*)malloc(sizeof(StudentAVL));

	newNode->ID = _id;
	strcpy(newNode->name, _name);
	strcpy(newNode->surname, _surname);
	newNode->year = _year;
	newNode->totalECTS = _totalECTS;
	newNode->grade = _grade;
	newNode->height = 0;

	newNode->leftNode = NULL;
	newNode->rightNode = NULL;

	return newNode;
}

StudentAVL* InsertAVL(StudentAVL* _root, int _id, char _name[], char _surname[], int _year, int _totalECTS, double _grade)
{
	if (_root == NULL)
	{
		_root = InitializationAVL(_id, _name, _surname, _year, _totalECTS, _grade);
	}
	else
	{
		if (_id < (_root->ID))
		{
			_root->leftNode = InsertAVL(_root->leftNode, _id, _name, _surname, _year, _totalECTS, _grade);
		}
		else if (_id > (_root->ID))
		{
			_root->rightNode = InsertAVL(_root->rightNode, _id, _name, _surname, _year, _totalECTS, _grade);
		}
		else
			return _root;
	}

	int leftSubtreeHeight = NodeHeightAVL(_root->leftNode);
	int rightSubtreeHeight = NodeHeightAVL(_root->rightNode);

	_root->height = 1 + MaxValue(leftSubtreeHeight, rightSubtreeHeight);

	int nodeBalance = BalanceCalc(_root, leftSubtreeHeight, rightSubtreeHeight);

	/* LEFT-LEFT ADDING CASE <=> RIGHT ROTATION */
	if (nodeBalance > 1 && _id < _root->leftNode->ID)
	{
		return RightRotation(_root);
	}
	/* RIGHT-RIGHT ADDING CASE <=> LEFT ROTATION */
	if (nodeBalance < -1 && _id > _root->rightNode->ID)
	{
		return LeftRotation(_root);
	}
	/* LEFT-RIGHT ADDING CASE <=> LEFT-RIGHT ROTATION */
	if (nodeBalance > 1 && _id > _root->leftNode->ID)
	{
		_root->leftNode = LeftRotation(_root->leftNode);
		return RightRotation(_root);
	}
	/* RIGHT-LEFT ADDING CASE <=> RIGHT-LEFT ROTATION */
	if (nodeBalance < -1 && _id < _root->rightNode->ID)
	{
		_root->rightNode = RightRotation(_root->rightNode);
		return LeftRotation(_root);
	}

	return _root;
}

StudentAVL* RightRotation(StudentAVL* _root)
{
	StudentAVL* intendedRoot = _root->leftNode;
	_root->leftNode = intendedRoot->rightNode;
	intendedRoot->rightNode = _root;

	_root->height = MaxValue(NodeHeightAVL(_root->leftNode), NodeHeightAVL(_root->rightNode)) + 1;
	intendedRoot->height = MaxValue(NodeHeightAVL(intendedRoot->leftNode), NodeHeightAVL(intendedRoot->rightNode)) + 1;

	return intendedRoot;
}

StudentAVL* LeftRotation(StudentAVL* _root)
{
	StudentAVL* intendedRoot = _root->rightNode;
	_root->rightNode = intendedRoot->leftNode;
	intendedRoot->leftNode = _root;

	_root->height = MaxValue(NodeHeightAVL(_root->leftNode), NodeHeightAVL(_root->rightNode)) + 1;
	intendedRoot->height = MaxValue(NodeHeightAVL(intendedRoot->leftNode), NodeHeightAVL(intendedRoot->rightNode)) + 1;

	return intendedRoot;
}

StudentBTREE* DeleteStudentBST(StudentBTREE* _root, int _id)
{
	if (_root == NULL)
	{
		return NULL;
	}
	else if (_id > (_root->ID))
	{
		_root->rightNode = DeleteStudentBST(_root->rightNode, _id);
	}
	else if (_id < (_root->ID))
	{
		_root->leftNode = DeleteStudentBST(_root->leftNode, _id);
	}
	else if (_id == (_root->ID))
	{
		if ((_root->leftNode == NULL) && (_root->rightNode == NULL))
		{
			free(_root);
			return NULL;
		}
		else if (_root->leftNode == NULL)
		{
			StudentBTREE* tempNode = _root;
			_root = _root->rightNode;

			free(tempNode);
			return _root;
		}
		else if (_root->rightNode == NULL)
		{
			StudentBTREE* tempNode = _root;
			_root = _root->leftNode;

			free(tempNode);
			return _root;
		}
		else
		{
			StudentBTREE* tempNode = MinNodeBST(_root->rightNode);
			_root->ID = tempNode->ID;
			_root->rightNode = DeleteStudentBST(_root->rightNode, tempNode->ID);
		}
	}
	return _root;
}

StudentAVL* DeleteStudentAVL(StudentAVL* _root, int _id)
{
	if (_root == NULL)
		return _root;

	else
	{
		if (_id < _root->ID)
		{
			_root->leftNode = DeleteStudentAVL(_root->leftNode, _id);
		}
		else if (_id > _root->ID)
		{
			_root->rightNode = DeleteStudentAVL(_root->rightNode, _id);
		}
		else
		{
			if (_root->leftNode == NULL || _root->rightNode == NULL)
			{
				StudentAVL* tempNode = _root->leftNode ? _root->leftNode : _root->rightNode;

				if (tempNode == NULL)
				{
					tempNode = _root;
					_root = NULL;
				}
				else
				{
					*_root = *tempNode;
				}

				free(tempNode);
			}
			else
			{
				StudentAVL* tempNode = MinNodeAVL(_root->rightNode);

				_root->ID = tempNode->ID;
				_root->rightNode = DeleteStudentAVL(_root->rightNode, tempNode->ID);
			}
		}
	}

	if (_root == NULL)
		return _root;

	int leftSubtreeHeight = NodeHeightAVL(_root->leftNode);
	int rightSubtreeHeight = NodeHeightAVL(_root->rightNode);

	_root->height = 1 + MaxValue(leftSubtreeHeight, rightSubtreeHeight);

	int nodeBalance = BalanceCalc(_root, leftSubtreeHeight, rightSubtreeHeight);

	/* LEFT-LEFT ADDING CASE <=> RIGHT ROTATION */
	if (nodeBalance > 1 && _id < _root->leftNode->ID)
	{
		return RightRotation(_root);
	}
	/* RIGHT-RIGHT ADDING CASE <=> LEFT ROTATION */
	if (nodeBalance < -1 && _id > _root->rightNode->ID)
	{
		return LeftRotation(_root);
	}
	/* LEFT-RIGHT ADDING CASE <=> LEFT-RIGHT ROTATION */
	if (nodeBalance > 1 && _id > _root->leftNode->ID)
	{
		_root->leftNode = LeftRotation(_root->leftNode);
		return RightRotation(_root);
	}
	/* RIGHT-LEFT ADDING CASE <=> RIGHT-LEFT ROTATION */
	if (nodeBalance < -1 && _id < _root->rightNode->ID)
	{
		_root->rightNode = RightRotation(_root->rightNode);
		return LeftRotation(_root);
	}

	return _root;
}

StudentBTREE* SearchStudentBST(StudentBTREE* _root, int _id, int* _searchFlag)
{
	if (_root != NULL)
	{
		if (_root->ID == _id)
		{
			(*_searchFlag) = 1;
			return _root;
		}
		else if ((_root->ID) > _id)
		{
			SearchStudentBST(_root->leftNode, _id, _searchFlag);
		}
		else
		{
			SearchStudentBST(_root->rightNode, _id, _searchFlag);
		}
	}
	else
	{
		return NULL;
	}
}

StudentAVL* SearchStudentAVL(StudentAVL* _root, int _id, int* _searchFlag)
{
	if (_root != NULL)
	{
		if (_root->ID == _id)
		{
			(*_searchFlag) = 1;
			return _root;
		}
		else if ((_root->ID) > _id)
		{
			SearchStudentAVL(_root->leftNode, _id, _searchFlag);
		}
		else
		{
			SearchStudentAVL(_root->rightNode, _id, _searchFlag);
		}
	}
	else
	{
		return NULL;
	}
}

int HeightBST(StudentBTREE* _root)
{
	if (_root == NULL)
	{
		return -1;
	}
	else
	{
		int leftHeight;
		int rightHeight;

		leftHeight = HeightBST(_root->leftNode);
		rightHeight = HeightBST(_root->rightNode);

		if (rightHeight > leftHeight)
			return rightHeight + 1;
		else
			return leftHeight + 1;
	}
}

int HeightAVL(StudentAVL* _root)
{
	if (_root == NULL)
	{
		return -1;
	}
	else
	{
		int leftHeight;
		int rightHeight;

		leftHeight = HeightAVL(_root->leftNode);
		rightHeight = HeightAVL(_root->rightNode);

		if (rightHeight > leftHeight)
			return rightHeight + 1;
		else
			return leftHeight + 1;
	}
}

int NodeHeightAVL(StudentAVL* _root)
{
	if (_root == NULL)
		return -1;
	else
		return _root->height;
}

int MaxValue(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}

int BalanceCalc(StudentAVL* _root, int leftSubtreeHeight, int rightSubtreeHeight)
{
	if (_root == NULL)
		return 0;
	else
		return leftSubtreeHeight - rightSubtreeHeight;
}

int SizeBST(StudentBTREE* _root)
{
	if (_root == NULL)
		return 0;
	else
		return 1 + SizeBST(_root->leftNode) + SizeBST(_root->rightNode);
}

int SizeAVL(StudentAVL* _root)
{
	if (_root == NULL)
		return 0;
	else
		return 1 + SizeAVL(_root->leftNode) + SizeAVL(_root->rightNode);
}

int LeafNodeCounterBST(StudentBTREE* _root)
{
	if (_root == NULL)
		return 0;
	if (_root->leftNode == NULL && _root->rightNode == NULL)
		return 1;
	else
		return LeafNodeCounterBST(_root->leftNode) + LeafNodeCounterBST(_root->rightNode);
}

int LeafNodeCounterAVL(StudentAVL* _root)
{
	if (_root == NULL)
		return 0;
	if (_root->leftNode == NULL && _root->rightNode == NULL)
		return 1;
	else
		return LeafNodeCounterAVL(_root->leftNode) + LeafNodeCounterAVL(_root->rightNode);
}

StudentBTREE* MinNodeBST(StudentBTREE* _root)
{
	if (_root == NULL)
		return NULL;

	while (_root->leftNode != NULL)
	{
		_root = _root->leftNode;
	}
	return _root;
}

StudentBTREE* MaxNodeBST(StudentBTREE* _root)
{
	if (_root == NULL)
		return NULL;

	while (_root->rightNode != NULL)
	{
		_root = _root->rightNode;
	}
	return _root;
}

StudentAVL* MinNodeAVL(StudentAVL* node)
{
	if (node == NULL)
		return NULL;

	while (node->leftNode != NULL)
	{
		node = node->leftNode;
	}

	return node;
}

StudentAVL* MaxNodeAVL(StudentAVL* node)
{
	if (node == NULL)
		return NULL;

	while (node->rightNode != NULL)
	{
		node = node->rightNode;
	}

	return node;
}

double CpuTimeCal(int start, int end)
{
	return ((double)(end - start) / 1000);
}

void PrintStudentArray(StudentArray student)
{
	printf("\n\n ------------------------------------------");
	printf("\n -------------- STUDENT INFO --------------");
	printf("\n ------------------------------------------");
	printf("\n Student ID: %d", student.ID);
	printf("\n Student Name: %s", student.name);
	printf("\n Student Surname: %s", student.surname);
	printf("\n Student's Year in Education: %d", student.year);
	printf("\n Student's Total Taken ECTS: %d", student.totalECTS);
	printf("\n Student's Grade: %.1lf", student.grade);
	printf("\n ------------------------------------------\n\n");
}

void PrintStudentBST(StudentBTREE* student)
{
	printf("\n\n ------------------------------------------");
	printf("\n -------------- STUDENT INFO --------------");
	printf("\n ------------------------------------------");
	printf("\n Student ID: %d", student->ID);
	printf("\n Student Name: %s", student->name);
	printf("\n Student Surname: %s", student->surname);
	printf("\n Student's Year in Education: %d", student->year);
	printf("\n Student's Total Taken ECTS: %d", student->totalECTS);
	printf("\n Student's Grade: %.1lf", student->grade);
	printf("\n ------------------------------------------\n\n");
}

void PrintStudentAVL(StudentAVL* student)
{
	printf("\n\n ------------------------------------------");
	printf("\n -------------- STUDENT INFO --------------");
	printf("\n ------------------------------------------");
	printf("\n Student ID: %d", student->ID);
	printf("\n Student Name: %s", student->name);
	printf("\n Student Surname: %s", student->surname);
	printf("\n Student's Year in Education: %d", student->year);
	printf("\n Student's Total Taken ECTS: %d", student->totalECTS);
	printf("\n Student's Grade: %.1lf", student->grade);
	printf("\n ------------------------------------------\n\n");
}

void MainMenu()
{
	printf(" \n-------------------- MENU -------------------\n");
	printf(" 0- EXIT\n");
	printf(" 1- ARRAY DATA STRUCTURE IMPLEMENTATION\n");
	printf(" 2- BINARY SEARCH TREE DATA STRUCTURE IMPLEMENTATION\n");
	printf(" 3- AVL TREE DATA STRUCTURE IMPLEMENTATION\n");
	printf(" ---------------------------------------------\n\n");
}

void ArrayDTMenu()
{
	printf(" \n------------ ARRAY STRUCTURE MENU ------------\n");
	printf(" 0- EXIT\n");
	printf(" 1- CREATE ARRAY STRUCTURE \n");
	printf(" 2- SEARCH A STUDENT\n");
	printf(" 3- DISPLAY MAIN MENU\n");
	printf(" ---------------------------------------------\n\n");
}

void BSTMenu()
{
	printf(" \n------------ BST STRUCTURE MENU ------------\n");
	printf(" 0- EXIT\n");
	printf(" 1- CREATE BINARY SEARCH TREE \n");
	printf(" 2- SEARCH A STUDENT IN BST\n");
	printf(" 3- DELETE STUDENT FROM BST\n");
	printf(" 4- QUERY BST HEIGHT INFO\n");
	printf(" 5- QUERY BST SIZE INFO\n");
	printf(" 6- QUERY NUMBER OF LEAF NODE IN BST\n");
	printf(" 7- QUERY LOWEST ID STUDENT INFO IN BST\n");
	printf(" 8- QUERY HIGHEST ID STUDENT INFO IN BST\n");
	printf(" 9- DISPLAY MAIN MENU\n");
	printf(" ---------------------------------------------\n\n");
}

void AVLMenu()
{
	printf(" \n------------ AVL TREE STRUCTURE MENU ------------\n");
	printf(" 0- EXIT\n");
	printf(" 1- CREATE AVL TREE \n");
	printf(" 2- SEARCH A STUDENT IN AVL TREE\n");
	printf(" 3- DELETE STUDENT FROM AVL TREE\n");//
	printf(" 4- QUERY AVL TREE HEIGHT INFO\n");
	printf(" 5- QUERY AVL TREE SIZE INFO\n");
	printf(" 6- QUERY NUMBER OF LEAF NODE IN AVL TREE\n");    //
	printf(" 7- QUERY LOWEST ID STUDENT INFO IN AVL TREE\n"); //
	printf(" 8- QUERY HIGHEST ID STUDENT INFO IN AVL TREE\n");//
	printf(" 9- DISPLAY MAIN MENU\n");
	printf(" --------------------------------------------------\n\n");
}

void ClearScreen()
{
	system("CLS");
	printf("\n Screen is cleaning...");
	Sleep(1500);
	system("CLS");
}