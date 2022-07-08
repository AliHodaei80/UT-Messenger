#include <stdio.h>/*This program is our last step towards creating a messenger.Hope you enjoy it.*/
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<conio.h>
#include<windows.h>
#include"CA3.h"


void setTextColor(int color) {/*This function is for coloring the text when we want*/
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}

char* input(FILE* stream)/*This function is for getting command line and reading from files*/
{
	char get = '\0';
	int count = ONE;
	char* command = (char*)malloc(sizeof(char));
	char* tmp;
	while (1) {
		get = getc(stream);
		if (get == '\n' || get == ' ' || get == EOF)
			break;
		tmp = (char*)realloc(command, count * sizeof(char));
		if (tmp == NULL)
			exit(EXIT_FAILURE);
		tmp[count - ONE] = get;
		count++;
		command = tmp;
	}
	tmp = (char*)realloc(command, count * sizeof(char));
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	command = tmp;
	command[count - ONE] = '\0';
	return command;
}

char* input_message(FILE* stream) {/*This function is for getting messages and reads from file*/
	char get = '\0';
	int count = ONE;
	char* command = (char*)malloc(sizeof(char));
	char* tmp;
	while (ONE) {
		get = getc(stream);
		if (get == '\n' || get == EOF)
			break;
		tmp = (char*)realloc(command, count * sizeof(char));
		if (tmp == NULL)
			exit(EXIT_FAILURE);
		tmp[count - ONE] = get;
		count++;
		command = tmp;
	}
	tmp = (char*)realloc(command, count * sizeof(char));
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	command = tmp;
	command[count - ONE] = '\0';
	return command;
}

User* newUser() {/*this function is for creating new a user*/
	User* new_user = (User*)malloc(sizeof(User));
	if (new_user == NULL)exit(EXIT_FAILURE);
	new_user->next = NULL;
	new_user->username = NULL;
	new_user->pass = NULL;
	new_user->date_created = NULL;
	new_user->phone = NULL;
	return new_user;
}


User* find_username(User* users, char* username) {/*This function searches in user link list and
												  if the username matches it will return the pointer of that node*/
	while (1) {
		if (users->next == NULL) {
			return NULL;
		}
		if (strcmp(users->username, username) == 0)
			return users;
		users = users->next;
	}
}

User* find_phone_number(User* users, char* phone_number) {/*This function searches in user link list and
												  if the phone number matches it will return the pointer of that node*/
	while (1) {
		if (users->next == NULL) {
			return NULL;
		}
		if (strcmp(users->phone, phone_number) == 0)
			return users;
		users = users->next;
	}
}

User* getLastUser(User* users) {/*this function searches on user link list and return the pointer of last user*/
	while (users->next != NULL)
		users = users->next;
	return users;
}

User* SignUp(User* users) {/*This function signs up the user*/
	char* username = input(stdin);
	char* pass = input(stdin);
	char* phoneNumber = input(stdin);
	int flag = ONE;
	if (find_username(users, username) != NULL) {/*Checks that input username is repetitious or not*/
		printf("Username already exists!\n");
		flag = ZERO;
	}
	if (strlen(phoneNumber) != PHONE_LENGTH) {/*Checks the length of input phone number*/
		printf("The phone number should contain 11 characters!\n");
		flag = ZERO;
	}
	if (find_phone_number(users, phoneNumber) != NULL) {/*Checks that input phone number is repetitious or not*/
		printf("Phone number exists!\n");
		flag = ZERO;
	}
	if (phoneNumber[ZERO] != '0') {
		printf("Phone number should start with 0!\n");
		flag = ZERO;
	}
	for (int i = ZERO; i < (int)strlen(phoneNumber); i++)
		if (phoneNumber[i] > '9' || phoneNumber[i] < '0') {/*Checks that input phone number is all number*/
			printf("Phone number should only contain numbers!\n");
			flag = ZERO;
			break;
		}
	if (strlen(pass) < MIN_PASS_LENGTH) {
		printf("Password should be at least 6 characters long!\n");
		flag = ZERO;
	}
	if (flag == ZERO)
	{
		free(username);
		free(pass);
		free(phoneNumber);
		return NULL;
	}
	printf("Sign Up successful\n");/*Adding new user*/
	User* user = getLastUser(users);
	user->username = username;
	user->phone = phoneNumber;
	time_t curtime;
	time(&curtime);
	char* Time = malloc(MAX_INPUT);
	if (Time == NULL)exit(EXIT_FAILURE);
	ctime_s(Time, MAX_INPUT, &curtime);
	Time[strlen(Time) - ONE] = '\0';
	user->date_created = Time;
	user->pass = pass;
	user->next = newUser();
	return user;
}

User* login(User* users) {/*Checks the username and its password and then lets user login*/
	char* username = input(stdin);
	char* pass = input(stdin);
	User* user = find_username(users, username);
	if (user == NULL) {
		printf("Username not found!\n");
		free(username);
		free(pass);
		return NULL;
	}
	if (strcmp(user->pass, pass) == ZERO) {
		printf("Login Successful\n");
		return user;
	}
	printf("Password is incorrect!\n");
	free(username);
	free(pass);
	return NULL;
}

void Info(User* users) {/*This function prints users' username*/
	if (users->username == NULL) {
		printf("No user signed up yet\n");
		return;
	}
	while (users->next != NULL) {
		printf("%s\n", users->username);
		users = users->next;
	}
}


void OutputInfo(User* user) {/*This function prints the users' username and his phone number*/
	printf("Username : %s\n", user->username);
	printf("Phone number : %s\n", user->phone);
}

Messages* newMessage() {/*This function is for creating new messages*/
	Messages* new_message = (Messages*)malloc(sizeof(Messages));
	if (new_message == NULL)
		exit(EXIT_FAILURE);
	new_message->next = NULL;
	new_message->Message = NULL;
	new_message->read = ZERO;
	new_message->from = NULL;
	new_message->to = NULL;
	new_message->date_sent = NULL;
	return new_message;
}

Messages* lastMessage(Messages* messages) {/*this function پیمایش on message link list and return the pointer of last message*/
	while (messages->next != NULL) {
		messages = messages->next;
	}
	return messages;
}

void add_message(char* from, char* to, char* message, Messages* messages, User* users) {/*this function is for sending messages*/
	if (find_username(users, to) == NULL) {
		printf("User not found!\n");
		free(to);
		return;
	}
	Messages* tmp = lastMessage(messages);
	tmp->next = newMessage();
	tmp->from = from;
	tmp->to = to;
	tmp->Message = message;
	time_t curtime;
	time(&curtime);
	char* Time = malloc(MAX_INPUT);
	if (Time == NULL)exit(EXIT_FAILURE);
	ctime_s(Time, MAX_INPUT, &curtime);
	Time[strlen(Time) - ONE] = '\0';
	tmp->date_sent = Time;
	printf("Message sent successfully.\n");
}

void getUnreadMessages(User* user, Messages* messages) {/*This function checks that if the user has unread messages*/
	while (messages->next != NULL) {
		if (strcmp(messages->to, user->username) == 0 && !messages->read) {
			printf("Unread message from ");
			printf("%s\n", messages->from);
			printf("at : %s\n", messages->date_sent);
		}
		messages = messages->next;
	}
}

void show_received(Messages* messages, char* from, char* to, int received, struct User* users) {/*This function is for showing the messages that users have received*/
	if (find_username(users, from) == NULL) {
		printf("Username not found\n");
		free(from);
		return;
	}
	int flag = ZERO;
	while (messages->next != NULL) {
		if (strcmp(messages->to, to) == ZERO && strcmp(messages->from, from) == ZERO) {
			flag = ONE;
			printf("Message from %s to %s\n", messages->from, messages->to);
			printf("at :  %s\n", messages->date_sent);
			printf("Message : %s\n", messages->Message);
			if (received)
				messages->read = ONE;
		}
		messages = messages->next;
	}
	if (!flag) {
		printf("No messages to show.\n");
	}
}
void show_sent(Messages* messages, char* from, char* to, User* users) {/*This is the main function for showing sent messages and received messages*/
	int flag = ZERO;
	if (find_username(users, to) == NULL) {
		printf("Username not found\n");
		free(to);
		return;
	}
	while (messages->next != NULL) {
		if (strcmp(messages->to, to) == ZERO && strcmp(messages->from, from) == ZERO) {
			flag = ONE;
			if (messages->read == ZERO)
				setTextColor(GREEN);
			printf("Message from %s to %s\n", messages->from, messages->to);
			printf("at :  %s\n", messages->date_sent);
			printf("Message : %s\n", messages->Message);
			setTextColor(WHITE);
		}
		messages = messages->next;
	}
	if (!flag) {
		printf("No messages to show.\n");
	}
}
void saving_on_files(User* users, Messages* messages)/*this function is for saving all users and all messages*/
{
	FILE* message_file, * user_file;
	fopen_s(&user_file, "user.txt", "w+");
	if (user_file == NULL)exit(EXIT_FAILURE);
	fopen_s(&message_file, "message.txt", "w+");
	if (message_file == NULL)exit(EXIT_FAILURE);
	while (messages->next != NULL) {
		fprintf(message_file, "Message:\n");
		fprintf(message_file, "%s\n", messages->from);
		fprintf(message_file, "%s\n", messages->to);
		fprintf(message_file, "%s\n", messages->date_sent);
		fprintf(message_file, "%d\n", messages->read);
		fprintf(message_file, "%s\n", messages->Message);
		messages = messages->next;
	}
	while (users->next != NULL) {
		fprintf_s(user_file, "User:\n");
		fprintf(user_file, "%s\n", users->username);
		fprintf(user_file, "%s\n", users->pass);
		fprintf(user_file, "%s\n", users->phone);
		fprintf(user_file, "%s\n", users->date_created);
		users = users->next;
	}
}
void reading_users(struct User* users)/*This function is for reading from file and saving them on their link list*/
{
	FILE* user_file;
	fopen_s(&user_file, "user.txt", "a+");
	if (user_file == NULL)exit(EXIT_FAILURE);
	fprintf(user_file, "Endoffile\n");/*For checking end of file*/
	fclose(user_file);
	fopen_s(&user_file, "user.txt", "r");
	if (user_file == NULL)exit(EXIT_FAILURE);
	while (ONE) {
		char* hp = input(user_file);
		if (strcmp("Endoffile", hp) == ZERO)
			break;
		User* tmp = getLastUser(users);
		tmp->next = newUser();
		tmp->username = input(user_file);
		tmp->pass = input(user_file);
		tmp->phone = input(user_file);
		tmp->date_created = input_message(user_file);
	}
	fclose(user_file);
}
void reading_messages(struct Messages* messages)/*This function is for reading from file and saving them on their link list*/
{
	FILE* message_file;
	fopen_s(&message_file, "message.txt", "a+");
	if (message_file == NULL)exit(EXIT_FAILURE);
	fprintf(message_file, "Endoffile\n");/*For checking end of file*/
	fclose(message_file);
	fopen_s(&message_file, "message.txt", "r");
	if (message_file == NULL)exit(EXIT_FAILURE);
	while (1) {
		char* string = input(message_file);
		char ch;
		if (strcmp(string, "Endoffile") == ZERO)
			break;
		Messages* messages1 = lastMessage(messages);
		messages1->from = input(message_file);
		messages1->to = input(message_file);
		messages1->date_sent = input_message(message_file);
		if (getc(message_file) == '1')
			messages1->read = 1;
		ch = getc(message_file);
		messages1->Message = input_message(message_file);
		messages1->next = newMessage();
	}
	fclose(message_file);
}
void about(User* users, char* username)/*This function print users' information*/
{
	if (find_username(users, username) == NULL) {
		printf("Username not found\n");
	}
	else {
		OutputInfo(find_username(users, username));
	}

}
void edit_pass(User* logged_in_user, char* pass)/*This function is for editing password*/
{
	if (strlen(pass) < MIN_PASS_LENGTH) {
		printf("password should be at least 6 characters long\n");
		free(pass);
	}
	else {
		if (strcmp(logged_in_user->pass, pass) == ZERO) {
			printf("This password is the same as last one\n");
			free(pass);
		}
		else {
			free(logged_in_user->pass);
			logged_in_user->pass = pass;
			printf("Password changed!\n");
		}
	}
}
void edit_username(User* users, User* logged_in_user, char* username, Messages* messages)/*This function is for editing username*/
{
	if (strcmp(logged_in_user->username, username) == ZERO) {
		printf("This username is the same as last one\n");
		free(username);
	}
	else if (find_username(users, username) != NULL) {
		printf("Username already exists!\n");
		free(username);
	}
	else {
		printf("Username Changed\n");
		while (messages->next != NULL)
		{
			if (strcmp(messages->to, logged_in_user->username) == ZERO)/*Changing the messages to*/
				messages->to = username;
			if (strcmp(messages->from, logged_in_user->username) == ZERO)/*Changing the messages from*/
				messages->from = username;
			messages = messages->next;
		}
		free(logged_in_user->username);
		logged_in_user->username = username;
	}
}
void FreeU(User* users)/*This function is for freeing our users link list beacause we get them from heap*/
{
	if (users == NULL)
	{
		return;
	}
	FreeU(users->next);

	free(users->username);
	free(users->pass);
	free(users->phone);
	free(users->date_created);
	free(users);
}
void FreeM(Messages* messages)/*This function is for freeing our messages link list beacause we get them from heap*/
{
	if (messages == NULL)
	{
		return;
	}
	FreeM(messages->next);

	free(messages->date_sent);
	free(messages->Message);
	free(messages);
}

int main() {
	User* users = newUser();
	User* logged_in_user = NULL;
	Messages* messages = newMessage();
	reading_users(users);
	reading_messages(messages);
	char ignore = '\0';/*This variable is for clearing buffer*/
	printf("Welcome to UT messenger.\n");
	while (ONE) {
		//ignore = '\0';
		printf(">> ");
		char* option = input(stdin);/*We get the order here and after that compare it*/
		if (strcmp(option, "close") == ZERO)
			break;
		else if (strcmp(option, "login") == ZERO) {
			if (logged_in_user != NULL) {/*Check that user is logged in or not*/
				printf("You are logged in. Please logout first\n");
				while (ignore != '\n')
					ignore = getchar();
			}
			else {
				logged_in_user = login(users);
				getUnreadMessages(logged_in_user, messages);
			}
			free(option);
		}
		else if (strcmp(option, "signup") == ZERO) {
			if (logged_in_user != NULL) {
				while (ignore != '\n')
					ignore = getchar();
				printf("Please logout first to signup\n");
			}
			else {
				logged_in_user = SignUp(users);
			}
			free(option);
		}
		else if (strcmp(option, "logout") == ZERO) {
			if (logged_in_user == NULL) {
				printf("You are not logged in to logout\n");
			}
			else {
				printf("Log out successful\n");
				logged_in_user = NULL;
				free(option);
			}
		}
		else if (strcmp(option, "edit_username") == ZERO) {
			char* username = input(stdin);
			if (logged_in_user == NULL) {
				printf("You are not signed in to change username\n");
			}
			edit_username(users, logged_in_user, username, messages);
			free(option);
		}
		else if (strcmp(option, "edit_pass") == ZERO) {
			char* pass = input(stdin);
			if (logged_in_user == NULL) {
				printf("You are not signed in to change password\n");
			}
			else
				edit_pass(logged_in_user, pass);
			free(option);
		}
		else if (strcmp(option, "info") == ZERO) {
			Info(users);
			free(option);
		}
		else if (strcmp(option, "about") == ZERO) {
			char* username = input(stdin);
			if (logged_in_user == NULL) {
				printf("Please login to use about<username>\n");
				free(username);
			}
			else
				about(users, username);
			free(option);
		}
		else if (strcmp(option, "send") == ZERO) {
			char* username = input(stdin);
			char* message = input_message(stdin);
			if (logged_in_user == NULL) {
				printf("Please login to use send message\n");
				free(username);
				free(message);
			}
			else {
				add_message(logged_in_user->username, username, message, messages, users);
			}
			free(option);
		}
		else if (strcmp(option, "show_received") == ZERO) {
			char* username = input(stdin);
			if (logged_in_user == NULL) {
				printf("Please login to see received messages\n");
				free(username);
			}
			else {
				show_received(messages, username, logged_in_user->username, 1, users);
			}
			free(option);
		}
		else if (strcmp(option, "show_sent") == ZERO) {
			char* username = input(stdin);
			if (logged_in_user == NULL) {
				printf("Please login to see received messages\n");
				free(username);
			}
			else {
				show_sent(messages, logged_in_user->username, username, users);
			}
			free(option);
		}
		else {
			printf("Invalid command\n");
			while (ignore != '\n')
				ignore = getchar();
			free(option);
		}
	}
	saving_on_files(users, messages);
	FreeM(messages);
	FreeU(users);
	return 0;
}
