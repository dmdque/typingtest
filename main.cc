#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <termios.h>
using namespace std;

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

int main(){
  int NUMLINES = 4;
  string sentences[] = new string[4]; // NUMLINES // USE VECTORS
  string filename = "input.txt";
  ifstream file;
  file.open(filename.c_str()); // .c_str());

  stringstream ss;

  for (int line = 0; line < NUMLINES; line++){
    getline(file, sentences[line]); // file >> filename; // ss;
  }

  for (int line = 0; line < NUMLINES; line++){
    cout << s.c_str() << endl; // ss.str(); 
    int i = 0;
    char ch;
    do{
      ch = getch();
      if (ch == sentences[line][i]){
        cout << ch ;//  << '\n'; // cout waits for a newline char before printing :(
        cout.flush();
        i++;
      }
      // cout << ss.str();
    } while (i < s.size());
    cout << endl;
  }
}