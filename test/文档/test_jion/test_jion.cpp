#include "json.hpp"
using json = nlohmann::json;
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

//json序列化实例1
void func1(){
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang_san";
    string sendBuf = js.dump(); //数据对象转成字符串
    cout << sendBuf <<endl;
    cout << sendBuf.c_str() <<endl;
}
//json 序列化实例2
void func2(){
    json js;
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    js["List"] = vec;

    map<int, string> m;
    m.insert({1,"华为"});
    m.insert({2,"荣耀"});
    js["path"] = m;
    cout << js <<endl;
}
int main(){
    func2();
    return 0;
}
