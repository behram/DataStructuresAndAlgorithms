#include<iostream>
#include<string.h>

using namespace std;

struct Element{
	int key;
	int value;
};

struct ElementLL{
	Element elem;
	ElementLL *next, *prev;
};

struct List2W{
	ElementLL *sentinel;
};

void init(List2W& l){
	l.sentinel = new ElementLL;
	ElementLL *sent = l.sentinel;
	sent->next = sent;
	sent->prev = sent;
}

void insertElem(List2W & l, Element elem){
	ElementLL *sent = l.sentinel;
	ElementLL *fresh = new ElementLL;
	ElementLL *search = l.sentinel->next;
	fresh->elem.key = elem.key;
	fresh->elem.value = elem.value;

	if (sent->next == sent)
	{
		fresh->next = sent;
		fresh->prev = sent;
		sent->next = fresh;
		sent->prev = fresh;
	}
	else
	{
		while (search->elem.key <= fresh->elem.key && search != sent)

			search=search->next;

		fresh->next = search;
		fresh->prev = search->prev;
		fresh->next->prev = fresh;
		fresh->prev->next = fresh;
	}
}

bool findKey(List2W & l,int key, Element &elem){
	ElementLL *search = l.sentinel->next;
	ElementLL *sent = l.sentinel;
	while(search != sent)
	{
		if (search->elem.key == key)
		{
			elem = search->elem;
			return true;
		}
		search=search->next;
	}
	return false;
}

void removeAllKeys(List2W& l, int key){
	ElementLL *search = l.sentinel->next;
	ElementLL *sent = l.sentinel;
	ElementLL *temp;
	while(search != sent)
	{
		if (search->elem.key == key)
		{
			temp = search;
			search=search->next;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			continue;
		}
		search=search->next;
	}
}

void showListFromHead(List2W& l){
	ElementLL *search = l.sentinel->next;
	ElementLL *sent = l.sentinel;
	while(search != sent)
	{
		cout<<search->elem.key<<"("<<search->elem.value<<"),";
		search=search->next;
	}
	cout<<endl;
}

void showListFromTail(List2W& l){
	ElementLL *search = l.sentinel->prev;
	ElementLL *sent = l.sentinel;
	while(search != sent)
	{
		cout<<search->elem.key<<"("<<search->elem.value<<"),";
		search=search->prev;
	}
	cout<<endl;
}

void clearList(List2W& l){
	ElementLL *search = l.sentinel->next;
	ElementLL *sent = l.sentinel;
	ElementLL *temp;
	while(search != sent)
	{
		temp = search;
		search=search->next;
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
	}
}

void addList(List2W& l1,List2W& l2){
	if (l1.sentinel != l2.sentinel && l2.sentinel != l2.sentinel->next)
	{
		ElementLL *search1 = l1.sentinel->next;
		ElementLL *sent1 = l1.sentinel;
		ElementLL *search2 = l2.sentinel->next;
		ElementLL *sent2 = l2.sentinel;
		ElementLL *temp;
		if (sent1 == sent1->next)
		{

			sent1->next=sent2->next;
			sent1->prev=sent2->prev;
			sent1->next->prev=sent1;
			sent1->prev->next=sent1;
			sent2->next=sent2;
			sent2->prev=sent2;
		}
		else
		{
			while (search2 != sent2)
			{
				temp = search2;
				search2=search2->next;

				while (temp->elem.key >= search1->elem.key && search1 != sent1)

					search1=search1->next;

				temp->next = search1;
				temp->prev = search1->prev;
				temp->next->prev = temp;
				temp->prev->next = temp;

			}


			sent2->next = sent2;
			sent2->prev = sent2;
		}
	}
}

void showBool(bool val){
	if(val)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

int main(){
	const int commandSize=2;
	const int MAXLINE=100;
	char line[MAXLINE];
	char command[commandSize+1];
	List2W *list;
	list=new List2W[1];
	int currentL=0;
	int value;
	command[commandSize]='\0';
	while(true){
		cin >> command[0];
		if(command[0]=='#')
		{
			cin.getline(line, MAXLINE);
			continue;
		}
		cin >> command[1];

		if(strcmp(command,"HA")==0){
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if(strcmp(command,"ST")==0)
		{
			showListFromTail(list[currentL]);
			continue;
		}

		if(strcmp(command,"SH")==0)
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if(strcmp(command,"CL")==0)
		{
			clearList(list[currentL]);
			continue;
		}

		if(strcmp(command,"IN")==0)
		{
			init(list[currentL]);
			continue;
		}


		cin >> value;

		if(strcmp(command,"FK")==0)
		{
			Element elem;
			bool ret=findKey(list[currentL], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if(strcmp(command,"RK")==0)
		{
			removeAllKeys(list[currentL],value);
			continue;
		}


		if(strcmp(command,"CH")==0)
		{
			currentL=value;
			continue;
		}

		if(strcmp(command,"IE")==0)
		{
			int variable2;
			cin >> variable2;
			Element elem;
			elem.key=value;
			elem.value=variable2;
			insertElem(list[currentL],elem);
			continue;
		}

		if(strcmp(command,"GO")==0)
		{
			list=new List2W[value];
			continue;
		}

		if(strcmp(command,"AD")==0)
		{
			addList(list[currentL],list[value]);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
		return 1;
	}
}
