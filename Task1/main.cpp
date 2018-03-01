#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int i,j,k,b,s;
void lineChars(int size, char * character) {
    for(i = 0; i < size; i++)
    {
        cout << character;
    }
}
void drawTriangle(int size){
    for(i = 1; i <= size; i++){
            lineChars(i, "X");
      cout << "\n";
    }
}

void drawSquare(int size){
    lineChars(size, "X");
    cout << "\n";
    for(b = 2; b < size; b++){
        lineChars(1, "X");
        lineChars(size-2, " ");
        lineChars(1, "X");
        cout << "\n";

    }
    lineChars(size, "X");
    cout << "\n";
}

void drawPyramidwithspaces(int size, int spacecount){
    for(j = 1; j <= size; j++){
        lineChars(size-j+ spacecount, " ");
        lineChars(j*2-1, "X");
        cout << "\n";
    }
}

void drawPyramid(int size){
    drawPyramidwithspaces(size, 0);
}

void drawChristmasTree(int size){
    for(k = 1; k <= size; k++){
        drawPyramidwithspaces(k, size-k);
    }
}

void drawCross(int size){
    for(s = 1; s <= size; s++){
        lineChars(size, " ");
        lineChars(1, "X");
        cout << "\n";
    }
    lineChars(size*2+1, "X");
    cout << "\n";
    for(s = 1; s <= size; s++){
        lineChars(size, " ");
        lineChars(1, "X");
        cout << "\n";
    }
}

void drawPa(int size){
    lineChars(size, "X");
    cout << "\n";
    for(b = 2; b < size; b++){
        lineChars(b-1, " ");
        lineChars(1, "X");
        lineChars(size-2, " ");
        lineChars(1, "X");
        cout << "\n";

    }
    lineChars(size-1, " ");
    lineChars(size, "X");
    cout << "\n";
}

void drawFigureX(int size){
}

void drawFigureY(int size){
}

void drawFigureZ(int size){
}

void drawFigureW(int size){
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line;
	string command;
	int value;
	cout << "START" << endl;
	while(true){
//		cin.getline(line, MAXLINE);
		getline(cin,line);
		std::stringstream stream(line);
		stream >> command;
		if(line=="" || command[0]=='#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0]=toupper(command[0]);
		command[1]=toupper(command[1]);

		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"TR"))
		{
			drawTriangle(value);
			continue;
		}
		if(isCommand(command,"SQ"))
		{
			drawSquare(value);
			continue;
		}
		if(isCommand(command,"PY"))
		{
			drawPyramid(value);
			continue;
		}
		if(isCommand(command,"CT"))
		{
			drawChristmasTree(value);
			continue;
		}
		if(isCommand(command,"FX"))
		{
			drawFigureX(value);
			continue;
		}
		if(isCommand(command,"FY"))
		{
			drawFigureY(value);
			continue;
		}
		if(isCommand(command,"FZ"))
		{
			drawFigureZ(value);
			continue;
		}
		if(isCommand(command,"FW"))
		{
			drawFigureW(value);
			continue;
		}
		if(isCommand(command,"CR"))
		{
			drawCross(value);
			continue;
		}
		if(isCommand(command,"PA"))
		{
			drawPa(value);
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}

}
