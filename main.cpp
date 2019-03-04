/*
Sam Hopkins, Section 3, sam.hopkins@blastsoccer.net

 
TEST CASES:
 in1: testing with simple union
 in2: testing with a simple join
 in3: testing a reflexive rule
 in4: testing a symmetric rule
 in5: testing join with multpile predicates
 in6: testing with multiple relations and multiple joins
 in7: testing with transitive rules
 in8: testing with symtransitive rule
 in9: testing multiple iteration
 in10: testing with combined test cases

 */
                                
#include <iostream>
#include <fstream>
#include <string>
#include "Lex.h"
#include "DatalogProgram.h"
#include "ValidityChecker.h"
#include "Database.h"
using namespace std;



int main(int argc, const char * argv[]) {
    int const ERROR_BY_ONE = 1;
    string totalFile;
    ostringstream filename;
    ifstream in(argv[1]);
    
    while (!in.eof()){
        std::string line;
        getline(in, line);
        totalFile = totalFile + line;
        totalFile = totalFile + '\n';
    }
    totalFile = totalFile.substr(0, (totalFile.length() - ERROR_BY_ONE));
    Lex lexAnalyzer(totalFile);
    lexAnalyzer.StartState();
    try {
        ValidityChecker InputParser(lexAnalyzer.tokenList);
        InputParser.BigParser();
        DataLog DLP(lexAnalyzer.tokenList);
      //  cout << DLP.ToString() << endl;
        Database Db;
        Db.CreateDatabase(DLP.GetSchemes(), DLP.GetFacts(), DLP.GetQueries(), DLP.GetRules());
        Db.Optimization();
       // Db.EvaluateRules();
        cout << "Query Evaluation" << endl;
        Db.EvaluateQueries();
    } catch (string x) {
        cout << "Failure!" << endl;
        cout << "  " << x;
    }

    return 0;
}

