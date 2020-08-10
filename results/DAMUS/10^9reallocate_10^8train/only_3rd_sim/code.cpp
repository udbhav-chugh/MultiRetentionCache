#include <iostream>
#include <fstream>
#include <string>
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double

ll m_total_write_counter[4096][16];int xw=0,yw=0;
ll m_total_read_counter[4096][16];int xr=0,yr=0;
ll m_total_write_cache_set[4096]; int xc =0;
ll m_total_write_retention_time[4]; int xt=0;
ll m_total_read_retention_time[4]; int xtr=0;
ll m_total_writeback_retention_time[4]; int xb=0;
ll m_swaps_between_retentions[4][4]; int xs=0,ys=0;
ll m_reset_cycles_index;
ll max_write_count_over_reset_interval;
ll total_writes;
ld lifetime;
ld static_energy;


int main(int argc, char * argv[]){
   fstream newfile;
   newfile.open(argv[1],ios::in);

	  if (newfile.is_open()){
	string tp;
	total_writes = 0;
	ll maxwrites=0;

      while(getline(newfile, tp)){
         if (tp.find("L2cache.totalwrites:") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    ll tot=0;
		    ll val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    total_writes+=tot;
		    maxwrites=max(maxwrites,tot);
		    m_total_write_counter[xw][yw]=tot;
		    yw++;
		    if(yw%16==0)
		    {
		    	yw=0;
		    	xw++;
		    }
		 }
		 if (tp.find("L2cache.totalreads:") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    ll tot=0;
		    ll val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    m_total_read_counter[xr][yr++]=tot;
		    if(yr%16==0)
		    {
		    	yr=0;
		    	xr++;
		    }
		 }

		 if (tp.find("L2cache.totalwritescacheset:") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    ll tot=0;
		    ll val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    m_total_write_cache_set[xc++]=tot;
		 }
		 if (tp.find("L2cache.totalwritesretentionset:") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    ll tot=0;
		    ll val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    m_total_write_retention_time[xt++]=tot;
		 }

		 if (tp.find("L2cache.totalreadsretentionset:") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    ll tot=0;
		    ll val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    m_total_read_retention_time[xtr++]=tot;
		 }

		 if (tp.find("L2cache.totalwritebackretentionset:") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    ll tot=0;
		    ll val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    m_total_writeback_retention_time[xb++]=tot;
		 }

		 if (tp.find("L2cache.totalswapsbetweenretention:") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    ll tot=0;
		    ll val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    m_swaps_between_retentions[xs][ys++]=tot;
		    if(ys%4==0)
		    {
		    	ys=0;
		    	xs++;
		    }
		 }

		 if (tp.find("L2cache.resetcycleindex") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    ll tot=0;
		    ll val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    m_reset_cycles_index=tot;
		 }

		 if (tp.find("L2cache.writecountoverresetinterval") != std::string::npos) {
		    int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    ll tot=0;
		    ll val=1;
		    while(tp[index]>='0' && tp[index]<='9')
		    {
		    	tot+=(tp[index]-'0')*val;
		    	val*=10;
		    	index--;
		    }
		    max_write_count_over_reset_interval=tot;
		 }
		 if(tp.find("sim_seconds") != std::string::npos){
		 	int index = tp.size()-1;
		    while(tp[index]<'0' || tp[index]>'9')
		    	index--;
		    string temp="";
		    while((tp[index]>='0' && tp[index]<='9') || tp[index]=='.')
		    {
	    		temp+=tp[index];	
		    	index--;
		    }
		    reverse(temp.begin(),temp.end());
		    ld tot = std::stod(temp);
		    static_energy = tot * 344.5;
		    static_energy/=1000;
		 }

      }

	// cout<<"m_total_write_counter"<<endl;
	// for(int i=0;i<4096;i++)
	// {
	// 	for(int j=0;j<16;j++)
	// 		cout<<m_total_write_counter[i][j]<<" ";
	// 	cout<<endl;
	// }
	// cout<<"m_total_read_counter"<<endl;
	// for(int i=0;i<4096;i++)
	// {
	// 	for(int j=0;j<16;j++)
	// 		cout<<m_total_read_counter[i][j]<<" ";
	// 	cout<<endl;
	// }
	// cout<<"m_total_write_cache_set"<<endl;
	// for(int i=0;i<4096;i++)
	// 		cout<<m_total_write_cache_set[i]<<" ";
	// cout<<endl;

	ld dynamic_energy;
	ld m_write_energy[4];
	ld m_read_energy[4];

    m_write_energy[0]=4.68902;
    m_write_energy[1]=5.77964;
    m_write_energy[2]=6.39038;
    m_write_energy[3]=6.69459;
    
    m_read_energy[0]=1.0439;
    m_read_energy[1]=1.05429;
    m_read_energy[2]=1.05992;
    m_read_energy[3]=1.06585;

	// cout<<"m_total_write_retention_time"<<endl;
	for(int i=0;i<4;i++)
	{
		// cout<<m_total_write_retention_time[i]<<" ";
		dynamic_energy+=(m_total_write_retention_time[i]*m_write_energy[i]);
	}
	// cout<<endl;
	// cout<<"m_total_read_retention_time"<<endl;
	for(int i=0;i<4;i++)
	{
		// cout<<m_total_read_retention_time[i]<<" ";
		dynamic_energy+=(m_total_read_retention_time[i]*m_read_energy[i]);
	}
	// cout<<endl;
	cout<<"m_total_writeback_retention_time"<<endl;
	ll tot_writebacks=0;
	for(int i=0;i<4;i++)
	{
		cout<<m_total_writeback_retention_time[i]<<" ";
		tot_writebacks+=m_total_writeback_retention_time[i];
	}
	cout<<endl;
	cout<<"total write backs"<<endl;
	cout<<tot_writebacks<<endl;
	// cout<<"m_swaps_between_retentions"<<endl;
	// for(int i=0;i<4;i++)
	// {
	// 	for(int j=0;j<4;j++)
	// 		cout<<m_swaps_between_retentions[i][j]<<" ";
	// 	cout<<endl;
	// }

	cout<<"m_reset_cycles_index"<<endl;
	cout<<m_reset_cycles_index<<endl;
	cout<<"max_write_count_over_reset_interval"<<endl;
	cout<<max_write_count_over_reset_interval<<endl;
	cout<<"Total Dynamic Energy"<<endl;
	cout<<dynamic_energy<<endl;

	ld write_avg = ((ld)total_writes)/(4096*16);
	ld intrav = 0;
	for(int i=0;i<4096;i++)
	{
		ld val = 0;
		for(int j=0;j<16;j++)
		{
			ld val2=0;
			for(int k=0;k<16;k++)
			{
				val2+=(m_total_write_counter[i][k]/16);
			}
			ld temp = m_total_write_counter[i][j]-val2;
			temp = temp*temp;
			val +=(temp/15);
		}
		val/=15;
		val = sqrt(val);
		intrav +=val;
	}
	intrav/=4096;
	intrav/=write_avg;
	cout<<"IntraV"<<endl;
	cout<<intrav<<endl;

	lifetime = 1/((ld)maxwrites);
	cout<<"Lifetime"<<endl;
	cout<<lifetime<<endl;
	cout<<"Maxwrites"<<endl;
	cout<<maxwrites<<endl;
	cout<<"static_energy"<<endl;
	cout<<static_energy<<endl;
      newfile.close();
   }
}
