#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <algorithm>
#include <list>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::vector;
using std::istream;
using std::ostream;
using std::domain_error;
using std::sort;
using std::list;

typedef list <string> phrase_type ;
typedef phrase_type::size_type sz;

bool compare_phrase(const phrase_type &a, const phrase_type &b) {
  return *a.begin()<*b.begin();
}

istream & read_phrase(istream &in, phrase_type &phrase) {
  string word;
  bool phrase_end = false;
  
  if (in)
    {
      phrase.clear();
      while (!phrase_end && in >> word) {
	phrase.push_back(word);
	if (word[word.size() - 1] == '.')
	  phrase_end = true;
      }
    }
  return in;
}

string format_phrase(const phrase_type &v) {
  string out;
  for (phrase_type::const_iterator i=v.begin() ; i!=v.end(); i++)
    out+=*i + " ";
  return out;
}

phrase_type rotate_phrase(const phrase_type &v, phrase_type::const_iterator pos) {

  phrase_type out(pos, v.end());
  out.insert(out.end(), v.begin(), v.end());
  return out;
}

string::size_type left_width(const phrase_type phrase) {
  string::size_type len = 0;
  phrase_type::const_iterator m = phrase.begin();
  m = m++;
  m = m+1;
  cout << phrase.end() - phrase.begin();
  for (phrase_type::const_iterator i = phrase.begin();
       (phrase.end() -i) != 1 ;i++)
    len += (*i).size()+1;
  return len;
}

string print_rotation(const phrase_type &phrase,
		    const phrase_type &rot,
		    phrase_type::size_type width) {
  string output;
  phrase_type::const_iterator i;

  for ( i = phrase.begin(); *i != *rot.begin(); i++) {
    output += *i + " ";
  }

  output = string(width - output.size(), ' ')  + output + "    ";

  for(phrase_type::const_iterator j = i;
      j != phrase.end(); j++)
    output+=*j + " ";
  
  return output; 
}

int main()
{
  phrase_type phrase;

  cout << "Enter the phrases" << endl;
  while (read_phrase(cin, phrase)) {
    vector <phrase_type > phrase_perm;
    // generate rotations
    for (phase_type::const_iterator i = phrase.begin();
	 i != phrase.end(); i++)
      phrase_perm.push_back(rotate_phrase(phrase, i));
    
    // sort rotations
    sort (phrase_perm.begin(), phrase_perm.end(), compare_phrase);
    
    // compute the width of the left side
    string::size_type width = left_width(phrase);
    
    // print rotations
    for (vector <phrase_type >::const_iterator i = phrase_perm.begin();
	 i!=phrase_perm.end(); i++) {
	cout << print_rotation(phrase, *i, width) << endl;
    }
    
  }
  return 0;
}
