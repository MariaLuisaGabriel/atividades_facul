#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

bool func(int i, int j){
    return (i<j)&&(abs(i-j)==2);
}

void moveAll3(std::vector<int> *arr) 
{ 
	int i,j;
    int temp;
    for (i = 0; i < arr->size() - 1; i++){
		for (j = 0; j < arr->size() - i - 1; j++) 
            if (arr->at(j+1)==3 && abs(arr->at(j) - arr->at(j + 1))==2){
                temp = arr->at(j);
                arr->at(j) = arr->at(j+1);
                arr->at(j+1) = temp;
            } 
                
    }
}

void moveAll5(std::vector<int> *arr) 
{ 
	int i,j;
    int temp;
    for (i = 0; i < arr->size() - 1; i++){
		for (j = 0; j < arr->size() - i - 1; j++) 
            if (arr->at(j+1)==5 && abs(arr->at(j) - arr->at(j + 1))==2){
                temp = arr->at(j);
                arr->at(j) = arr->at(j+1);
                arr->at(j+1) = temp;
            } 
                
    }
}
 
int main() {
    char num;
    std::vector<int> seq;
 
    while(1){
        num = getc(stdin);
        if(num=='\n') break;
        seq.push_back(num-'0');
    }
    
    moveAll5(&seq);
    moveAll3(&seq);

    for(auto i : seq){
        std::cout << i;
    }

    std::cout << std::endl;
 
    return 0;
}