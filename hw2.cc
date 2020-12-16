#include <iostream>
#include <vector>

using namespace std;

void outPut(int decNum, int numFmt);
int calculate(vector<int> nums, int op);
int calcHelp(int num1, int num2, int op);
int isOperator(string op);
int isNumFmt(string op);
vector<int> convrt(vector<string> vex, int start);
int digOrOct(string num);
int hexOrBin(string num);

string prgnm;

int main(int argc, char *argv[]) {
	//INITIAL DECLARATION OF VARIABLES
	prgnm = argv[0];
	vector<string> str;
	vector<int> numnum;
	int numFmt, op, vectSt, finNum;
	vectSt = 2;
	//CHECK TO SEE IF ENOUGH ARGUMENTS ARE PROVIDED TO PERFORM A FUNCTION
	if(argc < 3){
	 	cerr << prgnm << " ERROR: Not Enough Arguments\n";
		exit(1);	
	}
	//LOAD ALL THE ARGUMENTS INTO A VECTOR FOR LATER MANIPULATION
	for(int i = 1; i < argc; i++){
		str.push_back(argv[i]);
	}
	//SET OPERATORS
	numFmt = isNumFmt(str[0]);
	op = isOperator(str[1]);
	//CHECK FOR VALID OPERATORS
	if(numFmt == 0){
		if(op == 0 && isOperator(str[0]) && isNumFmt(str[1]) == 0){
			op = isOperator(str[0]);
			numFmt = 1;
			vectSt= 1;
		}else{
			cerr << prgnm << " ERROR: Invalid Formating - Operator or Base Format\n";
			exit(1);
		}
	}
	// If First if is past then there is a valid number formate present we then check for a valid operator
	if(op == 0){
		cerr << prgnm << " ERROR: Invalid Formating - Operator Not Detected or Invalid Form of Operator\n";
                exit(1);	
	}
	
	// Checking to make sure there is enougn values to perform and operation
	if(vectSt == int(str.size())){
		cerr << prgnm << " ERROR: No Values Detected\n";
                exit(1);	
	}
	// convrt takes the strings anc converts them in to integers that will later be used for calculating 	
	numnum = convrt(str, vectSt);
	// calculate takes a vecter of int and the operation to perform and computs the end value in decimal format
	finNum = calculate(numnum, op);
	// outPut takes the final decimal and converts it in the specified number format and adjusts for a negative
	outPut(finNum, numFmt);

        return 0;
}

void outPut(int decNum, int numFmt){
	if(decNum < 0){
		decNum *= -1;
		cout << '-';
	}
	switch(numFmt){
		case 1:
			cout << decNum << '\n';
			break;
		case 2:
			cout << hex << decNum << '\n';
			break;
		case 3:
			cout << oct << decNum << '\n';
			break;
		default:
			cerr << prgnm << " ERROR: UNDEFINED BEHAVIOR\n";
			exit(1);
	}
	
}
//CALCULATES THE VALUE OF USING OPERANDS IN VECTOR AND PROVIDED OPERATOR
int calculate(vector<int> nums, int op){
	int deciAnsw = nums[0];
	
	for(int i = 1; i < int(nums.size()); i++){
		deciAnsw = calcHelp(deciAnsw, nums[i], op);
	}
	return deciAnsw;
}
// HELPER FUCNTION FOR CALC 
int calcHelp(int num1, int num2, int op){
	switch(op){
		case 1:
			return num1 + num2;
		case 2:
			return num1 - num2;
		case 3:
			return num1 * num2;
		case 4: 
			if(num2 == 0){ //DIVISION BY ZERO CHECK
				cerr << prgnm << " ERROR: DIVISION BY ZERO\n";
                		exit(1);	
			}
			return num1 / num2;
		case 5:
			int distNum1, distNum2;
        		if(num1 <= 45){distNum1 = 45 - num1;}
        		if(num1 > 45){distNum1 = num1 - 45;}
        		if(num2 <= 45){distNum2 = 45 - num2;}
        		if(num2 > 45){distNum2 = num2 - 45;}
        		if(distNum2 == distNum1){
            			if(num1 > num2){return num2;}
				if(num1 < num2){return num1;}
                		return num1;
        		}
			if(distNum1 > distNum2){return num1;}
			if(distNum2 > distNum1){return num2;}
			return 0;
		default:
			return 0;
	}
}
int isOperator(string op){
	if(op.compare("+") == 0){return 1;}
	if(op.compare("-") == 0){return 2;}
        if(op.compare("*") == 0){return 3;}
        if(op.compare("/") == 0){return 4;}
        if(op.compare("@") == 0){return 5;}
        return 0;
}
int isNumFmt(string op){
	if(op.compare("-d") == 0){return 1;}
	if(op.compare("-h") == 0){return 2;}	
	if(op.compare("-o") == 0){return 3;}
	return 0;
}
vector<int> convrt(vector<string> vex, int start){
	vector<int> vox;
	string curr;
	int curNum;
	for(int i = start; i < int(vex.size()); i++ ){
		curr = vex[i];
                if(!(isdigit(curr[0])) || curr.size() == 0){
			cerr << prgnm << " ERROR: Invalid Formating Detected in the value entered at position " << i+1-start << " of the "<<int(vex.size())-start<<" values entered\n";
                	exit(1);	
		}
		if(isdigit(curr[1]) || curr.size() < 3){
			curNum = digOrOct(curr);		
		}else if(curr[1] == 'x' || curr[1] == 'b'){
			curNum = hexOrBin(curr);
		}else{
			cerr << prgnm << " ERROR: Invalid Formating Detected in the value entered at position " << i+1-start << " of the "<<int(vex.size())-1<<" values entered\n";
                        exit(1);	
		}
		if(curNum < 0){
			cerr << prgnm << " ERROR: Invalid Formating Detected in the value entered at position " << i+1-start << " of the "<<int(vex.size())-1<<" values entered\n";
                        exit(1);	
		}
		vox.push_back(curNum);
	}
	return vox;
}
int hexOrBin(string num){
	int value;
	if(num[1] == 'x'){
		for(int i = 2; i < int(num.size()); i++){
			if(!(isdigit(num[i]) || (num[i] >= 'a' && num[i] <= 'f'))){
				return -1;	
			}
		}
		try{
                        value = stoi(num, nullptr, 16);
                }catch(const exception& e){
                        return -1;
                }
		return value;
	}
	if(num[1] == 'b'){
		for(int i = 2; i < int(num.size()); i++){
			if(!(num[i] >= '0' && num[i] <= '1')){
				return -1;
			}
                }
		try{
                	value = stoi(num.substr(2), nullptr, 2);
                }catch(const exception& e){
                       	return -1;
                }
		return value;	
	}
	return -1;
}
int digOrOct(string num){
	int value = 0;
	char c = 'd';
	if(num[0] == '0'){
		c = 'o';
	}
	for(int i = 0; i < int(num.size()); i++){
		if(!(isdigit(num[i]))){
			return -1;
		}
		if(num[i] > '7'){
			c = 'd';
		}
        }
	if(c == 'd'){
		try{
			value = stoi(num);
		}catch(const std::exception& e){
			return -1;
		}
	}

	if(c == 'o'){
		try{
			value = stoi(num, nullptr, 8);
		}catch(const std::exception& e){
			return -1;
		}
	}
	return value;
}
