#define MAX_INPUT 100
#define PHONE_LENGTH 11
#define ZERO 0
#define ONE 1
#define MIN_PASS_LENGTH 6
#define GREEN 2
#define WHITE 7
typedef struct User User;
typedef struct Messages Messages;

struct Messages {
	Messages* next;
	char* Message;
	char* from, * to;
	int read;
	char* date_sent;
};

struct User {
	User* next;
	char* username;
	char* pass;
	char* phone;
	char* date_created;
};


void setTextColor(int color);
char* input(FILE* stream);
char* input_message(FILE* stream);
User* newUser();
Messages* newMessage();
User* find_username(User* users, char* username);
User* find_phone_number(User* users, char* phone_number);
User* getLastUser(User* users);
Messages* lastMessage(Messages* messages);
User* SignUp(User* users);
User* login(User* users);
void Info(User* users);
void OutputInfo(User* user);
void add_message(char* from, char* to, char* message, Messages* messages, User* users);
void getUnreadMessages(User* user, Messages* messages);
void show_received(Messages* messages, char* from, char* to, int received, struct User* users);
void show_sent(Messages* messages, char* from, char* to, User* users);
void about(User* users, char* username);
void edit_pass(User* logged_in_user, char* pass);
void edit_username(User* users, User* logged_in_user, char* username, Messages* messages);
void saving_on_files(User* users, Messages* messages);
void reading_users(struct User* users);
void reading_messages(struct Messages* messages);
void FreeU(User* users);
void FreeM(Messages* messages);
