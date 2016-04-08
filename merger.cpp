#include <iostream>
#include <fstream>

using namespace std;

void replaceAll(string& str, string toReplace,string replaceWith){
    if(toReplace==replaceWith) return;
    string processed;
    string remainder=str;
    int ndx=remainder.find(toReplace);
    while((ndx!=(int)string::npos)){
        processed+=remainder.substr(0,ndx)+replaceWith;
        remainder=remainder.substr(ndx+toReplace.size(),remainder.size()-1);  
        ndx=remainder.find(toReplace);
    }
    str=processed+remainder;
}
void replaceMergeSymbols(string filePath){
    fstream in;
    in.open(filePath.c_str(),ios::binary|ios::in|ios::ate);
    in.seekg(0l,ios::end);
    unsigned int size=in.tellg();
    cout<<size<<endl;
    in.seekg(0l,ios::beg);
    char buffer[size];
    in.read(buffer,size);
    in.close();
    string toEdit(buffer);
    cout<<"/*/ ======="<<filePath<<"/*/ ======="<<endl;
    cout<<toEdit<<endl;
    replaceAll(toEdit,"//* <<<<<<<","//* //* <<<<<<<");
    replaceAll(toEdit,"/*/ =======","/*/ /*/ =======");
    replaceAll(toEdit,"//*/>>>>>>>","//*///*/>>>>>>>");
    cout<<"==processed "<<filePath<<"=="<<endl;
    cout<<toEdit<<endl;
    cout<<"=====end "<<filePath<<"====="<<endl;
    cout<<endl;
    ofstream overwrite;
    overwrite.open(filePath.c_str());
    overwrite<<toEdit;
    overwrite.flush();
    overwrite.close();
}
bool isJava(string fileName){
    return(fileName.size()>4&&
            fileName.substr((fileName.size()-4),(fileName.size()-1))=="java");
}
bool isCpp(string fileName){
    return(fileName.size()>3&&
            fileName.substr((fileName.size()-3),(fileName.size()-1))=="cpp");
}
bool isC(string fileName){
    return(fileName.size()>2&&
            fileName.substr((fileName.size()-2),(fileName.size()-1))==".c");
}
int main(int argc, char** argv){
    string current;
    for(int i=0;i<argc;i++){
        current=argv[i];
        if(isCpp(current)||isJava(current)||isC(current)){
            if(current!=argv[0]){
                replaceMergeSymbols(current);
            }
        }
    }
    return 0;
}
