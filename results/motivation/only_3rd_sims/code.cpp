#include <iostream>
#include <fstream>
#include <string>
#include<bits/stdc++.h>
using namespace std;

#define ld long double
int main(int argc, char * argv[]){
   fstream newfile;
   newfile.open(argv[1],ios::in);
   if (newfile.is_open()){
      string tp;
      vector<int> inc,dec;
      int total;
      vector<int> newstat;
      while(getline(newfile, tp)){
         if (tp.find("L2cache.perblockretentioninc") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    int tot=0;
		    int val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    inc.push_back(tot);
		 }
		 if (tp.find("L2cache.perblockretentiondec") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    int tot=0;
		    int val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    dec.push_back(tot);
		 }
		 if (tp.find("L2cache.newstatmotivation") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    int tot=0;
		    int val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    newstat.push_back(tot);
		 }
		 if (tp.find("L2cache.resetcycleindex") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    int tot=0;
		    int val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    total=tot;
		 }

      }
      // int arr[5]={0};
      // for(int i=0;i<inc.size();i++)
      // {
      // 	int temp = floor(100*(((double)(inc[i]+dec[i]))/total));
      // 	if(temp==100)
      // 		temp--;
      // 	arr[temp/20]++;
      // }
      // for(int i=0;i<5;i++)
      // 		cout<<arr[i]<<endl;

      ld arr[21]={0};
      ld sum=0;
      for(int i=0;i<inc.size();i++)
      {
      	int temp = ceil(100*(((double)(inc[i]+dec[i]))/total));
      	if(temp==100)
      		temp--;
      	arr[temp/5]+=1;
      	sum++;
      }
      for(int i=0;i<=20;i++)
      {
      	arr[i]/=sum;
      	arr[i]*=100;
      	// if(i>0)
      	// 	arr[i]+=arr[i-1];
      	// cout<<arr[i]<<endl;
      }

      total--;
      float interval = (float)(total)/(float)11.0;
      
      int avg =0;
      int k=1;
      int count=0;
      for(int i=0;i<total;i++){
		avg=avg+newstat[i];
		count ++;
		if(i>=(floor(k*interval)-1)){
			cout<<(avg)/(40.96*16*count)<<endl;
			k++;
			avg=0;
			count =0;
		}
      	
      }
      // for(int i=1;i<=total;i++)
      // 	cout<<newstat[i]<<endl;
      newfile.close();
   }
}