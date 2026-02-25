#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<unistd.h>
#include<stack>
#include"tagger.cpp"

void build(std::string input, std::string output){
	using namespace std;
	ifstream ifp(input);
	mkdir("temp");
	ofstream cppo("temp/temp.cpp");
	//test
	string line,temp;
	string state="@outside";
	stack<string> state_stack;

	//func define
	string fn_name,fn_ret;
	vector<pair<string,string>> fn_args;
	pair<string,string> fn_arg;

	while(getline(ifp,line)){
		/*
		@func_begin
		int fib(int k){
			return ...;
		}
		@func_end
		@func_begin
		int main(){
			cout<<fib(60);
		}
		@func_end
		*/
		/*
		var tst = "123";
		fn fib(k: int) int {
			//cpp
		}
		*/
		stringstream ss(line);
		while(ss>>temp){
			if(state=="@outside"&&temp=="var"){
				cppo<<"auto ";
				state_stack.push(state);
				state="@vardef";
			}else if(state=="@vardef"){
				if(temp==";"){
					cppo<<"; ";
					state=state_stack.top();
					state_stack.pop();
				}else{
					cppo<<temp<<" ";
				}
			}else if(state=="@outside"&&temp=="fn"){
				state_stack.push(state);
				state="@fn_gn";//getting name
			}else if(state=="@fn_gn"){
				fn_name=temp;
				state="@fn_wp";//waitting for (
			}else if(state=="@fn_wp"&&temp=="("){
				state="@fn_args";
			}else if (state=="@fn_args"){
				if(temp==":"){
					state="@fn_args_ty";
				}else{
					fn_arg.first=temp;
				}
			}else if(state=="@fn_args_ty"){
				if(temp==","){
					fn_args.emplace_back(fn_arg);
					state="@fn_args";
				}else if(temp==")"){
					state="@fn_wbp";
				}else{
					fn_arg.second=temp;
				}
			}else if(state=="@fn_wbp"&&temp=="{"){
				state="@fn_body";
				cppo<<fn_ret<<" "<<fn_name<<"(";
				for(int post=0;post<fn_args.size();post++){
					cppo<<fn_args[post].second<<" "<<fn_args[post].first<<
					(post!=fn_args.size()?",":")");
				}
				cppo<<"{";
			}else if(state=="@fn_wbp"){
				fn_ret=temp;
			}
		}
	}
}

void build_dev(std::string input, std::string output){

}