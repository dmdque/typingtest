#include <iostream>
#include <cstdlib>
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
  return wpm;
}

int main(int argc, char **argv){
  int DEBUG = 0;
  int RANDOMIZE = 0;
  // getopt stuff
  // opterr = 0;
  int c;
  string filename; // = "input.txt";
  while ((c = getopt(argc, argv, "drf:")) != -1){
    if (c == 'd'){
      DEBUG = 1;
    }
    else if (c == 'r'){
      RANDOMIZE = 1;
    }
    else if (c == 'f'){
      filename = optarg;
    }
  }

  vector<string> sentences;

  if (filename == ""){
    cout << "Specify an input file: ";
    cin >> filename;
  }

  ifstream file;
  file.open(filename.c_str()); // .c_str());
  stringstream ss;

  // building the sentences vector
  cout << "Loading file " << filename << "... ";
  for(int line = 0; true; line++){
    string s;
    getline(file, s); // file >> filename; // ss;
    if (file.eof()){ break;}
    /*
    try{
      getline(file, s);
    } catch (ios_base::failure e) {
      cout << "fail" << endl;
      break;
    }
    */
    sentences.push_back(s);
  }
  cout << "File successfully loaded." << endl;

  vector<int> sentence_order;
  for (unsigned int i = 0; i < sentences.size(); i++){
    sentence_order.push_back(i);
  }
  if (RANDOMIZE){
    srand(time(NULL));
    if (DEBUG){ cout << "RANDOMIZE!" << endl;}
    for (unsigned int i = 0; i < sentences.size(); i++){
      int r = rand() % sentences.size();
      int temp = sentence_order[i];
      sentence_order[i] = sentence_order[r];
      sentence_order[r] = temp;
    }
  }
  if (DEBUG){
    for (unsigned int i = 0; i < sentences.size(); i++){
      if (i != 0){
        cout << ", ";
      }
      cout << sentence_order[i];
    }
    cout << "\n";
  }
  // actual meat
  time_t t1, t2;
  for (unsigned int si = 0; si < sentences.size(); si++){ // si = sentence iterator
    int line = sentence_order[si];
    if (sentences[line].size() == 0){ // empty line!
      // cout << "surpressed an empty line" << endl;
      continue;
    }
    cout << "\x1b[0;33m" << sentences[line].c_str() << "\x1b[0m" << endl; // ss.str(); // i think c_str() is optional
    unsigned int i = 0; // character iterator
    char ch;
    while (i < sentences[line].size()){
      ch = getch();
      if (i == 0){
        time(&t1); // first character // alt: t1 = time(NULL);
      }
      if (ch == sentences[line][i]){ // correct character has been typed
        cout << "\x1b[0;32m" << ch << "\x1b[0m";
        cout.flush();
        i++;
      } else if (ch == 127){ // BACKSPACE/DEL
        cout << "\x1b[0;36m" << sentences[line][i] << "\x1b[0m";
        cout.flush();
        i++;
      } else if (ch == 27){ // ESC/DEL
      // (ch == 9 || ch == 11 || ch == '\t' || ch == '\v' || ch == '\n' || ch == 92 || ch == '\\' || ch == 27)
          // line++;
          // goto end_loop;
          break;
      } else if (ch == 9){ // horizontal TAB
        if (' ' == sentences[line][i]){
          if (' ' == sentences[line][i+1]){ // **error check this for EOF
            cout << " ";
            cout.flush();
            i++;
          }
          cout << " ";
          cout.flush();
          i++;
          // continue;
        }
      }
      // cout << ss.str();
    }
    time(&t2);
    cout << endl;
    double dt = difftime(t2, t1);
    double wpm = calc_wpm(dt, sentences[line]);
    cout << "Your wpm was: " << wpm << endl;
    cout << "You took " << dt << " seconds to complete this line." << endl;
    // end_loop:
    // cout << "\x1b[0m" << endl;
  }
}
