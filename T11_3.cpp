/*/  Message:
     This program was written for a suffix array problem when I took the course Advanced Programming in Semester B of 2016/2017.
     I spent a lot of time understanding this algorithm and implementing it. I think it's really cool so I chose it 
     as the sample code for my application:) The problem is available at UVa online judge(UVa 11512).
/*/
//
//  main.cpp
//  T11_3
//
//  Created by youhan on 4/10/17.
//  Copyright © 2017 youhan. All rights reserved.
//
//要比较所有后缀的最长公共前缀，如果有此前缀则至少出现两次，因此可以直接由hight数组去最大值输出
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
const int maxi=1001;
using namespace std;
int length;
char current[maxi];
//find repetition in AGCT array, at least two times, SA
//分别比较两个关键字
int ranks[maxi],wb[maxi],wv[maxi],wss[maxi],height[maxi];

bool cmp(int *r,int a,int b,int l){
    return r[a]==r[b] && r[a+l]==r[b+l];
}

void calcuHeight(int *sa, int *s){
    int i,j,k;
    for(i=1;i<=length;i++)
        ranks[sa[i]]=i;
    for(i=k=0;i<length;height[ranks[i++]]=k)
        for(k?k--:0,j=sa[ranks[i]-1];s[i+k]==s[j+k];k++);
}

void da(int *r,int *sa,int n,int m){
    int i,j,p,*x=ranks,*y=wb,*t;
    for(i=0;i<m;i++) wss[i]=0;
    for(i=0;i<n;i++) wss[x[i]=r[i]]++;
    for(i=1;i<m;i++) wss[i]+=wss[i-1];
    for(i=n-1;i>=0;i--) sa[--wss[x[i]]]=i;
    
    for(j=1,p=1;p<n;j*=2,m=p){
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<m;i++) wss[i]=0;
        for(i=0;i<n;i++) wss[wv[i]]++;
        for(i=1;i<m;i++) wss[i]+=wss[i-1];
        for(i=n-1;i>=0;i--) sa[--wss[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}

int main(int argc, const char * argv[]) {
    int cases;
    int r[maxi],sa[maxi];

    scanf("%d", &cases);
    while (cases--){
        scanf("%s",current);
        length=(int)strlen(current);
        for(int i=0; i<length; i++) r[i] = current[i]-'A'+1;
        r[length]=0;//IMPORTANT
        da(r, sa, length+1, 27);
        calcuHeight(sa, r);
        // rank[i] : suffix(i)排第几; sa[i] : 排在第i个的是谁
        int max_value=0;
        for (int i=1;i<=length;i++)
            max_value=max(height[i],max_value);
        if (max_value){
            int count=1, k=0;
            for (int i=1;i<=length;i++)
                if (height[i]>=max_value){
                    k=i;
                    for (int j=i;j<=length && max_value<=height[j];j++)
                        count++;
                    break;
                }
            for (int j=sa[k];j<sa[k]+max_value;j++)
                printf("%c", current[j]);
            printf(" %d\n",count);
        }else
            printf("No repetitions found!\n");
    }
    return 0;
}
