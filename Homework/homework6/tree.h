#define MAX 50 //Maximum length of input.

typedef struct treenode{
	char* username;		//Username.
	char* password;		//Password.
	unsigned int depth;
	struct treenode* leftChild;
	struct treenode* rightChild;
}node;

int getLine();                                              /*Stores input line*/
void getUserInfo(char l[MAX], char p[MAX], char u[MAX]);    /*Gets user info from line*/
void erase(node* pos, char* u, char* p, int* n);            /*Erases user info*/
void alpha(node* pos);                                      /*Prints usernames alphabetically*/
void seeAll(node* pos);                                     /*Prints usernames and passwords*/
node* insert(char* u, char* p, node* pos, int d);           /*Inserts info in a node*/