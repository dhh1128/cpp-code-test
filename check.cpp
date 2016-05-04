#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/*
 * INSTRUCTIONS
 *
 * This module builds a simple cmdline program that tells whether words/phrases
 * match certain criteria. It uses C++11 constructs, but nothing overly
 * mysterious; reasonable familiarity with STL will probably be enough to
 * make you comfortable. You will be extending and debugging the program.
 *
 * 1. Read and understand the basics of the program. Don't worry too much
 *    about style; focus on what work gets done, and how.
 * 2. Extend the program so it can test for palindromes (words/phrases that are
 *    the same written forward and backward, like "noon" or "a toyotas a toyota").
 * 3. Bonus: can you find a latent bug in VowelHeavy::matches_def?
 * 4. Bonus: can you find a latent bug in FirstConsonant::matches_def?
 * 5. Bonus: can you find a bug with security ramifications in main()?
 * 6. Come up with a list of unit tests for specializations of Test. Think of
 *    ones that would catch the bugs you've found, as well as others that might
 *    be useful.
*/


/// A Test decides whether a string matches the definition of a
/// an interesting category. For example, a Test might tell you if
/// a string is a noun, a palindrome, longer than 10 letters, etc.
class Test {
public:
	virtual bool matches_def(const string &) const = 0;
	virtual const char * get_name() const = 0;
};

typedef unique_ptr<Test> TestHandle;
typedef vector<TestHandle> Tests;


static bool is_vowel(char c) {
	return strchr("aeiouAEIOU", c) != nullptr;
}


static bool is_consonant(char c) {
	return strchr("bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ", c) != nullptr;
}


// Does a string have more vowels than consonants?
class VowelHeavy: public Test {
public:
	virtual bool matches_def(const string & x) const {
		auto vowel_count = 0u;
		auto consonant_count = 0u;
		for (auto c: x) {
			if (is_vowel(c)) {
				++vowel_count;
			} else if (is_consonant(c)) {
				++consonant_count;
			}
		}
		return vowel_count / (float)consonant_count > 1.0;
	}
	virtual const char * get_name() const { return "vowelheavy"; }
};


// Does a string begin with a consonant?
class FirstConsonant: public Test {
public:
	virtual bool matches_def(const string & x) const {
		return !x.empty() && !is_vowel(x[0]);
	}
	virtual const char * get_name() const { return "firstcons"; }
};


// Show usage for the program
static void show_help(const Tests & tests) {
	cout << "check ";
	int i = 0;
	for (auto & test: tests) {
		if (i++ > 0) {
			cout << '|';
		}
		cout << test->get_name();
	}
	cout << " word" << endl;
}


int main(int argc, char ** argv) {
	Tests tests;
	tests.push_back(TestHandle(new VowelHeavy()));
	tests.push_back(TestHandle(new FirstConsonant()));
	if (argc < 3) {
		show_help(tests);
		return 1;
	}
	auto selected_test = argv[1];
	auto word = argv[2];
	for (auto & test: tests) {
		if (strcmp(selected_test, test->get_name()) == 0) {
			cout << (test->matches_def(word) ? "yes" : "no") << endl;
			return 0;
		}
	}
	cout << "Huh?" << endl;
	return 1;
}

