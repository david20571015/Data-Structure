//
// main.cpp
// ds_hw2_array_gcd
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include "GCD.h"
using namespace std;

GCD Gcd;
bool LineParser(ifstream &fin, long *input, int *deg);

int main(int argc, char** argv){
	clock_t t_cpu_start, t_use_start;
	double t_use=0;
 	t_cpu_start=clock();
	
	//input file
	ifstream fin;
	fin.open("example", ios::in);
	if(!fin){
		cout << "Where is the pattern file given by TA ?????" << endl;
		exit(-1);
	}//input file
	
	bool check;
	int total_num=0, correct_num=0, i;
	long *out;
	long *in1 = new long [ARRAY_MAX];
	long *in2 = new long [ARRAY_MAX];
	long *ans = new long [ARRAY_MAX];
	int deg1, deg2, deg;

	while(LineParser(fin, in1, &deg1) && LineParser(fin, in2, &deg2) && LineParser(fin, ans, &deg)){
		total_num++;
		t_use_start = clock();
		//your code
		out = Gcd.FindGCD(in1, in2, deg1, deg2);
		//end of your code
		t_use += clock()-t_use_start;
		
		//check
		check=1;
		for(i=0;i<ARRAY_MAX;i++){ if(out[i]!=ans[i]){ check=0; break; } }
		if( check ){ correct_num++; }
		
		if( out!=in1 && out!=in2 ){ delete [] out; }//delete out if you allocate new memory to out
	}
	
	delete [] in1, in2, ans;
	fin.close();
	cout<<"Total CPU time : "<<double(clock()-t_cpu_start)/CLOCKS_PER_SEC<<" seconds"<<endl;
	cout<<"Your performance : "<<double (t_use/CLOCKS_PER_SEC)<<" seconds"<<endl;
    cout<<"Total pass : "<<double (correct_num*100)/total_num<<" percentages of cases"<<endl;
    return 0;
}


bool LineParser(ifstream &fin, long *input, int *degree){
	int a, b, i, op_pre=0, x_post, temp, len, size_str;
	for(i=0;i<ARRAY_MAX;i++){ input[i] = 0; }//reset
	
	string in_str;
	if( !getline(fin, in_str) ){ return false; }
	size_str = in_str.size();
	while(1){
		//find variable x
		x_post = in_str.find("x", op_pre);
		if( x_post==std::string::npos ){//no more "x" -> only last constant
			a=atoi( (in_str.substr(op_pre, size_str-op_pre)).c_str() );
			input[0]=a;
			break;
		}
		
		//coefficient
		len = x_post-op_pre;
		if( len==0 ){ a=1; }
		else if( len==1 && !in_str.compare(op_pre,1,"-") ){ a=-1; }
		else { a=atoi( (in_str.substr(op_pre, len)).c_str() ); }
		
		//find next operator
		op_pre = in_str.find("+", x_post);
		temp = in_str.find("-", x_post);
		if( temp<op_pre && temp!=std::string::npos && op_pre!=std::string::npos ){ op_pre=temp; }//"-" before "+"
		if( op_pre==std::string::npos && temp!=std::string::npos ){ op_pre=temp; } //only "-"
		if( op_pre==std::string::npos ){//no more operator -> only last "x"
			len = size_str-x_post;
			if( len==1 ){ b=1; }
			else { b=atoi( (in_str.substr(x_post+2, len-2)).c_str() ); }
			input[b]=a;
			break;
		}
		
		//power
		len = op_pre-x_post;
		if( len==1 ){ b=1; }
		else { b=atoi( (in_str.substr(x_post+2, len-2)).c_str() ); }
		
		if( !in_str.compare(op_pre,1,"+") ){ op_pre++; }//pass through "+"
		input[b]=a;
	}
	for(i=ARRAY_MAX-1;i>=0;i--) { 
		if (input[i] != 0) {
			*degree = i;
			break;
		} 
	}//reset
	
	return true;
}


