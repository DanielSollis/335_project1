///////////////////////////////////////////////////////////////////////////////
// experiment.cc
//
// Example code showing how to run an algorithm once and measure its elapsed
// time precisely. You should modify this program to gather all of your
// experimental data.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "project1.hh"
#include "timer.hh"

using namespace std;

int main() {

  string_vector all_words;
  if ( ! load_words(all_words, "words.txt") ) {
    cerr << "error: cannot open \"words.txt\"" << endl;
    return 1;
  }

  int n = 5000;
  string_vector n_words(all_words.begin(), all_words.begin() + n);
  Timer timer;
  auto output = longest_mirrored_string(n_words);
  double elapsed = timer.elapsed();
  cout << "longest_mirrored_string, "
       << "n=" << n << ", "
       << "output=\"" << output << "\", "
       << "elapsed time=" << elapsed << " seconds" << endl;

  return 0;
}
