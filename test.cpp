#include"tagger.cpp"
#include<iostream>
using namespace std;
int main(){
	switch(tagSym("add","{return a+b;}")){
		case Rt:cout<<"Rt";break;
		case Ct:cout<<"Ct";break;
	};
	
}