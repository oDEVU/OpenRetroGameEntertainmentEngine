#pragma once

#include <iostream>
#include <vector>

#include "static.hpp"

using namespace std;

namespace orgee
{

int Partition(vector<static_object> &v, int start, int end){
	
	int pivot = end;
	int j = start;
	for(int i=start;i<end;++i){
		if(v[i].distance>v[pivot].distance){
			swap(v[i],v[j]);
			++j;
		}
	}
	swap(v[j],v[pivot]);
	return j;
	
}

void quick_sort(vector<static_object> &v, int start, int end ){

	if(start<end){
		int p = Partition(v,start,end);
		quick_sort(v,start,p-1);
		quick_sort(v,p+1,end);
	}
	
}
}