#include"tagger.cpp"
#include<iostream>
#include"usage.cpp"

int main(int argc, char const *argv[]){
	using namespace std;
	if(argc==1){
		cout<<usage;
		return 0;
	}
	string output,input;
	for(int post=1;post<argc;post++){
		string temp=argv[post];
		if(temp=="-o"||temp=="--output"){
			if(post+1<argc){
				output=argv[++post];
			}else{
				cerr<<"!no output file\n";
				return 0;
			}
		}else if(temp=="-h"||temp=="--help"){
			cout<<long_usage;
		}
		else{
			input=temp;
		}
	}
	if(output!=""&&input!=""){
		
	}
}