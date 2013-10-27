#include <iostream>
#include <string>
#include <vector>
#include <ctime>
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

double calc_wpm(double t, string in_s){
  double wpm = (in_s.size() * 60) / (5 * t); // order of operations changed to preserve accuracy
  // double wpm = (in_s.size() / 5) / (t / 60);
  return wpm;
}

int main(){
  int NUMLINES = 4;
  vector<string> sentences;

  // string sentences[] = new string[4]; // NUMLINES // USE VECTORS
  string filename = "input.txt";
  ifstream file;
  file.open(filename.c_str()); // .c_str());

  stringstream ss;

  // building the sentences vector
  for (int line = 0; line < NUMLINES; line++){
    string s;
    getline(file, s); // file >> filename; // ss;
    sentences.push_back(s);
  }

  // actual meat
  time_t t1, t2;
  for (int line = 0; line < NUMLINES; line++){
    cout << sentences[line].c_str() << endl; // ss.str(); // i think c_str() is optional
    int i = 0;
    char ch;
    time(&t1); // alt: t1 = time(NULL);
    do{
      ch = getch();
      if (ch == sentences[line][i]){
        cout << ch ;//  << '\n'; // cout waits for a newline char before printing :(
        cout.flush();
        i++;
      }
      // cout << ss.str();
    } while (i < sentences[line].size());
    time(&t2);
    cout << endl;
    double dt = difftime(t2, t1);
    double wpm = calc_wpm(dt, sentences[line]);
    cout << "Your wpm was: " << wpm << endl;
    cout << "You took " << dt;
    cout << " seconds to complete this line." << endl;
  }
}
