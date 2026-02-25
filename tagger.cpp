//
#pragma once
#include<vector>
#include<map>
#include<string>

enum RoC{//Runtime or Comptime
	Rt=1,
	Ct=0
};

std::map<std::string,RoC> sym2roc={
	{"input",Rt},
	{"time",Rt},
	{"rand",Rt},
};

std::map<std::string,std::vector<std::string> >deplist;

std::string noStr(std::string inputStr) {
	/*
	VIBE CODE
	DONOT BELIEVE IT
	*/

    std::string result;
    bool inQuotes = false;

    for (char c : inputStr) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } 
        else if (!inQuotes) {
            result += c;
        }
    }

    return result;
}

RoC tagSym(std::string symn,std::string body){
	using namespace std;
	auto trueBody=noStr(body);
	for (const auto &p:sym2roc){
		auto key=p.first;auto value=p.second;
		if((value==Rt)){
			if((trueBody.find(key)!=string::npos)){
				return sym2roc[symn]=Rt;
			}
		}else{
			if((trueBody.find(key)!=string::npos)){
				deplist[symn].push_back(key);
			}
		}
	}
	return sym2roc[symn]=Ct;
}